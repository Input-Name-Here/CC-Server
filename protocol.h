#include <string>
#include <vector>

#ifndef PROTOCOL_H
#define PROTOCOL_H

int arglen(struct argument);

struct argument{
	std::string type;
	short int      len;
	std::string data;
};

class message
{
public:
	std::vector<unsigned char>  encode();
	void decode(std::vector<unsigned char>  etxt);
    void debug();
    
	short int flags=0x0000;

	std::vector<struct argument> arguments;
	const unsigned char protocol[4] = {0x43,0x32,0x44,0x00}; 
	const unsigned char  version    = 1;
    unsigned int target = 0x111111; // Reciever / 3 Byte
    unsigned int origin = 0x222222; // Sender / 3 Byte
    unsigned int msgID  = 0x33333333; // Message block ID / 4 byte

private:
	unsigned short int startIndex;
	unsigned short int endIndex;

};




#endif
