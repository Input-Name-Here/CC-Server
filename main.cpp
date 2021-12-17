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
    struct argument arg;
    arg.arg_type = 0x00; // Null / Ignore
    arg.len=std::size(data);

    struct argument args[1] = {arg};

    message msg;
    msg.arguments = args;
    msg.type = 0x00; 
    msg.flags = 0b0000000000000000;


    signal(SIGINT, signal_handler); 

    if(argv <= 1){
        printf("Usage : %s [port]\n", argc[0]);
        return EXIT_FAILURE;
    }

    int port = atoi(argc[1]);

    server.Listen(port);
    return EXIT_SUCCESS;
}





