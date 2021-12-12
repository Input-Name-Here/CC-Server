#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#include "colour.h"

using namespace std;

int main()
{

    cout << "Server Start" << endl;
    cout << "Port: ";
    int port;
    string portinput;
    cin >> portinput;
    port = stoi(portinput);
    cout << endl;

    //return 0;

    int server_fd;
    int sock;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    if ( (server_fd = socket(AF_INET, SOCK_STREAM,0 )) == 0)
    {
        Log::alert("Critical Error");
        Log::error("Error attempting to initialise socket");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)))
    {
        Log::alert("Critical Error");
        Log::error("Error setting socket options");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address,sizeof(address))<0)
    {
        Log::alert("Critical Error");
        Log::error("Error while binding");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        Log::alert("Critical Error");
        Log::error("Error attempting to listen");
        exit(EXIT_FAILURE);
    }
    if ((sock = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen))<0)
    {
        Log::alert("Critical Error");
        Log::error("Error attempting to listen");
        exit(EXIT_FAILURE);
    }
    int valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );
    send(sock , "Ez" , strlen("Ez") , 0 );

}

