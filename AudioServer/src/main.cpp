#include "server.h"

int main()
{
    try
    {
        boost::asio::io_context ioContext;
        Server s(ioContext);
        s.start();
        ioContext.run();
    }
    catch(std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}