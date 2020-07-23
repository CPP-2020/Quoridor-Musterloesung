#pragma once

#include <string>
#include <climits> // needed for INT_MAX (only for certain compiler maybe).

namespace ConsoleUtils
{
    int readInteger();
    long readLong();
    double readDouble();
    std::string readString();
    std::string readString(const std::string &message, int maxLength = INT_MAX);
    int safelyReadInteger(const std::string & message);
    int safelyReadInteger(const std::string & message, int min, int max);
}

