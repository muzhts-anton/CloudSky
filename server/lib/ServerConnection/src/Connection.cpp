#include <iostream>
#include <boost/bind/bind.hpp>
#include <stdlib.h>
#include <fstream>

#include "Connection.h"
#include "dbOperations.h"
#include "TCPServerSocket.h"

namespace ServerConnection {
    Connection::Connection(boost::asio::io_context& io_context, int port):
        strand_(boost::asio::make_strand(io_context)),
        socket_(strand_),
        newPort(port)
    {
        clientIP.resize(clientIPSize);
    }

    boost::asio::ip::tcp::socket& Connection::socket()
    {
        return socket_;
    }

    void Connection::start()
    {
        std::cout << "[LOG] : Start\n";
        prepareClient();
        socket_.async_read_some(boost::asio::buffer(clientIP),
                                boost::bind(&Connection::handle_read, shared_from_this(),
                                            boost::asio::placeholders::error));
    }

    void Connection::prepareClient()
    {
        std::string pathToClientInfo = "clientInfo.bin";
        std::cout << "[LOG] : Ready to interact with client\n";
        TCPServer::TCPServerSocket TCPSocket(8090, "0.0.0.0");
        TCPSocket.activateSocket();
        do 
        {
            TCPSocket.receiveFile(pathToClientInfo);
            std::cout << "[LOG] : Have the 1st part read\n";
            ViktorDev::ServerRegOrLog receiver(pathToClientInfo);
            receiver.receiveIt();
            TCPSocket.receiveFile(pathToClientInfo);
            if (receiver.status)
            {
                dbInteraction::authInformation receivedMessage;
                ViktorDev::ServerAuthorizationHandler serverAuth(pathToClientInfo, receivedMessage);
                serverAuth.receiveIt();
                std::cout << std::endl<< std::endl<< "received message:"<< std::endl;
                serverAuth.printMessage();
                serverAuth.check();
                serverAuth.sendIt();
                serverAuth.printResult();
                TCPSocket.transmitFile(pathToClientInfo);
                if (serverAuth.checkingResult == ViktorDev::AuthorizationResult::SUCCESS)
                {
                    serverAuth.sendUserInfo();
                    TCPSocket.transmitFile(pathToClientInfo);
                    break;
                }
            }
            else
            {
                dbInteraction::registrationInfo receivedRegMessage;
                ViktorDev::ServerRegistrationHandler serverReg(pathToClientInfo, receivedRegMessage);
                serverReg.receiveIt();
                std::cout << std::endl<< "received message:" << std::endl;
                serverReg.printMessage();
                serverReg.check();
                serverReg.sendIt();
                serverReg.printResult();
                TCPSocket.transmitFile(pathToClientInfo);
                if (serverReg.checkingResult == ViktorDev::RegistrationResult::SUCCESS)
                    break;
            }
        }
        while (true);

    }

    void Connection::getClientInfo()
    {
        std::cout << "[LOG] : Ready to read client info\n";
        buffer.resize(1024);
        std::cout << "[LOG] : buffer resized\n";
        socket_.async_read_some(boost::asio::buffer(buffer, 1024), boost::bind(&Connection::handleClientInfo, shared_from_this(),
                                            boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        std::cout << "[LOG] : End read\n";
    }

    void Connection::handleClientInfo(
        const boost::system::error_code& error, // Result of operation.
        std::size_t bytes_transferred           // Number of bytes read.
    )
    {
        std::cout << "[LOG] : Ready to write client info to file\n";
        std::cout << "[LOG] : getClientInfo error: " << error << std::endl;
        std::string filename = "clientInfo.bin";
        std::fstream file;
        file.open(filename, std::ios::out | std::ios::trunc | std::ios::binary);
        if (file.is_open()) {
            std::cout << "[LOG] : TCP File Created.\n";
        } else {
            std::cerr << "[ERROR] : TCP File creation failed." << std::endl;
            throw std::invalid_argument("[ERROR] : TCP File creation failed.");
        }
        for (size_t i = 0; i < bytes_transferred; i++)
            file.write((&buffer[0]) + i, 1);
        file.close();
            std::cout << "[LOG] : TCP File Saved.\n";
    }

    std::string Connection::find_free_worker()
    {
        for (size_t i = 0; i < workersAmount; i++)
        {
            if (workersBussiness.at(i) == false)
            {
                workersBussiness.at(i) = true;
                return workersIP.at(i);
            }
        }
        return workersAreBusy;
    }

    void Connection::handle_read(const boost::system::error_code& e)
    {
        if (!e)
        {
            std::cout << "Клиент пришёл с IP " << clientIP << std::endl;
            std::string currentWorker;
            bool found = false;
            for (size_t i = 0; i < workersAmount; i++)
            {
                if (clientIP.compare(workersIP.at(i)) == 0)
                {
                    std::cout << "Освобождаем worker с IP " << clientIP << std::endl;
                    workersBussiness.at(i) = false;
                    currentWorker = workerFreedom;
                    found = true;
                }
            }
            if (!found)
                currentWorker = find_free_worker();
            std::cout << std::endl;
            std::cout << "Будем подключать клиента на IP " << currentWorker << std::endl;
            char buffer[20] = { 0 };
            int length = std::snprintf(buffer, 20, "%s", &currentWorker[0]);
            boost::asio::async_write(socket_, boost::asio::buffer(buffer, length),
                boost::bind(&Connection::handle_write, shared_from_this(),
                        boost::asio::placeholders::error));
        }
    }

    void Connection::handle_write(const boost::system::error_code& e)
    {
        if (!e)
        {
            std::cout << std::endl;
            boost::system::error_code ignored_ec;
            socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
        }
    }

}