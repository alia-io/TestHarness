/////////////////////////////////////////////////////////////////////
// Logger.cpp - log text messages to std::ostream                  //
// ver 1.0                                                         //
//-----------------------------------------------------------------//
// Jim Fawcett (c) copyright 2015                                  //
// All rights granted provided this copyright notice is retained   //
//-----------------------------------------------------------------//
// Language:    C++, Visual Studio 2015                            //
// Application: Several Projects, CSE687 - Object Oriented Design  //
// Author:      Jim Fawcett, Syracuse University, CST 4-187        //
//              jfawcett@twcny.rr.com                              //
/////////////////////////////////////////////////////////////////////

#include <functional>
#include "StaticLogger.h"
#include "Utilities.h"

Logger::Logger() : logLevel{ LOG_LEVEL::info } { }
void Logger::setLogLevel(LOG_LEVEL log) { logLevel = log; }

//----< attach logger to existing std::ostream >---------------------
void Logger::attach(std::ostream* pOut) { _pOut = pOut; }

//----< send text message to std::ostream >--------------------------
void Logger::write(const LogMsg msg) {
    if (_ThreadRunning)
        _queue.enQ(msg);
}

//----< start logging >----------------------------------------------
void Logger::start() {
    if (_ThreadRunning) return;
    _ThreadRunning = true;
    std::function<void()> tp = [=]() {
        while (true) {
            LogMsg msg = _queue.deQ();
            if (msg.text == "quit") {
                _ThreadRunning = false;
                break;
            }
            HANDLE hConsole;
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);		//retrieve handle for std ouput device
            switch (msg.outputType) {
            case OUTPUT_TYPE::system:
                SetConsoleTextAttribute(hConsole, 9);
                *_pOut << " [SYSTEM] ";
                break;
            case OUTPUT_TYPE::summary:
                SetConsoleTextAttribute(hConsole, 9);
                *_pOut << "\n [TEST RESULT SUMMARY] ";
                break;
            case OUTPUT_TYPE::positive:
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                *_pOut << "\n [PASS] ";
                break;
            case OUTPUT_TYPE::negative:
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                *_pOut << "\n [FAIL] ";
                break;
            case OUTPUT_TYPE::neutral:
                SetConsoleTextAttribute(hConsole, 14);
                *_pOut << "\n [EXCEPTION] ";
            }
            // 3,9 = light blue
            // 5, 13 = red-violet
            // 6 = golden
            SetConsoleTextAttribute(hConsole, 15);
            *_pOut << msg.text << "\n";
        }
    };
    std::thread thr(tp);
    thr.detach();
}

//----< stop logging >-----------------------------------------------
void Logger::stop(const LogMsg msg) {
    if (_ThreadRunning) {
        if (msg.text != "") write(msg);
        LogMsg quitMsg{};
        quitMsg.outputType = OUTPUT_TYPE::system;
        quitMsg.text = "quit";
        write(quitMsg);  // request thread to stop
        while (_ThreadRunning)
            /* wait for thread to stop*/
            ;
    }
}

//----< stop logging thread >----------------------------------------
Logger::~Logger() {
    LogMsg msg{};
    msg.outputType = OUTPUT_TYPE::system;
    msg.text = "";
    stop(msg);
}

LOG_LEVEL Logger::getLogLevel() { return logLevel; }

//--------------< test stub >--------------------

#ifdef TEST_LOGGER

int main() {
    Logger log;
    log.attach(&std::cout);
    log.write("\n  won't get logged - not started yet");
    log.start();
    log.title("Testing Logger Class", '=');
    log.write("\n  one");
    log.write("\n  two");
    log.write("\n  fini");
    log.stop();
    log.write("\n  won't get logged - stopped");
    log.start();
    log.write("\n  starting again");
    log.write("\n  and stopping again");
    log.stop("\n  terminating now");

    StaticLogger<1>::attach(&std::cout);
    StaticLogger<1>::start();
    StaticLogger<1>::write("\n");
    StaticLogger<1>::title("Testing StaticLogger class");
    StaticLogger<1>::write("\n  static logger at work");
    Logger& logger = StaticLogger<1>::instance();
    logger.write("\n  static logger still at work");
    logger.stop("\n  stopping static logger");
}

#endif
