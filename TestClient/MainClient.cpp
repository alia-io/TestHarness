/////////////////////////////////////////////////////////////////////
// Comm.h - message-passing communication facility                 //
//                                                                 //
// Jim Fawcett, CSE687-OnLine Object Oriented Design, Fall 2017    //
/////////////////////////////////////////////////////////////////////

#include "MainClient.h"
#include "StaticLogger.h"
#include "Utilities.h"
#include "TestBlockingQueue.h"
#include "TestMessage.h"
#include <iostream>
#include <functional>

using namespace MsgPassingCommunication;
using namespace Sockets;

Receiver::Receiver(IP_VERSION ipVer, std::string ipAddr, size_t port) : address{ ipVer, ipAddr, port }, listener(port) {
    StaticLogger<1>::write("starting Receiver");
}

TestBlockingQueue<TestMessage>& Receiver::queue() {
    return rcvQ;
}

template<typename CallableObject>
void Receiver::start(CallableObject& co) {
    listener.start(co);
}

void Receiver::stop() { }

TestMessage Receiver::getMessage() {
    return rcvQ.deQ();
}

Sender::Sender(IP_VERSION ipVer, std::string ipAddr, size_t port) : address{ ipVer, ipAddr, port } { }

Sender::~Sender() {
    if (sendThread.joinable())
        sendThread.join();
}

void Sender::start() {
    std::function <void()> threadProc = [&]() {
        TestMessage msg = sndQ.deQ();
        std::string msgStr = msg.toString();
        StaticLogger<1>::write("\n  send thread dequeued message: " + msgStr);
        if (msg.getMessageBody() == "quit")
        {
            StaticLogger<1>::write("\n  send thread shutting down");
            return;
        }
        StaticLogger<1>::write("\n  sending " + Utilities::Converter<size_t>::toString(msgStr.length()));
        bool sendRslt = connecter.send(msgStr.length(), (Socket::byte*)msgStr.c_str());
    };
    std::thread t(threadProc);
    sendThread = std::move(t);
}

void Sender::stop() {
    TestMessage msg{ address.getVersion(), address.getIp(), address.getPort(), IP_VERSION::IPV4, "server", 8080, MESSAGE_TYPE::request, "TestClient", "quit"};
    //msg. = "quit";
    postMessage(msg);
    connecter.shutDown();
}

bool Sender::connect(ServerAddress sa) {
    return connecter.connect(sa.getIp(), sa.getPort());
}

void Sender::postMessage(TestMessage& msg) {
    sndQ.enQ(msg);
}

bool Sender::sendFile(const std::string& fileName)
{
    return false;
}

class ClientHandler
{
public:
    ClientHandler(TestBlockingQueue<TestMessage>& q) : q_(q) {
        StaticLogger<1>::write("\n  starting ClientHandler");
    }
    ~ClientHandler() { std::cout << "\n  ClientHandler destroyed;"; }

    std::string readMsg(Socket& socket)
    {
        std::string temp, msgString;
        while (socket.validState())
        {
            temp = socket.recvString('\n');
            msgString += temp;
            StaticLogger<1>::write("--" + temp);
            if (temp.length() < 2)
                break;
        }
        return msgString;
    }
    void operator()(Socket socket)
    {
        while (socket.validState())
        {
            std::string msgString = readMsg(socket);
            Message msg = Message::fromString(msgString);
            StaticLogger<1>::write("read message from rcvr's socket: " + msg.toString());
            q_.enQ(msg);
            std::cout << msgString;
            if (msg.body == "quit")
                break;
        }
    }
private:
    BlockingQueue<Message>& q_;
};

int main() {

    int numTests = 10;
    std::string testListStr = "{ \"count\": 10, ";
    testListStr += "\"tests\": [ \"BasicCalculatorTestDriverPassScenario\", ";
    testListStr += "\"BasicCalculatorTestDriverFailScenario\", ";
    testListStr += "\"BasicCalculatorTestDriverExceptionScenario\", ";
    testListStr += "\"AdvCalculatorTestDriverPassScenario\", ";
    testListStr += "\"MemoryAllocatorTestDriverExceptionScenario1\", ";
    testListStr += "\"MemoryAllocatorTestDriverExceptionScenario2\", ";
    testListStr += "\"ContainerConversionsTestDriverFailScenario\", ";
    testListStr += "\"ContainerConversionsTestDriverExceptionScenario\", ";
    testListStr += "\"LengthErrorTestDriverExceptionScenario\", ";
    testListStr += "\"OverflowErrorTestDriverExceptionScenario\" ] }";

    Show::attach(&std::cout);
    Show::start();

    std::thread sendThread([=] {
        Show::title("Starting Client on thread " + Utilities::Converter<std::thread::id>::toString(std::this_thread::get_id()));
        try {
            SocketSystem ss;
            SocketConnecter si;
            while (!si.connect("localhost", 8080)) {
                Show::write("\n client waiting to connect");
                ::Sleep(100);
            }

            /*std::string msg;

            for (size_t i = 0; i < NumMessages; ++i)
            {
                msg = "message #" + Converter<size_t>::toString(i + 1) + " from client" + myCountString;
                si.sendString(msg);
                Show::write("\n  client" + myCountString + " sent \"" + msg + "\"");
                ::Sleep(TimeBetweenMessages);
            }
            msg = "quit";*/

            si.sendString(testListStr);
            Show::write("\n  client sent \"" + testListStr + "\"");

            Show::write("\n");
            //Show::write("\n  All done folks");
        }
        catch (std::exception& exc)
        {
            Show::write("\n  Exeception caught: ");
            std::string exMsg = "\n  " + std::string(exc.what()) + "\n\n";
            Show::write(exMsg);
        }
    });
    
    std::cin.get();
    sendThread.join();

    //Show::title("Demonstrating two String Clients each running on a child thread");

    //StringClient c1;
    //std::thread t1(
    //    [&]() { c1.execute(100, 50); } // 50 messages 100 millisec apart
    //);

    //StringClient c2;
    //std::thread t2(
    //    [&]() { c2.execute(120, 50); } // 50 messages 120 millisec apart
    //);
    //t1.join();
    //t2.join();
}