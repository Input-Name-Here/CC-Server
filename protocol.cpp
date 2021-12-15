#include <vector>
#include <stdio.h>
#include <iostream>
#include "protocol.h"

std::string message::mEncode(){
	std::string messageText;
	messageText  = messageHeader.version;
	messageText += "\n";
	messageText += messageHeader.request;
	messageText += "\n";

	for(int i=0; i<messageHeader.data.size(); i++)
	{
		messageText += messageHeader.data[i][0];
		messageText += ": ";
		messageText += messageHeader.data[i][1];
		messageText += ";\n ";
	}
	messageText += "Data;";
	messageText += messageBody.data;

	return messageText;

}

