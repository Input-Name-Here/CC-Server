#include <string>
#include <vector>

#ifndef PROTOCOL_H
#define PROTOCOL_H


struct argument{
	unsigned char  arg_type;
	short int      len;
	unsigned char* data;
};

class message
{
public:
	unsigned char* encode();
	void decode(unsigned char msg[]);

	unsigned char type;
	short int flags;

	struct argument* arguments[];
private:
	const unsigned char protocol[2] = {0x43,0x32}; 
	const unsigned char  version    = 1;

};




#endif