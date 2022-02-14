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



void message::decode(std::vector<unsigned char> Data)
{   
    if(Data[0]==0x43& Data[1]==0x32& Data[2]==0x44& Data[3]==0x00)
    {
        std::string msgStr = std::string(Data.begin(), Data.end());
        this->startIndex=(Data[4]<<8)+Data[5];
        this->endIndex=(Data[6]<<8)+Data[7];
        this->flags=(Data[10]<<8)+Data[11];
        this->target= (Data[12]<<16)+(Data[13]<<8)+Data[14];
        this->origin= (Data[15]<<16)+(Data[16]<<8)+Data[17];
        this->msgID= (Data[18]<<24)+(Data[19]<<16)+(Data[20]<<8)+Data[21];

        if(Data[endIndex]!=0x00)
        {
            int DataIndex = startIndex;
            while (DataIndex < endIndex)
            {
                int arglen = Data[DataIndex];
                std::string arg = std::string(msgStr,DataIndex+1,arglen );
                int datalen = (Data[DataIndex]<<8)+Data[DataIndex];
                std::string data = std::string(msgStr,DataIndex+arglen+3,arglen );

            }
        }
    }

}


/*
int arglen(struct argument arg){
    return sizeof(arg.data) + sizeof(arg.argtype) + 2;
}
*/

std::vector<unsigned char>  message::encode()
{
	

    //(unsigned char*)malloc(lenOfMsg);
	//unsigned char* msgStr = (unsigned char*)malloc(lenOfMsg);
    //unsigned char protocol[4] = {0x43,0x32,32,32}; 

    unsigned short int startIndex = 22;

	std::vector<unsigned char>  MSG_Arr;
    // Protocol 4 bytes
	MSG_Arr.push_back( protocol[0]);
	MSG_Arr.push_back( protocol[1]);
    MSG_Arr.push_back( protocol[2]);
    MSG_Arr.push_back( protocol[3]);
    // Start index 2 bytes
    MSG_Arr.push_back( (startIndex >> 8) & 0xFF);
    MSG_Arr.push_back( startIndex & 0xFF);
    // End index 2 bytes (placeholder)
    MSG_Arr.push_back(0x00);
    MSG_Arr.push_back(0x00);
    // Version 2 bytes
	MSG_Arr.push_back( (version >> 8) & 0xFF);
    MSG_Arr.push_back(  version & 0xFF);
    // Flags 2 bytes
	MSG_Arr.push_back( (flags >> 8) & 0xFF);
	MSG_Arr.push_back(  flags & 0xFF);
    // Target ID 3 bytes
    MSG_Arr.push_back( (target >> 16) & 0xFF);
    MSG_Arr.push_back( (target >> 8) & 0xFF);
    MSG_Arr.push_back(  target & 0xFF);
    // Origin / Source ID 3 bytes
    MSG_Arr.push_back( (origin >> 16) & 0xFF);
    MSG_Arr.push_back( (origin >> 8) & 0xFF);
    MSG_Arr.push_back(  origin & 0xFF);
    // Message Block ID / Message ID 4 Bytes
    MSG_Arr.push_back( (msgID >> 24) & 0xFF);
    MSG_Arr.push_back( (msgID >> 16) & 0xFF);
    MSG_Arr.push_back( (msgID >> 8) & 0xFF);
    MSG_Arr.push_back(  msgID & 0xFF);



	for(int i=0; arguments.size()>i; i++)
	{
        //std::cout<<arguments.size()<<std::endl;
        std::string TmpDataStr= 
            (char)arguments[i].argtype.size()+
            arguments[i].argtype+
            (char)((arguments[i].data.size() >> 8) & 0xFF)+
            (char) (arguments[i].data.size() & 0xFF)+
            arguments[i].data;
        for (int C=0; TmpDataStr.size()>C; C++){
            MSG_Arr.push_back(TmpDataStr[C]);
        }
	}
    MSG_Arr.push_back(0x00);
    endIndex = MSG_Arr.size();
    MSG_Arr[6] = (endIndex >> 8) & 0xFF;
    MSG_Arr[7] = (endIndex) & 0xFF;
    //*/
    //messageString.pop_back();
    //messageString+=";";
	return MSG_Arr;
    //return MSG_Arr;
}

void printhex(std::string ms){
    //std::cout << sizeof(ms)<<std::endl;
    for(int i=0; ms.size()>i; i++){
        printf("%d : %d %c 0x%x\n", i,ms[i],ms[i], ms[i]);

    }


}


void message::debug()
{
    std::vector<unsigned char> msgv = encode();
    std::string msg = std::string(msgv.begin(), msgv.end());
    std::cout << msg << std::endl;
    printhex(msg);
    char flag1 = (this->flags >> 8) & 0xFF;
    char flag2 = this->flags & 0xFF;
    
    printf("Message Debug\n");
    printf("- %sMSG Length%s: %s%lu\n%s",H_BLUE,RESET,H_GREEN , sizeof(msgv), RESET);
    printf("- %sProtocol%s: %s%c%c%c%c\n%s",H_BLUE,RESET,H_GREEN, this->protocol[0], this->protocol[1],this->protocol[2], this->protocol[3], RESET);
    printf("- %sVersion%s: %s%u\n%s",H_BLUE,RESET,H_GREEN, this->version, RESET);
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
