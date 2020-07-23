//
// Created by danie on 03.07.2020.
//

#ifndef GAMEFIELDGRAPH_LOGLEVEL_H
#define GAMEFIELDGRAPH_LOGLEVEL_H

#include <array>
#include <string>

enum class LogLevel : short
{
    ERROR,
    WARNING,
    INFO,
    DEBUG
};
// Kind of const-time lookup table for log level names
static std::array<std::string, 4> logLevelStrings({"ERROR","WARNING","INFO","DEBUG"});
// Utility methods
template <LogLevel l>
std::string const & toString();
std::string const & toString(LogLevel l);

////////////////////////////
/// Implementation

template <LogLevel l>
std::string const & toString()
{
    return std::get<static_cast<size_t>(l)>(logLevelStrings);
}


#endif //GAMEFIELDGRAPH_LOGLEVEL_H
