#pragma once
#ifndef LOGGER_H
#define LOGGER_H
/////////////////////////////////////////////////////////////////////
// Logger.h - log text messages to std::ostream                    //
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
/*
* Package Operations:
* -------------------
* This package supports logging for multiple concurrent clients to a
* single std::ostream.  It does this be enqueuing messages in a
* blocking queue and dequeuing with a single thread that writes to
* the std::ostream.
*
* Build Process:
* --------------
* Required Files: Logger.h, Logger.cpp, Utilities.h, Utilities.cpp
*
* Build Command: devenv logger.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 1.0 : 22 Feb 2016
* - first release
*
* Planned Additions and Changes:
* ------------------------------
* - none yet
*/

//////////////////////////////////////////////////////
// TestLogger.h										//
// CSE 681: Object Oriented Design					//
// Santhosh Srinivasan, Jiawen Zhen, Alifa Stith	//
//////////////////////////////////////////////////////

/*
*
* This class is retrieve the logLevel and print the exception messages to a file.
* This class also includes a function for summarizing the test results into a pass/failed section
*
*/

#include <iostream>
#include <string>
#include <thread>
#include <string>
#include <Windows.h>
#include <iomanip>
#include "BlockingQueue.h"
#include "Message.h"
#include "TestResultCounter.h"

using namespace TestMessenger;

enum class LOG_LEVEL { info, debug, detail };
enum class OUTPUT_TYPE { system, positive, negative, error, summary };

class LogMsg {
private:
	OUTPUT_TYPE outputType;
	std::string text = "";
	friend class Logger;
public:
	LogMsg() : outputType{ OUTPUT_TYPE::system }, text{ "" } { }
	LogMsg(OUTPUT_TYPE ot, std::string t) : outputType{ ot }, text{ t } { }
};

class Logger {
private:
	LOG_LEVEL logLevel;
	std::thread* _pThr;
	std::ostream* _pOut;
	BlockingQueue<LogMsg> _queue;
	bool _ThreadRunning = false;
public:
	Logger();
	Logger(const Logger&) = delete;
	~Logger();
	Logger& operator=(const Logger&) = delete;
	void attach(std::ostream* pOut);
	void write(const LogMsg msg);
	void start();
	void stop(const LogMsg msg);
	LOG_LEVEL getLogLevel();
	void setLogLevel(LOG_LEVEL log);
};

template<int i>
class StaticLogger {
private:
	static Logger _logger;
public:
	StaticLogger(const StaticLogger&) = delete;
	StaticLogger& operator=(const StaticLogger&) = delete;
	static Logger& instance() { return _logger; }
	static void attach(std::ostream* pOut) { _logger.attach(pOut); }
	static void write(const LogMsg& msg) { _logger.write(msg); }
	static void start() { _logger.start(); }
	static void stop(const LogMsg& msg = "") { _logger.stop(msg); }
	static LOG_LEVEL getLogLevel() { return _logger.getLogLevel(); }
	static void setLogLevel(LOG_LEVEL log) { _logger.setLogLevel(log); }
};

template<int i>
Logger StaticLogger<i>::_logger;

#endif
