#pragma once

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <string>
#include <iostream>

using namespace boost::asio;
using ip::tcp;

class Client
{
private:
    boost::asio::io_context io_context;
    tcp::socket socket;
    boost::system::error_code boostErr;
public:
    Client(std::string ipAddress, unsigned short port = 5005);
    ~Client();
    void sendMessage(const std::string msg);
};