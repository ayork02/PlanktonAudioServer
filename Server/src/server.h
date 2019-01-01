#pragma once

#include <plankaudio.h>
#include <boost/asio.hpp>
#include <string>
#include <iostream>
#include <functional>
#include <system_error>

using namespace boost::asio;
using ip::tcp;

class Server
{
public:
    Server(boost::asio::io_context& io_context);
    ~Server();
    void start();
    void stop();
    

private:
    bool stopped = false;
    bool audioInit = false;
    tcp::socket socket;
    tcp::acceptor acceptor;
    std::error_code err;
    steady_timer deadline;
    std::string inputBuffer;
    boost::system::error_code boostErr;
    Wave* w;

    void startAccept();
    void handleAccept(const std::error_code& err);
    void startRead();
    void handleRead(const boost::system::error_code& boostErr, std::size_t n);
    void writeMessage(std::string str);
    void checkDeadline();
};