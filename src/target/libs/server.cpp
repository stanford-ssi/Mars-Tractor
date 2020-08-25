/** @file server.cpp
 * -----------------------------
 * @brief This file implements server.hpp.
 * @author Bartolone, Kai
 * @date August 2020
 */

#include <server.hpp>

TcpServer::TcpServer()
    : acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 13)),
      messageQueue(new std::queue<std::pair<std::string, std::string>>),
      serverThread(&TcpServer::run, this)
{
}

TcpServer::~TcpServer()
{
    stop();
    delete messageQueue;
}

void TcpServer::run()
{
    using boost::asio::ip::tcp;
    using namespace std;

    try
    {
        for (;;)
        {
            // Create socket connection with client
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            socketConnected = true;

            // Infinite loop of sending messages in message queue
            for (;;)
            {
                // Get message from messageQueue
                if (messageQueue->empty()) continue;
                pair<string, string> pair = messageQueue->front();
                messageQueue->pop();

                // Convert message to JSON
                Json::Value message;
                message[pair.first] = pair.second;

                // Convert JSON to string
                Json::StreamWriterBuilder builder;
                builder["indentation"] = "";    // If you want whitespace-less output
                const std::string output = Json::writeString(builder, message);

                // Send message to client
                boost::system::error_code ignored_error;
                boost::asio::write(socket, boost::asio::buffer(output), ignored_error);
            }
        }
    }
    // Make sure to catch exception if client stops connection
    catch (std::exception& e)
    {
        socketConnected = false;
        std::cerr << e.what() << std::endl;
    }
}

bool TcpServer::addMessage(std::string id, std::string value)
{
    using namespace std;    // For string usage

    // Checks for server socket connection to client
    if (!socketConnected) return false;

    pair<string, string> pair(id, value);
    messageQueue->push(pair);
    return true;

    // Passthrough for server logs
}

void TcpServer::stop()
{
    acceptor.close();
    if (serverThread.joinable()) serverThread.join();
}

bool TcpServer::hasConnection() { return socketConnected; }