#ifndef CONNECTION_H
#define CONNECTION_H

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

class Connection {
public:
    using ip_t = char*;
    using client_t = SOCKET;
    using msg_t = char*;

    Connection() = delete;
    explicit Connection(const ip_t& ip);
    Connection(const Connection&) = delete;
    Connection(Connection&&) = delete;
    Connection operator=(const Connection&) = delete;
    Connection operator=(Connection&&) = delete;
    ~Connection();

    void safe_connect();

    void safe_send(const char * msg);
    void safe_read(msg_t& reply, size_t reply_size);
private:
    ip_t ip_;
    client_t client_;
    addrinfo info_;
    sockaddr_in addr_;
};

#endif
