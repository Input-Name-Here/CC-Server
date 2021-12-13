#include <stdio.h>
#include <iostream>

#include "colour.h"


void Log::alert(std::string msg)
{
    std::cout << B_RED << BLINK << WHITE;
    std::cout << msg << RESET << std::endl;
}
void Log::error(std::string msg)
{
    std::cout << RED;
    std::cout << msg << RESET << std::endl;
}
void Log::warn(std::string msg)
{
    std::cout << H_YELLOW;
    std::cout << msg << RESET << std::endl;
}
void Log::print(std::string msg)
{
    std::cout << RESET;
    std::cout << msg << RESET << std::endl;
}
void Log::note(std::string msg)
{
    std::cout << H_BLUE;
    std::cout << msg << RESET << std::endl;
}
void Log::success(std::string msg)
{
    std::cout << GREEN;
    std::cout << msg << RESET << std::endl;
}
