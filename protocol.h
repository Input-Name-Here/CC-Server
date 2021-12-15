#include <string>
#include <vector>

#ifndef PROTOCOL_H
#define PROTOCOL_H


struct header
{
	std::string version; // Example "CC1"
	std::string request; // Example "Get"
	std::vector<std::vector<std::string>> data; 
};

struct body
{
	std::string data; 
};

class message
{
public:
	std::string mEncode(); // Encode 
	message mDecode(std::string etxt);
	header messageHeader;
	body messageBody;
private:
	char seperator = ':';
	char endofline = ';';
    
};




#endif