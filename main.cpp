//skillfactory home work modul 25 Client

#include <iostream>
#include "Client.h"
#include "Chat.h"

int main()
{
    std::string client_message;
    std::string server_message;

    Client client;
    Chat chat;

    client.create_socket();
    client.connection_to_server();

    chat.start_message();

	while (true) 
	{
		client_message = chat.chat_processing();
		client.write_data(client_message);
		if (client_message == "exit") {
			break;
		}
		server_message = client.read_data();
		chat.message_processing(server_message);
	}

	client.close_socket();

	return 0;
}
