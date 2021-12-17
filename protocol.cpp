#include <vector>
#include <stdio.h>
#include <iostream>
#include <array>
#include "protocol.h"

/*
std::vector<std::string> split(std::string)
{
	
}







message message::mDecode(std::string etxt)
{
	

}

*/

unsigned char* message::encode()
{
	unsigned int nOfArgs = sizeof(arguments); // Number of arguments
	int lenOfMsg = 5; // Length of message in bytes
	for(int i=0; nOfArgs>i; i++)
	{
		lenOfMsg += arguments[i].len;
	}


	unsigned char msgStr[lenOfMsg] = {0};
	msgStr[0] = protocol[0];
	msgStr[1] = protocol[1];
	msgStr[2] = version;

	msgStr[3] = type;
	msgStr[4] = (flags >> 8) & 0xFF;
	msgStr[5] = flags & 0xFF;

	return msgStr;
}
