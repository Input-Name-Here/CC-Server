#include <stdio.h>
#include <stdlib.h>
#include <csignal>
#include "server.h"
#include "logger.h"

Server server;

void signal_handler(int sig)
{
    Logger::Log(LOG_WARNING, "Got interrupt signal");
    server.~Server(); // Call deconstructor
    exit(sig);
}

int main(int argv, char** argc)
{
    signal(SIGINT, signal_handler); 

    if(argv <= 1){
        printf("Usage : %s [port]\n", argc[0]);
        return EXIT_FAILURE;
    }

    int port = atoi(argc[1]);

    server.Listen(port);
    return EXIT_SUCCESS;
}





