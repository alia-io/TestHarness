#pragma once
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
#include "..\TestSuite\Sockets.h"
#include "..\TestSuite\StaticLogger.h"
#include "..\TestSuite\Utilities.h"
#include "..\TestSuite\TestMessage.h"
#include "..\TestSuite\TestMessageParser.h"
#include <string>
#include <iostream>
#include <thread>
#include <list>

using Show = StaticLogger<1>;
using namespace Utilities;
using namespace Sockets;
using namespace TestSuite;

class ConnectionHandler
{
public:
    void operator()(Socket& socket_);
};

class MainClient {
public:
    void runClient(std::list<std::string> tests);
};