#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <thread>
#include <netinet/in.h>

class Server {
public:
    ~Server();

    void Listen(int port);

    static void ClientHandler(int s_fd);

private:
    int m_server_fd;
    int m_sock;
    struct sockaddr_in m_address;
    static bool threads_active;

};

#endif // SERVER_H