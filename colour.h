#ifndef COLOUR_H
#define COLOUR_H

#include <string>

// Specials
#define RESET "\e[0m"
#define BOLD "\e[1m"
#define ITALICS "\e[3m"
#define UNDERLINE "\e[4m"
#define BLINK "\e[5m"
#define INVERSE "\e[7m"
#define STRIKE "\e[9m"

// Foreground / Background defaults
#define F_DEFAULT "\e[39m"
#define B_DEFAULT "\e[49m"

// Foreground colours
#define HIDDEN "\e[8m" // Same as background
#define BLACK "\e[30m"
#define RED "\e[31m"
#define GREEN "\e[32m"
#define YELLOW "\e[33m"
#define BLUE "\e[34m"
#define MAGENTA "\e[35m"
#define CYAN "\e[36m"
#define WHITE "\e[37m"

// Background colours
#define B_BLACK "\e[40m"
#define B_RED "\e[41m"
#define B_GREEN "\e[42m"
#define B_YELLOW "\e[43m"
#define B_BLUE "\e[44m"
#define B_MAGENTA "\e[45m"
#define B_CYAN "\e[46m"
#define B_WHITE "\e[47m"

// Foreground High colours
#define H_BLACK "\e[90m"
#define H_RED "\e[91m"
#define H_GREEN "\e[92m"
#define H_YELLOW "\e[93m"
#define H_BLUE "\e[94m"
#define H_MAGENTA "\e[95m"
#define H_CYAN "\e[96m"
#define H_WHITE "\e[97m"

#endif // COLOUR_H
