/** @file client.hpp
 * -----------------------------
 * @author Bartolone, Kai
 * @date August 2020
 */

#ifndef _client_Included
#define _client_Included

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

class TcpClient
{
public:
    /**
     * @fn TcpClient
     * -------------------------
     * Accesses server and constructs io_context and resolves server endpoints. Does not create or
     * connect socket.
     */
    TcpClient(const std::string& serverName);
    ~TcpClient();
    void listen();

private:
    boost::asio::io_context io_context;
    tcp::resolver resolver;
    tcp::resolver::results_type endpoints;
};

#endif