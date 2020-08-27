/** @file client.cpp
 * -----------------------------
 * @author Bartolone, Kai
 * @date August 2020
 */

#include <client.hpp>

TcpClient::TcpClient(const std::string& serverName)
    : messageQueue(new std::queue<std::string>), resolver(io_context)
{
    try
    {
        endpoints = resolver.resolve(serverName, "daytime");
        socketConnected = true;
    }
    catch (const std::exception& e)
    {
        socketConnected = false;
        // log this to gui somehow std::cerr << e.what() << '\n';
    }

    if (socketConnected)
    {
        clientThread = std::thread(&TcpClient::listen, this);
    }
}

TcpClient::~TcpClient()
{
    if (clientThread.joinable()) clientThread.join();
    delete messageQueue;
}

void TcpClient::listen()
{
    // Construct containers for reading in messages
    std::stack<char> brackets;
    std::string message;

    // Connect to socket
    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);

    for (;;)
    {
        // Conatiners for buffers
        boost::array<char, 128> buf;
        boost::system::error_code error;

        size_t len = socket.read_some(boost::asio::buffer(buf), error);    // Read in data

        if (error == boost::asio::error::eof)
            break;    // Connection closed cleanly by host
        else if (error)
            throw boost::system::system_error(error);    // Some other error

        for (char c : buf)
        {
            message += c;
            if (c == '}')
            {
            messageQueue->push(message);
            message = "";
            }
        }

        std::cout.write(buf.data(), len);
    }
}

std::string TcpClient::getNextMessage()
{
    std::string result;

    if (!messageQueue->empty())
    {
        result = messageQueue->front();
        messageQueue->pop();
    }

    return result;
}