#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <array>
#include "protocol.h"
#include <string.h>
#include <string>
#include "colour.h"
#include <algorithm>



void message::decode(std::string etxt)
{   
    std::string txt = etxt;
    if(txt.at(0)=='C' & txt.at(1)=='2')
    {
        this->type = txt.at(3);
        this->flags = (((short)txt.at(4)) << 8) | txt.at(5);
        std::string searchtxt = txt.substr(6,(txt.size()-6));

        size_t pos = 0;
        std::string token;
        std::string delimiter=",";
        std::vector<std::string> strArgs;
        
        while ((pos = searchtxt.find(delimiter)) != std::string::npos) {
            token = searchtxt.substr(0, pos);
            strArgs.push_back(token);
            searchtxt.erase(0, pos + delimiter.length());
        }
        searchtxt.pop_back();
        strArgs.push_back(searchtxt);
        
        
        for(int i=0; strArgs.size()>i; i++){
            std::string atxt = strArgs[i];
            std::string delimiter=":";
            while ((pos = atxt.find(delimiter)) != std::string::npos) {
                token = atxt.substr(0, pos);
                atxt.erase(0, pos + delimiter.length());
            }
            struct argument arg;
            arg.argtype = token; 
            arg.data = atxt;
            this->arguments.push_back(arg);
        }
        
        

    }

}



int arglen(struct argument arg){
    return sizeof(arg.data) + sizeof(arg.argtype) + 2;
}


std::string message::encode()
{
	

    //(unsigned char*)malloc(lenOfMsg);
	//unsigned char* msgStr = (unsigned char*)malloc(lenOfMsg);
	char msgStr[6] = {0};
	msgStr[0] = protocol[0];
	msgStr[1] = protocol[1];
	msgStr[2] = version;

	msgStr[3] = type;
	msgStr[4] = (flags >> 8) & 0xFF;
	msgStr[5] = flags & 0xFF;
    std::string messageString = msgStr;
    
	for(int i=0; arguments.size()>i; i++)
	{
        messageString += arguments[i].argtype+":"+arguments[i].data+",";
	}
    
    messageString.pop_back();
    messageString+=";";
	return messageString;
}


void message::debug()
{
    std::string msg = encode();
    
    char flag1 = (this->flags >> 8) & 0xFF;
    char flag2 = this->flags & 0xFF;
    
    printf("Message Debug\n");
    printf("- %sMSG Length%s: %s%lu\n%s",H_BLUE,RESET,H_GREEN , msg.size(), RESET);
    printf("- %sProtocol%s: %s%c%c\n%s",H_BLUE,RESET,H_GREEN, this->protocol[0], this->protocol[1], RESET);
    printf("- %sVersion%s: %s%u\n%s",H_BLUE,RESET,H_GREEN, this->version, RESET);
    printf("- %sType%s: %s0x%02x\n%s",H_BLUE,RESET,H_GREEN, this->type, RESET);
    printf("- %sFlags%s: %s0x%02x%02x\n%s",H_BLUE,RESET,H_GREEN, flag1, flag2 , RESET);
    printf("- %sArguments%s:\n",H_BLUE,RESET);

    for(int i=0; this->arguments.size()>i; i++)
	{
		printf("  - %s%s%s:%s%s%s\n",H_MAGENTA,
               this->arguments[i].argtype.c_str(),
               RESET,H_YELLOW,
               this->arguments[i].data.c_str(),
               RESET
              );
	}
    
    //free(msg);
}
