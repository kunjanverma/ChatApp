#include <Util_types.h>
#include <Util_exception.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <errno.h>
#include <arpa/inet.h>

#ifndef SERVER_SOCKET
#define SERVER_SOCKET

#define MAX_BUF_LENGTH 2000

namespace ServerUtils
{

class Socket
{
    SockFd m_fd;
    bool m_serverSocket;
        
    protected:
    SockAddr m_sockAddr;

    public:
        
        Socket(int domain, int type, int protocol, int port, unsigned long address, const short family):
               m_fd(-1), m_serverSocket(false),m_sockAddr(port, address, family)
        {
            try
            {
                if ( -1 == ( m_fd = socket(domain, type, protocol ) ) )
                {
                    throw ServerUtils::Exception("Socket create failed!");
                }
            }
            catch(std::exception &e)
            {
                std::cerr<<e.what();
                throw;
            }
        }

        bool& isServerSocket()
        {
            return m_serverSocket;
        }
        
        SockFd& getFD(){return m_fd;}

        SockAddr& getSockAddr()
        {
            return m_sockAddr;
        }

        void Bind()
        {
            try
            {
                if(isServerSocket())
                {
                    if( bind(m_fd, (struct sockaddr *)&(m_sockAddr.getC_SockAddr()), sizeof(struct sockaddr_in)) < 0 )
                    {
                        throw ServerUtils::Exception("Socket bind failed");
                    }
                }
                else
                {
                    throw ServerUtils::Exception("Cannot bind a client socket");
                }
            }
            catch(std::exception &e)
            {
                std::cerr<<e.what();
                throw;
            }
        }

        void Listen()
        {
            try
            {
                if(isServerSocket())
                {
                    listen(m_fd, SOCK_CONN_BACKLOG);
                }
                else
                {
                    throw ServerUtils::Exception("Cannot listen to a client socket");
                }
            }
            catch(std::exception &e)
            {
                std::cerr<<e.what();
                throw;
            }
        }
        
        void Connect()
        {
            try
            {
                if (connect(m_fd , (struct sockaddr *)&(m_sockAddr.getC_SockAddr()) , sizeof(struct sockaddr_in)) < 0)
                {
                    throw ServerUtils::Exception("Socket connect failed");
                }
            }
            catch(std::exception &e)
            {
                std::cerr<<e.what();
                throw;
            }
        }

        void recvData(std::string &msg)
        {
            try
            {
                msg.clear();
                msg.resize(MAX_BUF_LENGTH);
                int len=0;
                if( (len = recv(m_fd, &msg[0] , msg.size(), 0)) < 0 )
                {
                    std::cout<<"error is:"<<strerror(errno)<<std::endl;
                    throw ServerUtils::Exception("Failed to read data from socket");
                }
                msg.resize(len);
            }
            catch(std::exception &e)
            {
                std::cerr<<e.what();
                throw;
            }
        }

        void sendData(const std::string &msg)
        {
            try
            {
                if( send(m_fd, &msg[0], msg.size(), 0) < 0 )
                {
                    throw ServerUtils::Exception("Failed to send data");
                }
            }
            catch(std::exception &e)
            {
                std::cerr<<e.what();
                throw;
            }
        }

        virtual ~Socket(){}
};

}
#endif
