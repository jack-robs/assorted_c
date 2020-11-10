// Compile with: gcc tcpserver.c -o tcpserver
//
// Implement tcp server below.
//
// stnd libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//types/unix ops
#include <sys/types.h>
#include <unistd.h>

//sockets lib/IP lib
#include <sys/socket.h>
#include <netinet/in.h>

int main() {

	//create server socket
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	//define server address format
	struct sockaddr_in server_address;

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = htons(INADDR_ANY);

	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
	printf("Server bind()\n");

	
	listen(server_socket, 27);

	//accept connections
	int client_socket;
	client_socket = accept(server_socket, NULL, NULL);
	char server_message[256] = "You have reached the server";
	
	send(client_socket, server_message, sizeof(server_message), 0);

	close(server_socket);

}

