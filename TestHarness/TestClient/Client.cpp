/////////////////////////////////////////////////////////////////////////
// StringClient.cpp - Demonstrates simple one-way string messaging     //
//                                                                     //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2016           //
// Application: OOD Project #4                                         //
// Platform:    Visual Studio 2015, Dell XPS 8900, Windows 10 pro      //
/////////////////////////////////////////////////////////////////////////
/*
 * This package implements a client that sends string messages
 * to a server that simply displays them.
 *
 * It's purpose is to provide a very simple illustration of how to use
 * the Socket Package provided for Project #4.
 */
 /*
  * Required Files:
  *   StringClient.cpp, StringServer.cpp
  *   Sockets.h, Sockets.cpp
  *   Logger.h, Logger.cpp, Cpp11-BlockingQueue.h
  *   Utilities.h, Utilities.cpp
  */
#include "Client.h"
#include "Sockets.h"
#include "StaticLogger.h"
#include <string>
#include <iostream>
#include <thread>

const IP_VERSION Client::ipVersion = IP_VERSION::IPv6;
const std::string Client::ipAddress = "localhost";
const size_t Client::portNumber = 9090;

using namespace Sockets;

class ConnectionHandler {
public:
    void operator()(Socket& socket_);
};

void ConnectionHandler::operator()(Socket& socket_) {
    while (true) {
        std::string msg = Socket::removeTerminator(socket_.recvString());
        StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, "Recvd message: " + msg });
        if (msg == "quit") break;
    }
}

int main() {

    StaticLogger<1>::attach(&std::cout);
    StaticLogger<1>::start();
    StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, "Client started" });

    try {
        SocketSystem ss;

        std::thread listenThread([=] {
            SocketListener sl(9090, IP_VERSION::IPv6);
            ConnectionHandler cp;
            sl.start(cp);
            std::cout.flush();
            std::cin.get();
            });

        ::Sleep(1000);   // make sure server listener is started

        SocketConnecter si;
        while (!si.connect("localhost", 8080)) {
            StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, "Client waiting to connect" });
            ::Sleep(100);
        }

        std::string msg = "request_list";
        si.sendString(msg);
        StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, "Client sent msg: " + msg });

        ::Sleep(100);

        msg = "quit";
        si.sendString(msg);
        StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, "Client sent msg: " + msg });

        StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, "Connection terminated." });

        listenThread.join();
    } catch (std::exception& exc) {
        StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, "Exeception caught: " + std::string(exc.what()) });
    }
}