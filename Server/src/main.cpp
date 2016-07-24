#include<Server.h>

using namespace ChatServer;

int main(int argc, char*argv[])
{
    if(argc < 2)
    {
        std::cout<<"Usage ./Server <port>";
    }

    try
    {
        Server server(std::stoi(argv[1]));
        server.waitForClientConn();
    }
    catch(const std::invalid_argument& arg_error)
    {
        std::cerr << arg_error.what() << '\n';
    }
    catch(...)
    {
    }
    return 0;
}
