#include <iostream>
#include <boost/bind/bind.hpp>
#include <stdlib.h>

#include "Connection.h"

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
        socket_.async_read_some(boost::asio::buffer(clientIP),
                                boost::bind(&Connection::handle_read, shared_from_this(),
                                            boost::asio::placeholders::error));
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