#include "MainClient.h"

void ConnectionHandler::operator()(Socket& socket_) {
    while (true) {
        std::string msg = Socket::removeTerminator(socket_.recvString());
        Show::write("\nrecvd message: " + msg);
        if (msg == "quit")
            break;
    }
}

void MainClient::runClient(std::list<std::string> tests) {
    
    Show::attach(&std::cout);
    Show::start();
    Show::title("\n  Client started");

    try {
        SocketSystem ss;
        
        std::thread listenThread([=] {
            SocketListener sl(9090, Socket::IP6);
            ConnectionHandler cp;
            sl.start(cp);
            Show::write("\n --------------------\n  press key to exit: \n --------------------");
            std::cout.flush();
            std::cin.get();
        });

        ::Sleep(1000);   // make sure server listener is started

        SocketConnecter si;
        while (!si.connect("localhost", 8080)) {
            Show::write("\n client waiting to connect");
            ::Sleep(100);
        }

        TestMessage requestMessage{ IP_VERSION::IPV6, "localhost", 9090, IP_VERSION::IPV6, "localhost", 8080,
            MESSAGE_TYPE::request_list, "TestClient", TestMessageParser::convertRequestListToJSONBody(tests) };
        std::string request = TestMessageParser::convertMessageToJSONString(requestMessage);
        si.sendString(request);
        Show::write("\n  client sent msg: " + request);

        ::Sleep(100);

        std::string msg = "quit";
        si.sendString(msg);
        Show::write("\n  client sent msg: " + msg);

        Show::write("\n\n  Connection terminated.");

        listenThread.join();
    }
    catch (std::exception& exc) {
        Show::write("\n  Exeception caught: ");
        std::string exMsg = "\n  " + std::string(exc.what()) + "\n\n";
        Show::write(exMsg);
    }
}