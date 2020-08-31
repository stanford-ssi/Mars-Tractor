/**
 * @file client.cpp
 * -----------------------------
 * @author Bartolone, Kai
 * @date August 2020
 */

#include <client.hpp>

TcpClient::TcpClient(const std::string& serverName)
    : messageQueue(new std::queue<std::string>), resolver(io_context)
{
}

TcpClient::~TcpClient()
{
    // TODO::fix this it is really bad
    resolver.cancel();
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

        size_t len = socket.read_some(boost::asio::buffer(buf), error); // Read in data

        if (error == boost::asio::error::eof)
            break; // Connection closed cleanly by host
        else if (error)
            throw boost::system::system_error(error); // Some other error

        std::string temp;
        std::copy(buf.begin(), buf.begin() + len, std::back_inserter(temp));
        message += temp;

        readBuffer(message);
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

void TcpClient::readBuffer(std::string& buf)
{
    size_t pos = buf.find("}");

    while (pos != std::string::npos)
    {
        messageQueue->push(buf.substr(0, pos + 1));
        buf = buf.substr(pos + 1);
        queuePushed();
        pos = buf.find("}");
    }
}

void TcpClient::connect()
{
    for (;;)
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
}