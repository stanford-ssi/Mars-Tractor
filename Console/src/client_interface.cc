/**
 * @file client_interface.cc
 * ----------
 * @author Bartolone, Kai
 * @date June 2021
 */

#include "client_interface.hpp"

client_interface::client_interface(QObject* parent): QObject(parent)
{
    // Start context thread
    m_context_thread = std::thread([this]() { m_context.run(); std::cout << "finished running"<<std::endl;});

    // Connect signals
    m_status = false;
    QObject::connect(this, &client_interface::status_change, this, &client_interface::set_status);
}

client_interface::~client_interface() { close(); }

bool client_interface::connect(const std::string& host, uint16_t port)
{
    try
    {
        // Resolve hostname/ip-address into tangiable physical address
        asio::ip::tcp::resolver resolver(m_context);
        asio::ip::tcp::resolver::results_type endpoints =
            resolver.resolve(host, std::to_string(port));
        connect(endpoints);
    }
    catch (std::exception& e)
    {
        std::cerr << "[CLIENT] Exception: " << e.what() << std::endl;
        return false;
    }
    return true;
}

void client_interface::close()
{
    // Release previous session
    release();

    // Join context thread which should have no jobs
    m_context.stop();
    if (m_context_thread.joinable()) m_context_thread.join();
}

bool client_interface::send(const message& msg)
{
    if (has_connection())
    {
        return m_session->send(msg);
    }
    return has_connection();
}

void client_interface::push(const message& msg)
{
    if (has_connection())
    {
        m_session->push(msg);
    }
}


bool client_interface::connect(const asio::ip::tcp::resolver::results_type& endpoints)
{
    // std::cout << "[Client] connecting " << std::endl;
    // release();
    close();


    asio::ip::tcp::socket socket(m_context);
    asio::error_code ec;

    // Request asio attempts to connect to an endpoint
    asio::connect(socket, endpoints, ec);
    if (!ec)
    {
        std::function<void(bool)> signal = std::bind(&client_interface::status_change, this, std::placeholders::_1);
        m_session = new session(std::move(socket), m_incoming, this, signal);//, this, (const char*)&client_interface::status_change);

    // Start context thread
    m_context.restart();
    m_context_thread = std::thread([this]() { m_context.run(); std::cout << "finished running"<<std::endl;});
    }
    else
    {
        std::cerr << "[CLIENT] Error could not resolve endpoints." << std::endl;
        return false;
    }
    return true;
}

void client_interface::release()
{
    if (m_session == nullptr) return;
    delete m_session;
    m_session = nullptr;
}

void client_interface::set_status(bool status)
{
    m_status = status;
}