//
// Created by danie on 03.07.2020.
//

#include "LogLevel.h"

std::string const & toString(LogLevel l)
{
    switch (l)
    {
        case LogLevel::ERROR: return toString<LogLevel::ERROR>();
        case LogLevel::WARNING: return toString<LogLevel::WARNING>();
        case LogLevel::INFO: return toString<LogLevel::INFO>();
        case LogLevel::DEBUG: return toString<LogLevel::DEBUG>();
        default: return "UNKNOWN LOG LEVEL";
    }
}