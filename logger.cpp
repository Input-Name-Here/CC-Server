#include <stdio.h>
#include <iostream>
#include <string>

#include "colour.h"
#include "logger.h"

void Logger::Log(LogLevel lvl, const char* msg)
{
    printf("%s %s %s\n", getColor(lvl), msg, RESET);
}
void Logger::sLog(LogLevel lvl, const std::string msg)
{
    printf("%s %s %s\n", getColor(lvl), msg.c_str(), RESET);
}


const char* Logger::getColor(LogLevel lvl)
{
    switch(lvl) {
        case LOG_DEBUG:
            return H_CYAN;
        case LOG_INFO:
            return WHITE;
        case LOG_WARNING:
            return YELLOW;
        case LOG_ERROR:
            return H_RED;
        case LOG_FATAL:
            return B_RED;
        default:
            return "";
    }
}