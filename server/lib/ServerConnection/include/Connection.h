#ifndef CONNECTION_H_

#define CONNECTION_H_

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace ServerConnection {
class Connection:
    public boost::enable_shared_from_this<Connection>,
    private boost::noncopyable
{
public:
    explicit Connection(boost::asio::io_context& ioContext, int port);
    boost::asio::ip::tcp::socket& socket();

    void start();

private:
    void handle_read(const boost::system::error_code& e);

    void handle_write(const boost::system::error_code& e);

    boost::asio::strand<boost::asio::io_context::executor_type> strand_;

    boost::asio::ip::tcp::socket socket_;

    boost::array<char, 1024> buffer_;

    int newPort;
};
}

#endif