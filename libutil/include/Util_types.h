#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef UTIL_TYPES
#define UTIL_TYPES

namespace ServerUtils
{

typedef int SockFd;
#define SOCK_CONN_BACKLOG 5
class SockAddr
{
    struct sockaddr_in m_addr;

    public:
    SockAddr(const unsigned short port, unsigned long address, const short family )
    {
        m_addr.sin_family = family;
        m_addr.sin_addr.s_addr = address;
        m_addr.sin_port = htons(port);
    }

    struct sockaddr_in& getC_SockAddr()
    {
        return m_addr;
    }
    
    unsigned long getAddr()
    {
        return m_addr.sin_addr.s_addr;
    }

    unsigned short& getPort()
    {
        return m_addr.sin_port;
    }
};

}
#endif

