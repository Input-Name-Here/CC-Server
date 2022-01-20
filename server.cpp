#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "logger.h"
#include "colour.h"
#include "server.h"
#include "protocol.h"
bool Server::threads_active = true;

Server::~Server()
{

}

void Server::Listen(int port)
{
    int opt = 1;
    int addrlen = sizeof(m_address);


    if ( (m_server_fd = socket(AF_INET, SOCK_STREAM,0 )) == 0)
    {
        Logger::Log(LOG_FATAL, "Error attempting to initialize socket");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(m_server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)))
    {
        Logger::Log(LOG_FATAL, "Error setting socket options");
        exit(EXIT_FAILURE);
    }

    m_address.sin_family = AF_INET;
    m_address.sin_addr.s_addr = INADDR_ANY;
    m_address.sin_port = htons(port);

    if (bind(m_server_fd, (struct sockaddr *)&m_address,sizeof(m_address))<0)
    {
        Logger::Log(LOG_FATAL, "Error while binding to address");
        exit(EXIT_FAILURE);
    }

    
    if (listen(m_server_fd, 50) < 0)
    {
        Logger::Log(LOG_FATAL, "Error while attempting to listen");
        exit(EXIT_FAILURE);
    }

    while (true)
    {
        int sock = 0;
        
        if ((sock = accept(m_server_fd, (struct sockaddr *) &m_address, (socklen_t*) &addrlen))<0)
        {
            Logger::Log(LOG_FATAL, "Error while accepting connection");
            exit(EXIT_FAILURE);
        }
        else{
            Logger::Log(LOG_INFO, "Client has connected");
            std::thread handler(ClientHandler, sock);
            handler.detach();
        }
    }

    
}

void Server::ClientHandler(int sfd)
{
    char buffer[1024] = {0}; // buffer for input
    int valread;

    while (threads_active && (valread = read( sfd , buffer, 1024) != 0)) // Loop that listens to a socket
    {
        
        message recvmsg;
        std::string str(buffer,1024);
        recvmsg.decode(std::string(buffer,1024));
        recvmsg.debug();
        
        char *reply = "Message Recieved\0";
        send(sfd , reply , strlen(reply) , 0 );
        printf("Message received : %s\n%s%s\n", H_CYAN,buffer,RESET);
        if (buffer[0]=='C'&buffer[1]=='S'&buffer[2]=='V'){
            printf("CSV Receieved");
        }
        buffer[1024] = {0};
    }
    Logger::Log(LOG_INFO, "Loop died");
}
