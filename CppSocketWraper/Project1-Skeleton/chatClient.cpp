#include <iostream> 
#include "tcpClientSocket.h"
#include <algorithm>

using namespace std; 

int main(int argc, char ** argv)
{
    
    string command;
    cout << "Starting client example" <<endl; 
    string serverIP(argv[1]);
    string username = argv[2];
    int port = atoi(argv[3]); 

    cs457::tcpClientSocket clientSocket(serverIP,port);
    int val = clientSocket.connectSocket(); 
    cout << "Client Socket Value after connect = " << val << endl; 

    clientSocket.sendString("Hello Server. How are you? ",false); 
    while(cin){
        string command;
        cout << "enter command: ";
        cin >> command;
        clientSocket.sendString(transform(command.begin(), command.end(),command.begin(), ::toupper), false);
    }

    string msg;
    ssize_t v;
    tie(msg,v) =  clientSocket.recvString(4096,false);
    cout << "server said: " << msg << endl;

    cout << "Client will try to exit now" <<endl;

    clientSocket.sendString("EXIT",false); 

    tie(msg,v) =  clientSocket.recvString(4096,false);
    cout << "server said: " << msg << endl;

    clientSocket.closeSocket(); 
    
    return 0; 
}