/**
 * @file client.cpp
 * -----------------------------
 * @author Bartolone, Kai
 * @date August 2020
 */

#include <client.hpp>

TcpClient::TcpClient(const std::string& serverName)
    : messageQueue(new std::queue<std::string>), serverName(serverName)
{
    clientThread = std::thread(&TcpClient::run, this);
}

TcpClient::~TcpClient()
{
    // TODO::fix this it is really bad
    isRunning = false;
    if (socket != nullptr) socket->close();
    if (clientThread.joinable()) clientThread.join();
    delete messageQueue;
}
// void TcpClient::run()
// {
//     while (isRunning)
//     {
//         try
//         {
//             endpoints = resolver.resolve(serverName, "daytime");
//         }
//         catch (const std::exception& e)
//         {
//             std::cerr << e.what() << '\n';
//             continue;
//         }

//         tcp::socket socket(io_context);
//         try
//         {
//             boost::asio::connect(socket, endpoints);
//         }
//         catch (const std::exception& e)
//         {
//             std::cerr << e.what() << '\n';
//             continue;
//         }

//         try
//         {
//             listen(socket);
//         }
//         catch (const std::exception& e)
//         {
//             std::cerr << e.what() << '\n';
//             continue;
//         }
//     }
// }

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
    size_t pos = buf.find(" ");

    while (pos != std::string::npos)
    {
        messageQueue->push(buf.substr(0, pos));
        // std::cout << buf.substr(0, pos + 1) << std::endl;
        parseMessage(buf.substr(0, pos));
        buf = buf.substr(pos + 1);
        pos = buf.find(" ");
    }
}
void TcpClient::run()
{
    while (isRunning)
    {
        listen();
    }
}
void TcpClient::listen()
{
    try
    {

        boost::asio::io_service io_service;
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(serverName, "daytime");
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        tcp::resolver::iterator end;

        tcp::socket socket(io_service);
        this->socket = &socket;
        boost::system::error_code error = boost::asio::error::host_not_found;
        while (error && endpoint_iterator != end)
        {
            socket.close();
            socket.connect(*endpoint_iterator++, error);
        }
        if (error) throw boost::system::system_error(error);

        socketConnected = true;
        sendConnectionStatus(socketConnected);

        std::string message;
        for (;;)
        {
            boost::array<char, 128> buf;
            boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer(buf), error);

            if (error == boost::asio::error::eof)
                break; // Connection closed cleanly by peer.
            else if (error)
                throw boost::system::system_error(error); // Some other error.

            std::string temp;
            std::copy(buf.begin(), buf.begin() + len, std::back_inserter(temp));
            message += temp;

            readBuffer(message);
        }
    }
    catch (std::exception& e)
    {
        socketConnected = false;
        this->socket = nullptr;
        sendConnectionStatus(socketConnected);

        // TODO: instead of outputing to console output to logview
        std::cerr << e.what() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void TcpClient::parseMessage(const std::string& message)
{
    using namespace std;

    string front = message.substr(1, message.find('e'));
    if (front == "frame")
    {
        // string temp = message.substr(message.find(':') + 2, message.find('}'));
        // string result = temp.substr(0, temp.length() - 1);
        string result = message.substr(message.find('e') + 1, message.length());
        sendFrame(result);
        return;
    }

    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();

    Json::Value root;
    string errors;

    bool parsingSuccessful =
        reader->parse(message.c_str(), message.c_str() + message.size(), &root, &errors);
    delete reader;

    if (!parsingSuccessful)
    {
        cerr << errors << endl;
        return;
    }

    // Send correct signal
    string id = root.getMemberNames().front();
    if (id == "log")
    {
        sendLog(root["log"].asString());
    }
    if (id == "gamepad")
    {
        sendLog(root["gamepad"].asString());
    }
}