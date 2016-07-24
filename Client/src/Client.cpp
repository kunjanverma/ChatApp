#include <Client.h>
#include <arpa/inet.h>
#include <limits>

namespace ChatClient
{
    Client::Client(const std::string &ip_addr, int port)
    {
        m_servSock = new ServerUtils::TcpSocket(port, inet_addr( ip_addr.c_str() ));
    }

    void Client::Start()
    {
        //Connect to remote server
        m_servSock->Connect();
        std::cout << "Connected to server\n";
        
        std::thread(&Client::HandleDataReceived,this).detach();
        m_dataSendThread = std::thread(&Client::SendData,this);

        m_dataSendThread.join();
    }

    void Client::HandleDataReceived()
    {
        std::string peer_reply;

        while(1)
        {
            m_servSock->recvData(peer_reply);
            std::cout<< peer_reply <<std::endl;
        }
    }

    void Client::SendData()
    {
        std::string input;
        while(1)
        {
            std::getline(std::cin, input);
            m_servSock->sendData(input);
            if("!quit" == input)
            {
                break;
            }
            input.clear();
        }
    }
}
