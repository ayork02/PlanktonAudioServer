#include "client.h"

Client::Client(std::string ipAddress, unsigned short port) // default 5005
    : socket(io_context)
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

int main()
{
    Client c("10.0.0.18");
    c.sendMessage("/home/yorka/Documents/Productions/AddamsFamily/Music/12-Waiting.wav||20");
    boost::this_thread::sleep(boost::posix_time::seconds(5));
    c.sendMessage("time");
    c.sendMessage("stop");
    c.sendMessage("/home/yorka/Documents/Productions/AddamsFamily/Music/12-Waiting.wav||30");
    boost::this_thread::sleep(boost::posix_time::seconds(5));
    c.sendMessage("time");
    c.sendMessage("stop");
    return 0;
}