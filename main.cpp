#include <stdio.h>
#include <stdlib.h>
#include <csignal>
#include <array>

#include "server.h"
#include "logger.h"
#include "protocol.h"

Server server;




void signal_handler(int sig)
{
    Logger::Log(LOG_WARNING, "Got interrupt signal");
    server.~Server(); // Call deconstructor
    exit(sig);
}

int main(int argv, char** argc)
{
    unsigned char data[] = "Hello world!";
    struct argument arg1;
    arg1.argtype = "A"; 
    arg1.data = "hello";
    struct argument arg2;
    arg2.argtype = "B"; 
    arg2.data = "Wow!";
    struct argument arg3("SEX","Test");

    //std::vector<struct argument> args = {arg};

    message msg;
    msg.arguments = {arg1,arg2,arg3};
    msg.type = 0x00; 
    msg.flags = 0x0000;
    //msg.debug();

    //message msg2;
    //msg2.decode(msg.encode());
    //msg2.debug();
    
    signal(SIGINT, signal_handler); 

    if(argv <= 1){
        printf("Usage : %s [port]\n", argc[0]);
        return EXIT_FAILURE;
    }

    int port = atoi(argc[1]);

    server.Listen(port);
    return EXIT_SUCCESS;
}





