#include <iostream>
#include <boost/bind/bind.hpp>

#include "Connection.h"

namespace ServerConnection {
    Connection::Connection(boost::asio::io_context& io_context, int& port):
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
            int length = std::snprintf(buffer, 20, "%d", newPort++);
            boost::asio::async_write(socket_, boost::asio::buffer(buffer, length),
                boost::bind(&Connection::handle_write, shared_from_this(),
                        boost::asio::placeholders::error));
        }
    }

    void Connection::handle_write(const boost::system::error_code& e)
    {
        if (!e)
        {
            boost::system::error_code ignored_ec;
            socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
        }
    }

}