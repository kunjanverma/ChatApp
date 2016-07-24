#include <Socket.h>

#ifndef TCP_SOCKET
#define TCP_SOCKET

namespace ServerUtils
{

class TcpSocket:public Socket
{
    public:
    
    TcpSocket(int port=-1, unsigned long address = INADDR_ANY, const short family = AF_INET);
    int acceptConnections(SockAddr &cliAddr);
    
};

}
#endif
