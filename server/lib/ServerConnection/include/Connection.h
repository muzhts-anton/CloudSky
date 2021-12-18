#ifndef CONNECTION_H_

#define CONNECTION_H_

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <iostream>
#include <string>
#include <array>

constexpr int clientIPSize = 13;
constexpr int workersAmount = 4;
constexpr const char *paulIP = "10.147.18.164";
constexpr const char *kostyaIP = "10.147.18.218";
constexpr const char *tonyIP = "10.147.18.148";
constexpr const char *localhost = "127.0.0.1";
constexpr const char *workersAreBusy = "BUSY";
constexpr const char *workerFreedom = "FREE";


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

    std::string find_free_worker();

    boost::asio::strand<boost::asio::io_context::executor_type> strand_;

    boost::asio::ip::tcp::socket socket_;

    //boost::array<char, 1024> buffer_;
    std::array<std::string, workersAmount> workersIP = { paulIP, kostyaIP, tonyIP, localhost };
    std::array<bool, workersAmount> workersBussiness = { true, false, false, true};
    std::string clientIP;
    int newPort;
    
};
}

#endif