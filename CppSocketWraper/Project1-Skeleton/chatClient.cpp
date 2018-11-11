#include <iostream> 
#include "tcpClientSocket.h"
#include <algorithm>
#include <string>
#include <ctime>
#include <fstream>
using namespace std; 

void readHelpFile(string filePath){
    string line;
    ifstream file(filePath);
    if(file.is_open()){
        while(getline(file,line)){
            cout << line << "\n";
        }
    }
}


int main(int argc, char ** argv)
{
    
    string command;
    cout << "Starting client example" <<endl; 
    string serverIP(argv[1]);
    string username = argv[2];
    int port = atoi(argv[3]); 
    //string serverIP("127.0.0.1");
    //string username = "ben";
    //int port = 2000;

    cs457::tcpClientSocket clientSocket(serverIP,port);
    int val = clientSocket.connectSocket(); 
    cout << "Client Socket Value after connect = " << val << endl;
    clientSocket.sendString("-u " + username, false);

    //clientSocket.sendString("Hello Server. How are you? ",false); 
    while(cin){
        string command;
        cout << "enter command: ";
        cin >> command;
        if(command.substr(0,1) == "/"){
            transform(command.begin(),command.end(),command.begin(), ::toupper);
        }
        if (command == "/AWAY"){
            clientSocket.sendString(command,false);
            //todo set matching name in map to true if away or false if returning from away
            
        }
        if(command == "/ISON"){
            clientSocket.sendString(command, false);
            string ison;
            ssize_t c;
            tie(ison,c) = clientSocket.recvString(4096,false);
            cout << ison << '\n';
        }
        if(command == "/PING"){
            clock_t start;
            start = clock();
            clientSocket.sendString(command, false);
            string pong;
            ssize_t c;
            tie(pong, c) = clientSocket.recvString(4096,false);
            double timer = (clock() - start) / (double) CLOCKS_PER_SEC;
            cout << "server has replied : " << pong << "\n" << "Server response time: " << timer << "\n";           
        }if(command == "/HELP"){
            clientSocket.sendString(command, false);
            string help;
            ssize_t c;
            tie(help, c) = clientSocket.recvString(4096,false);
            readHelpFile(help);
        }if(command == "/TIME"){
            clientSocket.sendString(command, false);
            string serverTime;
            ssize_t c;
            tie(serverTime, c) = clientSocket.recvString(4096,false);
            cout << serverTime << '\n';
        }
        
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