#include "Client.h"

void Client::create_socket()
{
#ifdef _WIN32
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
    {
        std::cout << "Failed to initialize Winsock!" << std::endl;
        exit(1);
    }

    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_file_descriptor == INVALID_SOCKET)
    {
        std::cout << "Creation of Socket failed!" << std::endl;
        exit(1);
    }
#else
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_file_descriptor == -1)
    {
        std::cout << "Creation of Socket failed!" << std::endl;
        exit(1);
    }
#endif
}

void Client::connection_to_server() 
{
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(PORT);
    server_address.sin_family = AF_INET;

#ifdef _WIN32
    connection = connect(socket_file_descriptor, (struct sockaddr*)&server_address, sizeof(server_address));

    if (connection == SOCKET_ERROR) {
        std::cout << "Connection with the server failed!" << std::endl;
        exit(1);
    }
#else   
    connection = connect(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));

    if (connection == -1) {
        std::cout << "Connection with the server failed.!" << std::endl;
        exit(1);
    }
#endif
}

void Client::close_socket()
{
#ifdef _WIN32
    closesocket(socket_file_descriptor);
    WSACleanup();
#else
    close(socket_file_descriptor);
#endif
}

char* Client::read_data()
{
#ifdef _WIN32
    memset(message, '\0', MESSAGE_LENGTH);
    recv(socket_file_descriptor, message, sizeof(message), 0);
#else
    bzero(message, sizeof(message));
    read(socket_file_descriptor, message, sizeof(message));
#endif

    return message;
}

void Client::write_data(std::string clientMessage)
{
#ifdef _WIN32
    memset(message, '\0', MESSAGE_LENGTH);
    strcpy_s(message, clientMessage.c_str());

    send(socket_file_descriptor, message, sizeof(message), 0);
#else
    bzero(message, sizeof(message));
    strcpy_s(message, clientMessage.c_str());

    write(socket_file_descriptor, message, sizeof(message));
#endif
}
