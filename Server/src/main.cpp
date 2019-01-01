#include "server.h"

int main()
{
    try
    {
        boost::asio::io_context io_context;
        Server s(io_context);
        s.start();
        io_context.run();
    }
    catch(std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}