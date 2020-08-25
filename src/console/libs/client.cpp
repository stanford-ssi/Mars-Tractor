/** @file client.cpp
 * -----------------------------
 * @author Bartolone, Kai
 * @date August 2020
 */

#include <client.hpp>

TcpClient::TcpClient(const std::string& serverName) : resolver(io_context)
{
    try
    {
    endpoints = resolver.resolve(serverName, "daytime");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void TcpClient::listen()
{
    // Connect to socket
    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);

    while (1)
    {
        boost::array<char, 128> buf;
        boost::system::error_code error;

        size_t len = socket.read_some(boost::asio::buffer(buf), error);

        if (error == boost::asio::error::eof)
            break;    // Connection closed cleanly by host
        else if (error)
            throw boost::system::system_error(error);    // Some other error

        std::cout.write(buf.data(), len);
    }
}