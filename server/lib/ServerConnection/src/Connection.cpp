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
    }

    boost::asio::ip::tcp::socket& Connection::socket()
    {
        return socket_;
    }

    void Connection::start()
    {
        socket_.async_read_some(boost::asio::buffer(buffer_),
                                boost::bind(&Connection::handle_read, shared_from_this(),
                                            boost::asio::placeholders::error));
    }

    void Connection::handle_read(const boost::system::error_code& e)
    {
        if (!e)
        {
            char buffer[20] = { 0 };
            std::cout << "Будем подключать клиента на порт " << newPort << std::endl;
            int length = std::snprintf(buffer, 20, "%d", newPort);
            boost::asio::async_write(socket_, boost::asio::buffer(buffer, length),
                boost::bind(&Connection::handle_write, shared_from_this(),
                        boost::asio::placeholders::error));
        }
    }

    void Connection::handle_write(const boost::system::error_code& e)
    {
        if (!e)
        {
            char command[180];
            snprintf(command, 180, "docker run --rm --net=host -it -p \
            0.0.0.0:%d:%d -e IP=0.0.0.0 -e PORT=%d \
            cloud-sky-worker", newPort, newPort, newPort);
            std::cout << command << std::endl;
            system(command);
            boost::system::error_code ignored_ec;
            socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
        }
    }

}