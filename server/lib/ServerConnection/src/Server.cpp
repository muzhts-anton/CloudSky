#include <iostream>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/socket.h>
#include <thread>
#include <boost/bind/bind.hpp>

#include "DataBaseHandler.h"
#include "Interactions.h"
#include "Server.h"
#include "Connection.h"
#include "SoundComponent.h"
#include "VideoComponent.h"
#include "constants.h"

#include <unistd.h>


Server::Server(const std::string& address, const std::string& initPort, std::size_t threadPoolSize):
    serverThreadPoolSize(threadPoolSize),
    serverSignals(serverContext),
    serverTCPAcceptor(serverContext),
    newConnection()
{
    port = std::stoi(initPort);
    workerPort = port + 1;
    serverSignals.add(SIGINT);
    serverSignals.add(SIGTERM);
    serverSignals.async_wait(boost::bind(&Server::handleStop, this));
    
    boost::asio::ip::tcp::resolver resolver(serverContext);
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(address, initPort).begin();
    serverTCPAcceptor.open(endpoint.protocol());
    serverTCPAcceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    serverTCPAcceptor.bind(endpoint);
    serverTCPAcceptor.listen();

    startAccept();
}

void Server::run()
{
    std::vector<std::shared_ptr<std::thread> > threads;
    for (std::size_t i = 0; i < serverThreadPoolSize; ++i)
    {
        std::shared_ptr<std::thread> thread(new std::thread(
                boost::bind(&boost::asio::io_context::run, &serverContext)));
        threads.push_back(thread);
    }

    for (std::size_t i = 0; i < threads.size(); ++i)
        threads[i]->join();
}

void Server::startAccept()
{
    newConnection.reset(new ServerConnection::Connection(serverContext, workerPort++));
        serverTCPAcceptor.async_accept(newConnection->socket(),
        boost::bind(&Server::handleAccept, this,
        boost::asio::placeholders::error));
}

void Server::handleAccept(const boost::system::error_code& e)
{
    if (!e)
    {
        newConnection->start();
    }
    startAccept();
}

void Server::handleStop()
{
    serverContext.stop();
}

