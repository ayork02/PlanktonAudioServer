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
    boost::asio::io_context ioContext;
    tcp::socket socket;
    boost::system::error_code boostErr;

    void sendMessage(const std::string msg);
    std::string readMessage();
public:
    Client(std::string ipAddress, unsigned short port = 5005);
    ~Client();
    
    void play(std::string filepath, unsigned short startPos = 0);
    void stop();
    void pause();
    void go();
    double timecode();
};