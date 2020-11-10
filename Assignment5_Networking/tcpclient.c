// Note: I recommend implementing the tcpserver.c first.
//
// Compile with: gcc tcpclient.c -o tcpclient
//
// Implement tcp client below.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

int main() {

    //id of socket when it's created
	int client_socket;


    //try to create socket for client - a file descriptor (fd)
    // this is basically just an empty file right now
	if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		("\nSocket creation error\n");
        return -1;
	}

    //create an address to assoc w/ the socket
	struct sockaddr_in server_address;
    //ipv4 = AF_INET sin_family = familyof addresses
	server_address.sin_family = AF_INET;
    //sin_port = port
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = htons(INADDR_ANY);
	
    int connection_status;

    //connect: connect clicent socket to server address craeted 
	if ((connection_status = connect(client_socket, (struct sockaddr*) &server_address, sizeof(server_address))) < 0) {
		printf("%d connection fail\n", connection_status);
		close(client_socket);

        //safer than return -1 for additional cleanup
		exit(0);
	} else {
		printf("Connected success\n");
	}


    //connection interaction

    //get client usenrame
    char name[32];
    printf("Enter username:\n");
    fgets(name, 32, stdin);


    //(1) SEND
    //send username to server
    send(client_socket, &name, sizeof(name), 0);

    //kill later
    printf("Sizeof sent: %ld\n", strlen(name));

    //get response from server
	char server_response[256];

    
    //(2) RECEIVE
    //receive through the client socket, the server response
	recv(client_socket, &server_response, sizeof(server_response), 0);

	printf("The server sent data: %s\n", server_response);

    char clientCommand[128];
    char *PROMPT  = "client> ";

    while (1) {
        printf("%s", PROMPT);
        fgets(clientCommand, 128, stdin);
        send(client_socket, &clientCommand, strlen(clientCommand), 0);
        if (strcmp(clientCommand, "exit\n") == 0) {
            close(client_socket);
            return 0;
        }
    }

}
