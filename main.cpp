#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <thread>
#include <mutex>

#include "colour.h"

using namespace std;

// Thread to handle connections
void ConnectionThread(int sock_fd){
    try {
        mutex socket_lock;
        Log::print("Thread created");

        int sock = sock_fd; // sock input from accept()
        char buffer[1024] = {0}; // buffer for input
        bool runLoop = true; // runs loop while true
        int valread;

        while (runLoop && (valread = read( sock , buffer, 1024) != 0)) // Loop that listens to a socket
        {
            Log::success("Loop");
            try{
                Log::print("Before try read");
                ;
                Log::print("After try read");
            } catch (exception& e) {
                Log::warn(strcat("Error ",e.what()));
            }
            Log::print("After try ");

            //printf("%s\n",buffer );
            char *message = "Message Recieved\0";
            Log::print("Before Send ");
            try{
                Log::print("Before try send");
                
                Log::print("After try send");
            } catch (exception& e) {
                Log::warn(strcat("Error ",e.what()));
            }
            unique_lock<mutex> lock(socket_lock);
            send(sock , message , strlen(message) , 0 );
            printf("Message received : %s\n", buffer);
        }
        Log::warn("Thread Killed");
    } catch(...) {
        Log::alert("FUCK!");
    }
}



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

    
    if (listen(server_fd, 50) < 0)
    {
        Log::alert("Critical Error");
        Log::error("Error attempting to listen");
        exit(EXIT_FAILURE);
    }

    while (true)
    {
        int sock = 0;
        Log::print("Listening");
        if ((sock = accept(server_fd, (struct sockaddr *) &address, (socklen_t*) &addrlen))<0)
        {
            Log::alert("Critical Error");
            Log::error("Error attempting to listen");
            exit(EXIT_FAILURE);
        }
        else{
            Log::note("Accepted connection!");
            thread connThrObj(ConnectionThread, sock);
            connThrObj.detach();
            Log::warn("After Thread");
        }
    }



    

    Log::warn("End main loop");
    while (true) {
        // bing
    }   
    Log::warn("End of main");
}





