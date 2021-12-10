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
#include "Sockets.h"
#include "StaticLogger.h"
#include "Utilities.h"
#include <string>
#include <iostream>

using namespace Sockets;
using Show = StaticLogger<1>;

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

//----< test stub >--------------------------------------------------

int main()
{
    Show::attach(&std::cout);
    Show::start();
    Show::title("\n  Server started");
    try
    {
        SocketSystem ss;
        SocketListener sl(8080, Socket::IP6);
        ConnectionHandler cp;
        sl.start(cp);
        Show::write("\n --------------------\n  press key to exit: \n --------------------");
        std::cout.flush();
        std::cin.get();
    }
    catch (std::exception& exc)
    {
        Show::write("\n  Exeception caught: ");
        std::string exMsg = "\n  " + std::string(exc.what()) + "\n\n";
        Show::write(exMsg);
    }
}