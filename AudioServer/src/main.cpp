#include "server.h"

int main()
{
    try
    {
        unsigned short i;
	    std::cout << "Please select a port (default 5005): ";
	    std::cin >> i;
        while(!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input, please select a valid port: ";
            std::cin >> i;
        }
        boost::asio::io_context ioContext;
        Server s(ioContext, i);
        s.start();
        ioContext.run();
    }
    catch(std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}