#include "Server.h"

int main(int argc, char* argv[])
{   
    if (argc != 4)
        return -1;
    while (true)
    {
        try
        {
            std::size_t num_threads = boost::lexical_cast<std::size_t>(argv[3]);
            Server server(argv[1], argv[2], num_threads);

            server.run();
        }
        catch (std::exception& e)
        {
            std::cerr << "exception: " << e.what() << "\n";
        }
    }

    return 0;
}