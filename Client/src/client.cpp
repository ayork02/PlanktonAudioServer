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

int main()
{
    Client c("10.0.0.18");
    c.play("/home/yorka/Documents/Productions/AddamsFamily/Music/12-Waiting.wav", 20);
    boost::this_thread::sleep(boost::posix_time::seconds(5));
    std::cout << c.timecode() << std::endl;
    boost::this_thread::sleep(boost::posix_time::seconds(5));
    c.stop();
    // c.timecode();
    // c.sendMessage("stop");
    // c.sendMessage("/home/yorka/Documents/Productions/AddamsFamily/Music/12-Waiting.wav||30");
    // boost::this_thread::sleep(boost::posix_time::seconds(5));
    // c.sendMessage("time");
    // c.sendMessage("stop");
    return 0;
}