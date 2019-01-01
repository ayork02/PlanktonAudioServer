#include "server.h"

Server::Server(boost::asio::io_context& io_context)
    : socket(io_context), acceptor(io_context, tcp::endpoint(tcp::v4(), 5005)), deadline(io_context)
{
    
}

Server::~Server()
{
    socket.close();
}

void Server::start()
{
    startAccept();
    deadline.async_wait(std::bind(&Server::checkDeadline, this));
}

void Server::stop()
{
    stopped = true;
    socket.close();
    deadline.cancel();
}

void Server::startAccept()
{
    acceptor.async_accept(socket, std::bind(&Server::handleAccept, this, std::placeholders::_1));
}

void Server::handleAccept(const std::error_code& err)
{
    if(stopped)
    {
        return;
    }
    if(err)
    {
        std::cerr << "Error Connecting to Client: " << err.message() << std::endl;
        socket.close();
        startAccept();
    }
    else
    {
        std::cout << "Connected to: " << socket.remote_endpoint().address().to_string() << std::endl;
        startRead();
    }
}

void Server::startRead()
{
    deadline.expires_after(std::chrono::seconds(30));
    boost::asio::async_read_until(socket, boost::asio::dynamic_buffer(inputBuffer), '\n', 
        std::bind(&Server::handleRead, this, std::placeholders::_1, std::placeholders::_2));
}

void Server::handleRead(const std::error_code& err, std::size_t n)
{
    if(stopped)
    {
        return;
    }
    if(!err)
    {
        std::string line(inputBuffer.substr(0, n-1));
        inputBuffer.erase(0, n);
        std::cout << "Received Message: " << line << std::endl;
        if(line.find("/") != std::string::npos && !audioInit) //FIXME!!: Not cross platform
        {
            if(line.find("||") != std::string::npos)
            {
                size_t pos_end = line.find("||", 0);
                std::string path = line.substr(0, pos_end);
                w = new Wave(path.c_str());
                std::string timeStart = line.substr(pos_end + 2, line.length());
                w->play(static_cast<unsigned short>(std::stoul(timeStart, nullptr, 0)));
            }
            else
            {
                w = new Wave(line.c_str());
                w->play();
            }
            audioInit = true;
        }
        if(line == "time" && audioInit)
        {
            std::cout << w->getTime() << std::endl;
        };
        if(line == "stop" && audioInit)
        {
            audioInit = false; 
        }
        startRead();
    }
    else if(err.value() == 2) //FIXME!!: Not cross platform
    {
        std::cout << "Client Disconnected" << std::endl;
        socket.close();
        deadline.expires_at(steady_timer::time_point::max());
        startAccept();
    }
    else
    {
        std::cerr << "Error Receiving Message: " << err.message() << std::endl;
        stop();
    }
}

void Server::writeMessage(std::string str)
{
    boost::system::error_code boostErr;
    boost::asio::write(socket, boost::asio::buffer(str), boostErr);
    if(boostErr)
    {
        std::cerr << "Error Writing Message: " << boostErr.message() << std::endl;
        stop();
    }
}

void Server::checkDeadline()
{
    if(stopped)
    {
        return;
    }
    if(deadline.expiry() <= steady_timer::clock_type::now())
    {
        socket.close();
        deadline.expires_at(steady_timer::time_point::max());
        startAccept();
    }
    deadline.async_wait(std::bind(&Server::checkDeadline, this));
}






