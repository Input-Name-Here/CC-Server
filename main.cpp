#include <stdio.h>
#include <stdlib.h>
#include <csignal>
#include "server.h"
#include "logger.h"
#include "protocol.h"

Server server;

const std::string exampleMtext =
  "CC_0.1\n"
  "SEND_C_MSG\n"
  "Username: Pine07;\n"
  "Body;\n"
  "Hello this is a message!\n";





void signal_handler(int sig)
{
    Logger::Log(LOG_WARNING, "Got interrupt signal");
    server.~Server(); // Call deconstructor
    exit(sig);
}

int main(int argv, char** argc)
{
    struct header h;
    h.version = "CC_0.1";
    h.request = "SEND_C_MSG";
    h.data = {{"Username","Pine07"}};
    struct body b;
    b.data = "Hello this is a message!";

    message m;
    m.messageHeader = h;
    m.messageBody = b;

    signal(SIGINT, signal_handler); 

    Logger::sLog(LOG_INFO,"Message: \n"+m.mEncode());

    if(argv <= 1){
        printf("Usage : %s [port]\n", argc[0]);
        return EXIT_FAILURE;
    }

    int port = atoi(argc[1]);

    server.Listen(port);
    return EXIT_SUCCESS;
}





