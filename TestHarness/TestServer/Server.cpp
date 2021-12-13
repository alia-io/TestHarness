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
#include "TestHarness.h"
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

    ::Sleep(1000);    // wait to make sure client listener is started

    //std::vector<std::thread> threads{};

    //while (true) {
        std::string msg = Socket::removeTerminator(socket_.recvString());
        Message request{ msg };
        StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, "Recvd message: " + msg });
        //if (msg == "quit") break;
        //threads.push_back(std::thread([=] { Server::runTestHarness(request); }));
        //Server::runTestHarness(request);
        //std::string response = "I got your message. It said " + msg + ".";
        //si.sendString(response);
        //StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, "Server sent msg: " + response });


    //}

        SocketConnecter si;
        StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, "source IP address: " + request.sourceIpAddress() });
        StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, "source port: " + std::to_string(request.sourcePort()) });
        while (!si.connect(request.sourceIpAddress(), request.sourcePort())) {
            StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, "Server waiting to connect" });
            ::Sleep(100);
        }

        TestHarness testHarness{ "default", request };
        MessageHandler* handler = testHarness.getHandler();
        testHarness.execute();

        si.sendString("hello");

        while (true) {
            //if (numberOfTests >= 0) break;
            Message resultMsg = handler->dequeueTestResult();
            si.sendString(resultMsg.getJsonFormattedMessage());
            //numberOfTests--;
            StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, "Server sent msg: " + resultMsg.getJsonFormattedMessage() });
        }
    
    //for (auto& thr : threads) {
    //    if (thr.joinable()) thr.join();
    //}

    /*si.sendString("quit");
    StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, "Server sent msg: quit" });
    StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, "Connection terminated." });*/

}

void Server::runServer() {
    init();
    try {
        SocketSystem ss;
        startListener();
    }
    catch (std::exception& exc) {
        StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, "\n  Exeception caught: " });
        std::string exMsg = "\n  " + std::string(exc.what()) + "\n\n";
        StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, exMsg });
    }
}

void Server::init() {
    StaticLogger<1>::attach(&std::cout);
    StaticLogger<1>::start();
    StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, "Server started" });
}

void Server::startListener() {
    SocketListener sl(Server::portNumber, Server::ipVersion);
    ConnectionHandler cp;
    sl.start(cp);
    std::cout.flush();
    std::cin.get();
}

/* Open a new client channel and run TestHarness on the client request */
void Server::runTestHarness(Message requestMsg) {
    
    SocketConnecter si;             // connect to client
    while (!si.connect(requestMsg.sourceIpAddress(), requestMsg.sourcePort())) {
        StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, "Server waiting to connect" });
        ::Sleep(100);
    }

    int numberOfTests = requestMsg.getRequestMessageBody().testCount;
    TestHarness testHarness{ "default", requestMsg };
    MessageHandler* handler = testHarness.getHandler();
    testHarness.execute();

    while (true) {
        //if (numberOfTests >= 0) break;
        Message resultMsg = handler->dequeueTestResult();
        si.sendString(resultMsg.getJsonFormattedMessage());
        numberOfTests--;
    }

    //si.sendString("quit");
    //StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, "Server sent msg: quit" });
    //StaticLogger<1>::write(LogMsg{ OUTPUT_TYPE::system, "Connection terminated." });
}

int main() {
    Server::runServer();
}