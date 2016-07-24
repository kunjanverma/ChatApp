#include <TcpSocket.h>

namespace ServerUtils
{

TcpSocket::TcpSocket(int port, unsigned long address, const short family):Socket(AF_INET, SOCK_STREAM, 0, port, address, family)
{
}

int TcpSocket::acceptConnections(SockAddr &cliAddr)
{
    try
    {
        if ( !isServerSocket() )
        {
            throw Exception("Not a server socket. Only server can accept connections");
        }
        else
        {
            size_t addr_len = sizeof(struct sockaddr_in);
            int fd = accept(getFD(), (struct sockaddr *)&(cliAddr.getC_SockAddr()),(socklen_t*)&addr_len);
            return fd;
        }
    }
    catch(std::exception &e)
    {
        std::cerr << e.what();
        throw;
    }
}

}
