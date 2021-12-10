///////////////////////////////////////////////////////////////////////////
// Message.cpp - defines message structure used in communication channel //
//                                                                       //
// Jim Fawcett, CSE687-OnLine Object Oriented Design, Fall 2017          //
///////////////////////////////////////////////////////////////////////////

#include "Message.h"
#include <iostream>

using namespace MsgPassingCommunication;
using SUtils = Utilities::StringHelper;

std::string Message::toString()
{
    std::string out = "name: " + name;
    out += "\nto: " + to.toString();
    out += "\nfrom: " + from.toString();
    out += "\ncommand: " + command;
    out += "\nbody: " + body;
    out += "\n\n";
    return out;
}

std::string extractName(const std::string& attribute)
{
    size_t pos = attribute.find_first_of(':');
    if (pos == attribute.length())
        return "";
    std::string temp = attribute.substr(0, pos);
    return Utilities::StringHelper::trim(temp);
}

std::string extractValue(const std::string& attribute)
{
    size_t pos = attribute.find_first_of(':');
    if (pos == attribute.length())
        return "";
    std::string temp = attribute.substr(pos + 1, attribute.length() - pos);
    return Utilities::StringHelper::trim(temp);
}

Message Message::fromString(const std::string& src)
{
    Message msg;
    std::vector<std::string> splits = Utilities::StringHelper::split(src);
    if (splits.size() < 5)
        return msg;
    std::string temp = splits[0];
    msg.name = extractValue(temp);
    temp = splits[1];
    std::string value = extractValue(temp);
    msg.to.address = extractName(value);
    msg.to.port = Utilities::Converter<size_t>::toValue(extractValue(value));
    temp = splits[2];
    value = extractValue(temp);
    msg.from.address = extractName(value);
    msg.from.port = Utilities::Converter<size_t>::toValue(extractValue(value));
    temp = splits[3];
    msg.command = extractValue(splits[3]);
    temp = splits[4];
    msg.body = extractValue(splits[4]);
    return msg;
}
#ifdef TEST_MESSAGE

int main()
{
    SUtils::Title("Testing Message Class");

    SUtils::title("testing endpoints");
    EndPoint ep("localhost", 8080);
    std::cout << "\n  address = " << ep.address;
    std::cout << "\n  port = " << ep.port;
    std::string epStr = ep.toString();
    std::cout << "\n  " << epStr;

    EndPoint newEp = EndPoint::fromString(epStr);
    std::cout << "\n  " << newEp.toString();
    Utilities::putline();

    SUtils::title("testing messages");
    Utilities::putline();

    SUtils::title("testing toString()");
    Message msg;
    msg.name = "test message";
    msg.to = ep;
    msg.from = ep;
    msg.command = "some command";
    msg.body = "some important stuff";
    std::cout << msg.toString() << "\n";

    SUtils::title("testing fromString");
    Message newMsg = Message::fromString(msg.toString());
    std::cout << newMsg.toString();
    std::cout << "\n\n";
    return 0;
}
#endif
