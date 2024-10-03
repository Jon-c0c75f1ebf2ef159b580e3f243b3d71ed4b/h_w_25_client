#pragma once
#include <iostream>
#include <string>

#ifdef _WIN32
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

#define MESSAGE_LENGTH 1024
#define PORT 7777

class Client
{
public:
#ifdef _WIN32
    WSADATA wsa_data;
    SOCKET socket_file_descriptor, connection;
#else
    int socket_file_descriptor, connection;
#endif
    sockaddr_in server_address;
    sockaddr_in client;

    void create_socket();
    void connection_to_server();
    void close_socket();
    char* read_data();
    void write_data(std::string clientMessage);

private:
    char message[MESSAGE_LENGTH];
};
