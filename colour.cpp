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
    std::cout << YELLOW;
    std::cout << msg << RESET << std::endl;
}

