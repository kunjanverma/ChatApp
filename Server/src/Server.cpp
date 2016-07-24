#include<Server.h>
#include<cstring>
#include<algorithm>

namespace ChatServer
{

std::mutex clientDataMtx;

Server::Server(int port):m_numClients(0)
{
    try
    {
        m_servSock = new ServerUtils::TcpSocket(port);
        m_servSock->isServerSocket() = true;
    }
    catch(std::exception &e)
    {
    }
}

void Server::waitForClientConn()
{
    try
    {
        m_servSock->Bind();
        m_servSock->Listen();
    
        while(true)
        {
            ClientData clientData;
            clientData.m_clientSocket.getFD() = dynamic_cast<ServerUtils::TcpSocket*>(m_servSock)->acceptConnections
                                                (clientData.m_clientSocket.getSockAddr());
            m_numClients++;
            clientDataMtx.lock();
            clientData.m_ClientNum = m_numClients;
            m_clientData.push_back(clientData);
            std::thread(&Server::handleConnectedClient,this).detach(); // Handle each client send recieve in a separate thread 
            clientDataMtx.unlock();
        }
    }
    catch(std::exception &e)
    {
    }
}

void Server::handleConnectedClient()
{
    clientDataMtx.lock();
    ClientData &client = m_clientData.back();
    std::string client_message;
    client_message.resize(2000);

    try
    {
        std::string message = "Greetings from server\n";
        client.m_clientSocket.sendData(message);

        client.m_clientSocket.recvData(client_message);

        while(true)
        {
            if ( client_message.front() != ':' )
            {
                message = "Wrong msg format, return\n";
                client.m_clientSocket.sendData(message);
            }
            else if ( m_clientData.end() != std::find_if(m_clientData.begin(), m_clientData.end(), 
                                            [&](const ClientData &client_data){ return client_message.substr(1) == client_data.m_name; }) )
            {
                message = "This client name already exists, choose a different name\n";
                send(client.m_clientSocket.getFD(), message.c_str(), message.size(), 0);
            }
            else
            {
                break;
            }

            client.m_clientSocket.recvData(client_message);
        }

        client.m_isConnected = true;
        client.m_name = client_message.substr(1);

        clientDataMtx.unlock();

        //Receive a message from client
        while(true)
        {
            client.m_clientSocket.recvData(client_message);
            if( client_message == "!quit" )
            {
                message = std::string("server:Bye\n");;
                client.m_clientSocket.sendData(message);
                break;
            }
            else
            {
                size_t pos = client_message.find(":");
                if(std::string::npos == pos)
                {
                    message = std::string("Wrong message format\n");;
                    client.m_clientSocket.sendData(message);
                    continue;
                }

                std::string client_name =  client_message.substr(0,pos);
                auto client_iter = std::find_if(m_clientData.begin(), m_clientData.end(), [&](const ClientData &client_data){ return client_name == client_data.m_name; });
                if ( m_clientData.end() == client_iter)
                {
                    message = std::string("server:Cannot send data to ") + client_name + ". No Such Client exists\n";
                    client.m_clientSocket.sendData(message);
                    continue;
                }
                else//Pass on the message to the peer
                {
                    client_iter->m_clientSocket.sendData(client_message);
                }
            }
        }
        m_clientData.erase( std::remove_if(m_clientData.begin(), m_clientData.end(), 
                            [&](const ClientData &client_data){return client_data.m_name == client.m_name;})
                            , m_clientData.end() );
    }
    catch(std::exception &e)
    {
    }
    catch(...)
    {
        std::cout<<"some exception thrown\n";
    }
}

}
