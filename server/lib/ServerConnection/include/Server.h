#ifndef SERVER_HPP_

#define SERVER_HPP_

#include <fstream>
#include <iostream>
#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <thread>

#include "Connection.h"

constexpr int serverDefaultPort = 8050;
constexpr const char* serverDefaultIp = "127.0.0.1";

class Server: private boost::noncopyable {
public:
    Server(const std::string& address, const std::string& port, std::size_t threadPoolSize);

    void run();

private:
    std::size_t serverThreadPoolSize;
    boost::asio::io_context serverContext;
    boost::asio::signal_set serverSignals;
    boost::asio::ip::tcp::acceptor serverTCPAcceptor;
    boost::shared_ptr<ServerConnection::Connection> newConnection;
    char* hostName;
    int port;
    int workerPort;

    void startAccept();

    void handleAccept(const boost::system::error_code& e);

    void handleStop();
};

#endif