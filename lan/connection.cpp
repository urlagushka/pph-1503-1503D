#include "connection.h"

#include <cstring>
#include <stdexcept>
#include <string>

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

Connection::Connection(const ip_t& ip) :
    ip_(ip),
    client_(INVALID_SOCKET),
    info_(),
    addr_()
{}

Connection::~Connection() {
    closesocket(client_);
}

void Connection::safe_connect() {
    WSADATA ws;
    struct sockaddr_in server;

    if (WSAStartup(MAKEWORD(2, 2), &ws) != 0) {
        std::string error = "wsa error at ";
        error.append(std::to_string(GetLastError()));
        throw std::runtime_error(error);
    }

    if ((client_ = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::string error = "invalid socket at ";
        error.append(std::to_string(GetLastError()));
        throw std::runtime_error(error);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip_);
    server.sin_port = htons(8888);

    if (connect(client_, (struct sockaddr*)&server, sizeof(server)) < 0) {
        std::string error = "connection err ";
        error.append(std::to_string(GetLastError()));
        throw std::runtime_error(error);
    }
}

void Connection::safe_send(const char * msg) {
    if (send(client_, msg, (int)strlen(msg), 0) == SOCKET_ERROR) {;
        throw std::runtime_error("send error");
    }
}

void Connection::safe_read(msg_t& reply, const size_t reply_size) {
    if (recv(client_, reply, reply_size, 0) < 0) {
        throw std::runtime_error("receive error");
    }
}
