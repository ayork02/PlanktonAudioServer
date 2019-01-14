#include "client.h"

Client::Client(std::string ipAddress, unsigned short port) // default port = 5005
    : socket(ioContext)
{
    socket.connect(tcp::endpoint(boost::asio::ip::address::from_string(ipAddress), port));
}

Client::~Client()
{
    socket.close();
}

void Client::sendMessage(const std::string msg)
{
    std::string output = msg;
    output.append("\n");
    boost::asio::write(socket, boost::asio::buffer(output), boostErr);
    if(boostErr)
    {
        std::cerr << "Error Sending Message: " << boostErr.message() << std::endl;
    }
}

void Client::play(std::string filepath, unsigned short startPos) // default startPos = 0
{
    if(startPos != 0)
    {
        filepath.append("||");
        filepath.append(std::to_string(startPos));
    }
    sendMessage(filepath);
}

void Client::stop()
{
    sendMessage("stop");
}

void Client::pause()
{
    sendMessage("pause");
}

void Client::go()
{
    sendMessage("go");
}

double Client::timecode()
{
    sendMessage("time");
    std::string input;
    boost::asio::read_until(socket, boost::asio::dynamic_buffer(input), '\n', boostErr);
    if(!boostErr)
    {
        std::string line(input.substr(0, input.length() - 1));
        return std::stod(line, nullptr);
    }
    else
    {
        std::cerr << "Error Reading Timecode: " << boostErr.message() << std::endl;
    }
}