#pragma once
/////////////////////////////////////////////////////////////////////
// Comm.h - message-passing communication facility                 //
//                                                                 //
// Jim Fawcett, CSE687-OnLine Object Oriented Design, Fall 2017    //
/////////////////////////////////////////////////////////////////////

#include "TestMessage.h"
#include "TestBlockingQueue.h"
#include "Sockets.h"
#include <string>
#include <thread>

using namespace Sockets;
using namespace TestSuite;

namespace MsgPassingCommunication
{
    class Receiver
    {
    public:
        Receiver(IP_VERSION ipVer, std::string ipAddr, size_t port);
        template<typename CallableObject>
        void start(CallableObject& co);
        void stop();
        TestMessage getMessage();
        TestBlockingQueue<TestMessage>& queue();
    private:
        /*static*/ TestBlockingQueue<TestMessage> rcvQ;
        SocketListener listener;
        ServerAddress address;
    };

    //BlockingQueue<Message> Receiver::rcvQ;

    class Sender
    {
    public:
        Sender(IP_VERSION ipVer, std::string ipAddr, size_t port);
        ~Sender();
        void start();
        void stop();
        bool connect(ServerAddress sa);
        void postMessage(TestMessage& msg);
        bool sendFile(const std::string& fileName);
    private:
        TestBlockingQueue<TestMessage> sndQ;
        SocketConnecter connecter;
        std::thread sendThread;
        ServerAddress address;
    };
}