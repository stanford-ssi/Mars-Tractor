/**
 * @file client_interface.hpp
 * ----------
 * @author Bartolone, Kai
 * @date June 2021
 */

#ifndef _CLIENT_INTERFACE_HPP
#define _CLIENT_INTERFACE_HPP

#ifdef _WIN32
#include <sdkddkver.h>
#endif

#include <QObject>
#include "message.h"
#include "session.hpp"
#include "tsqueue.h"
#include <asio.hpp>
#include <functional>
#include <mutex>
#include <thread>

/**
 * @class client_interface
 * ----------
 * @description: Defines client entity that can synchronously make connections and maintain a
 * session with such connection.
 */
class client_interface: public QObject
{
  Q_OBJECT
  public:
    explicit client_interface(QObject* parent = nullptr);
    ~client_interface();

    /**
     * @fn connect
     * ----------
     * @returns: True on connection false on failed to connect.
     */
    bool connect(const std::string& host, uint16_t port);

    /**
     * @fn has_connection
     * ----------
     * @brief: Checks session connectivity.
     */
    bool inline has_connection() { return m_status; }

    /**
     * @fn push
     * ----------
     * @returns: True on message sent and false on sending error.
     */
    bool send(const message& msg);

    /**
     * @fn push
     * ----------
     * @brief: Adds message to session queue for sending. No guarantee that message reaches
     * destination.
     */
    void push(const message& msg);

signals:
  // void new_connection();
  // void end_connection();
  void status_change(bool status);

// private:
//   void join_session();

  protected:
    /**
     * @fn close
     * ----------
     * @brief: Deletes current session and and joins context thread.
     */
    void close();

    /**
     * @fn set_status
     * ----------
     * @brief: Sets the connection status.
     */
    void set_status(bool status);

    /**
     * @fn connect
     * ----------
     * @brief: Connect but uses endpoints.
     */
    bool connect(const asio::ip::tcp::resolver::results_type& endpoints);

    /**
     * @fn release
     * ----------
     * @brief: Deletes session.
     */
    void release();

  protected:
    std::atomic_bool m_status;
    tsqueue<message> m_incoming;

    asio::io_context m_context;
    std::thread m_context_thread;

    session* m_session = nullptr;
};
#endif