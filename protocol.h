#include <string>
#include <vector>

#ifndef PROTOCOL_H
#define PROTOCOL_H

int arglen(struct argument);

struct argument{
	std::string argtype;
	short int      len;
	std::string data;
    argument(){}
    argument(std::string a, std::string d){
        this->argtype = a;
        this->data = d;
    }
};



class message
{
public:
	std::string encode();
	void decode(std::string etxt);
    
    std::string getRequest();
    void debug();
    
	unsigned char type;
	short int flags;

	std::vector<struct argument> arguments;
private:
	unsigned char protocol[2] = {0x43,0x32}; 
	unsigned char  version    = 1;

};




#endif
