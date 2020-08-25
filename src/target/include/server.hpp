/** @file server.hpp
 * -----------------------------
 * @brief This file defines a server that makes a tcp connection to a client defined in the console
 * target.
 * @author Bartolone, Kai
 * @date August 2020
 */

#ifndef _SERVER_HPP
#define _SERVER_HPP

#include <boost/asio.hpp>
#include <chrono>
#include <iostream>
#include <json/json.h>
#include <queue>
#include <string>
#include <thread>
#include <unordered_set>

class TcpServer
{
public:
    // TcpServer(TcpServer&&) = default;
    
    /**
     * @fn TcpServer
     * -------------------------
     * Creates a server on the computers ip address and waits for a socket connection on a separate
     * thread. Can not be copied.
     */
    TcpServer();

    /**
     * @fn ~TcpServer
     * -------------------------
     * Cleans up memory and ends thread.
     */
    ~TcpServer();

    /**
     * @fn addMessage
     * -------------------------
     * This method adds a message to the messageQueue. It ensures that only one message of a certain
     * id is added at a time except for server logs. Bool socketConnected must be true in order to
     * add a message. Returns true if message is added.
     */
    bool addMessage(std::string id, std::string value);

    /** 
     * @fn hasConnection
     * -------------------------
     * This method is a getter for bool socketConnected.
     */
    bool hasConnection();

protected:
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor acceptor;
    bool socketConnected = false;
    std::queue<std::pair<std::string, std::string>>* messageQueue;
    std::thread serverThread;

protected:
    /**
     * @fn run
     * -------------------------
     * Infinite loop that attempts to send messages from messageQueue through the socket connection.
     * If no socket is connected, the loop is blocked. This method can throw a socket exception.
     */
    void run();

    /**
     * @fn stop
     * -------------------------
     * Ends server.
     */
    void stop();


    // Mat to string maybe
};

#endif