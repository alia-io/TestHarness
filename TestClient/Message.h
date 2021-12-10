#pragma once
/////////////////////////////////////////////////////////////////////////
// Message.h - defines message structure used in communication channel //
//                                                                     //
// Jim Fawcett, CSE687-OnLine Object Oriented Design, Fall 2017        //
/////////////////////////////////////////////////////////////////////////

#include "Utilities.h"
#include <string>
#include <vector>

namespace MsgPassingCommunication
{
    struct EndPoint
    {
        using Address = std::string;
        using Port = size_t;
        Address address;
        Port port;
        EndPoint(Address anAddress = "", Port aPort = 0);
        std::string toString();
        static EndPoint fromString(const std::string& str);
    };

    inline EndPoint::EndPoint(Address anAddress, Port aPort) : address(anAddress), port(aPort) {}

    inline std::string EndPoint::toString()
    {
        return address + ":" + Utilities::Converter<size_t>::toString(port);
    }

    inline EndPoint EndPoint::fromString(const std::string& str)
    {
        EndPoint ep;
        size_t pos = str.find_first_of(':');
        if (pos == str.length())
            return ep;
        ep.address = str.substr(0, pos);
        std::string portStr = str.substr(pos + 1);
        ep.port = Utilities::Converter<size_t>::toValue(portStr);
        return ep;
    }

    class Message
    {
    public:
        using Name = std::string;
        using Command = std::string;
        using Body = std::string;

        Name name;
        EndPoint to;
        EndPoint from;
        Body body;
        Command command;
        std::string toString();
        static Message fromString(const std::string& src);
    };
}