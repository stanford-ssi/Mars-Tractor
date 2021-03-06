/** @file client.hpp
 * -----------------------------
 * @author Bartolone, Kai
 * @date August 2020
 */

#ifndef _CLIENT_HPP
#define _CLIENT_HPP

#include <QObject>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <chrono>
#include <iostream>
#include <json/json.h>
#include <queue>
#include <string>

using boost::asio::ip::tcp;

class TcpClient : public QObject
{
    Q_OBJECT

  public:
    /**
     * @fn TcpClient
     * -------------------------
     * Accesses server and constructs io_context and resolves server endpoints. Attempts to create a
     * socket connection on a separate thread.
     */
    TcpClient(const std::string& serverName);

    /**
     * @fn ~TcpClient
     * -------------------------
     * Cleans up client memory and closes socket connnection and thread.
     */
    ~TcpClient();

    /**
     * @fn getNextMessage
     * -------------------------
     * Gets next message. returns empty string if no messages have been received.
     */
    std::string getNextMessage();

    /**
     * @fn connect
     * -----------------------------
     * Attempts to connect to socket on clientThread. This function will throw an exception if there
     * is a problem.
     */
    void connect();

  private:
    std::queue<std::string>* messageQueue;
    tcp::socket* socket = nullptr;
    std::string serverName;
    bool socketConnected = false;
    bool isRunning = true;
    std::thread clientThread;

  private:
    /**
     * @fn listen
     * -----------------------------
     * Performs a blocking attempt to connect to a server and infinitely listens for input once
     * connected.
     */
    void listen();
    void run();

    /**
     * @fn parseMessage
     * -----------------------------
     * Parses message into json object and sends correct signals.
     */
    void parseMessage(const std::string& message);

    /**
     * @fn readBuffer
     * ---------------------------
     * Reads char buffer and sections off complete messages.
     */
    void readBuffer(std::string& buf);

  signals:
    void sendLog(const std::string& message);
    void sendFrame(const std::string& message);
    void sendConnectionStatus(bool status);
};

#endif