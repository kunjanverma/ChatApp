// Example program
#include <thread>
#include <mutex>
#include <TcpSocket.h>
#include <vector>

#define MAX_CONN = 100

#ifndef CHAT_SERVER
#define CHAT_SERVER

namespace ChatServer
{

extern std::mutex clientDataMtx;

struct ClientData
{
    ServerUtils::TcpSocket m_clientSocket;
    bool m_isConnected;
    std::string m_name;
    unsigned int m_ClientNum;
    
    ClientData():m_isConnected(false),m_ClientNum(0)
    {
    }
};

class Server
{
    std::vector<ClientData> m_clientData;
    ServerUtils::Socket *m_servSock;
    unsigned int m_numClients;
    
    public:
    Server(int port);

    void waitForClientConn();
    void handleConnectedClient();
};

}
#endif

