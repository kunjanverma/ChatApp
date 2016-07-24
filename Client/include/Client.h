#include <thread>
#include <TcpSocket.h>

#ifndef CHAT_CLIENT
#define CHAT_CLIENT

namespace ChatClient
{
    class Client
    {
        std::thread m_dataSendThread;
        ServerUtils::Socket *m_servSock;

        public:
        
        Client(const std::string &ip_addr, int port);
        void Start();
        void HandleDataReceived();
        void SendData();
    };
}
#endif
