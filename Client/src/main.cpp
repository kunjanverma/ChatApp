#include <Client.h>

using namespace ChatClient;

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        std::cout<<"Usage ./Client <ip_address> <port>";
    }

	try
	{
		int port = std::stoi(argv[2]);
		Client client(argv[1], port);
		client.Start();
	}
	catch(...)
	{
	}
}
