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
#include "Sockets.h"
#include "StaticLogger.h"
#include "Utilities.h"
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

/////////////////////////////////////////////////////////////////////
// ClientCounter creates a sequential number for each client
//
/*class ClientCounter
{
public:
    ClientCounter() { ++clientCount; }
    size_t count() { return clientCount; }
private:
    static size_t clientCount;
};

size_t ClientCounter::clientCount = 0;

/////////////////////////////////////////////////////////////////////
// StringClient class
// - was created as a class so more than one instance could be 
//   run on child thread
//
class StringClient
{
public:
    void execute(const size_t TimeBetweenMessages, const size_t NumMessages);
};

void StringClient::execute(const size_t TimeBetweenMessages, const size_t NumMessages)
{
    ClientCounter counter;
    size_t myCount = counter.count();
    std::string myCountString = Utilities::Converter<size_t>::toString(myCount);

    Show::attach(&std::cout);
    Show::start();

    Show::title(
        "Starting String client" + myCountString +
        " on thread " + Utilities::Converter<std::thread::id>::toString(std::this_thread::get_id())
    );
    try
    {
        SocketSystem ss;
        SocketConnecter si;
        while (!si.connect("localhost", 8080))
        {
            Show::write("\n client waiting to connect");
            ::Sleep(100);
        }

        std::string msg;

        for (size_t i = 0; i < NumMessages; ++i)
        {
            msg = "message #" + Converter<size_t>::toString(i + 1) + " from client" + myCountString;
            si.sendString(msg);
            Show::write("\n  client" + myCountString + " sent \"" + msg + "\"");
            ::Sleep(TimeBetweenMessages);
        }
        msg = "quit";
        si.sendString(msg);
        Show::write("\n  client sent \"" + msg + "\"");

        Show::write("\n");
        Show::write("\n  All done folks");
    }
    catch (std::exception& exc)
    {
        Show::write("\n  Exeception caught: ");
        std::string exMsg = "\n  " + std::string(exc.what()) + "\n\n";
        Show::write(exMsg);
    }
}*/

int main()
{
    Show::attach(&std::cout);
    Show::start();
    Show::title("\n  Client started");
    try
    {
        SocketSystem ss;
        SocketListener sl(9090, Socket::IP6);
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
    
    
    
    /*Show::title("Demonstrating two String Clients each running on a child thread");

    StringClient c1;
    std::thread t1(
        [&]() { c1.execute(100, 50); } // 50 messages 100 millisec apart
    );

    StringClient c2;
    std::thread t2(
        [&]() { c2.execute(120, 50); } // 50 messages 120 millisec apart
    );
    t1.join();
    t2.join();*/
}