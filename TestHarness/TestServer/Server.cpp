/////////////////////////////////////////////////////////////////////////
// StringServer.cpp - Demonstrates simple one-way string messaging     //
//                                                                     //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2016           //
// Application: OOD Project #4                                         //
// Platform:    Visual Studio 2015, Dell XPS 8900, Windows 10 pro      //
/////////////////////////////////////////////////////////////////////////
/*
* This package implements a server that receives string messages
* from multiple concurrent clients and simply displays them.
*
* It's purpose is to provide a very simple illustration of how to use
* the Socket Package provided for Project #4.
*/
/*
* Required Files:
*   StringClient.cpp, StringServer.cpp
*   Sockets.h, Sockets.cpp, Cppll-BlockingQueue.h
*   Logger.h, Logger.cpp, Cpp11-BlockingQueue.h
*   Utilities.h, Utilities.cpp
*/
#include "Server.h"
#include "Sockets.h"
#include "StaticLogger.h"
#include <string>
#include <iostream>

using namespace Sockets;

const IP_VERSION Server::ipVersion = IP_VERSION::IPv6;
const std::string Server::ipAddress = "localhost";
const size_t Server::portNumber = 8080;

class ConnectionHandler
{
public:
    void operator()(Socket& socket_);
};

void ConnectionHandler::operator()(Socket& socket_) {

    ::Sleep(1000);    // make sure client listener is started

    SocketConnecter si;
    while (!si.connect("localhost", 9090)) {
        StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, "Server waiting to connect" });
        ::Sleep(100);
    }

    while (true) {
        std::string msg = Socket::removeTerminator(socket_.recvString());
        StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, "Recvd message: " + msg });
        if (msg == "quit") break;
        std::string response = "I got your message. It said " + msg + ".";
        si.sendString(response);
        StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, "Server sent msg: " + response });
    }

    si.sendString("quit");
    StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, "Server sent msg: quit" });
    StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, "Connection terminated." });

}

//----< test stub >--------------------------------------------------

int main() {
    StaticLogger<1>::attach(&std::cout);
    StaticLogger<1>::start();
    StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, "Server started" });
    try {
        SocketSystem ss;
        SocketListener sl(8080, IP_VERSION::IPv6);
        ConnectionHandler cp;
        sl.start(cp);
        std::cout.flush();
        std::cin.get();
    }
    catch (std::exception& exc) {
        StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, "\n  Exeception caught: " });
        std::string exMsg = "\n  " + std::string(exc.what()) + "\n\n";
        StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, exMsg });
    }
}