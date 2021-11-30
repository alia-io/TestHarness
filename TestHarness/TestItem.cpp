#include "TestItem.h"

TestItem::TestItem(std::string testName, bool (*testPtr)()) : name { testName }, pointer{ testPtr } { }

std::string TestItem::getName() { return name; }

