#pragma once

#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <strings.h>
#include <string> 
#include <tuple> 
#include <unistd.h>
#include <memory> 
#include <mutex> 


namespace cs457
{
    using namespace std; 
    //an ideal solution is to create a socket and then either 
    //derive or create templates that handle the differences 
    //between a client and a socket. 
    //there are certain aspects that a client socket does not need 
    //such as listen and accept for example but the server does
    class tcpClientSocket
    {
    public:
        
        tcpClientSocket(string networkAddress, uint portNumber);
        //int bindSocket();
        int connectSocket();
        int closeSocket(); 
        std::tuple<string,ssize_t> recvString(int bufferSize=4096,bool useMutex = true);
        ssize_t sendString(const string & data,bool useMutex = true);
        
    private: 
        void init();
        void setSocketOptions();
        uint port; 
        string address; 
        
     
        //
        int clientSocket;
        
        struct sockaddr_in serverAddress; 

        //do I need this? 
        struct in_addr addr;

        //        
        mutex sendMutex;
        mutex recvMutex; 
        
    };


}

