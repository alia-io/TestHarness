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
#include "CSockets.h"
#include "CStaticLogger.h"
#include "CUtilities.h"
#include <string>
#include <iostream>
#include <thread>

using Show = StaticLogger<1>;
using namespace Utilities;
using namespace Sockets;

class ConnectionHandler
{
public:
    void operator()(Socket& socket_);
};

void ConnectionHandler::operator()(Socket& socket_)
{
    while (true)
    {
        std::string msg = Socket::removeTerminator(socket_.recvString());
        Show::write("\nrecvd message: " + msg);
        if (msg == "quit")
            break;
    }
}

int main()
{
    Show::attach(&std::cout);

    std::thread listenThread([=] {
        Show::start();
        Show::title("\n  Client started");
        try {
            SocketSystem ss;
            SocketListener sl(9090, Socket::IP6);
            ConnectionHandler cp;
            sl.start(cp);
            Show::write("\n --------------------\n  press key to exit: \n --------------------");
            std::cout.flush();
            std::cin.get();
        } catch (std::exception& exc) {
            Show::write("\n  Exeception caught: ");
            std::string exMsg = "\n  " + std::string(exc.what()) + "\n\n";
            Show::write(exMsg);
        }
    });
    
    ::Sleep(1000);   // wait for server to start
    
    try {
        SocketSystem ss;
        SocketConnecter si;
        while (!si.connect("localhost", 8080)) {
            Show::write("\n client waiting to connect");
            ::Sleep(100);
        }

        std::string msg = "request_list";
        si.sendString(msg);
        Show::write("\n  client send msg: " + msg);

        ::Sleep(100);

        msg = "quit";
        si.sendString(msg);
        Show::write("\n  client sent msg: " + msg);

        Show::write("\n");
        Show::write("\n  All done folks");
    } catch (std::exception& exc) {
        Show::write("\n  Exeception caught: ");
        std::string exMsg = "\n  " + std::string(exc.what()) + "\n\n";
        Show::write(exMsg);
    }

    listenThread.join();
}