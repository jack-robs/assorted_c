// Compile with: gcc tcpserver.c -o tcpserver
//
// Implement tcp server below.
//
// stnd libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

//types/unix ops
#include <sys/types.h>
#include <unistd.h>

//sockets lib/IP lib
#include <sys/socket.h>
#include <netinet/in.h>


//add signal handler
static int server_socket;

void sighan(int sig) {
    write(1, "Terminating server Ctr-C\n", 35);
    close(server_socket);
    exit(0);
}

int main() {

    //install signal handler
    signal(SIGINT, sighan);

	//create server socket
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        printf("Server socket fail\n");
        exit(0); 
    }

	//define server address format
	struct sockaddr_in server_address;

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = htons(INADDR_ANY);

	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
	printf("Server bind()\n");

	
	listen(server_socket, 27);


    //****REPEAT****/

    while(1) {

 
        //****Start handshake****//
        //accept connections
        int client_socket;
        //has all info from client socket - it's addr
        //accepting connects on server socket
        client_socket = accept(server_socket, NULL, NULL);

        //send message to client
        printf("Client has joined: %d", client_socket);

        //receive username of client, send it back
        char username[32];
        recv(client_socket, &username, sizeof(username), 0);
        printf("Username: %s\n", username);


        //send: tell client a server was reached
        char serverResponse[256] = "You reached server ";
        strcat(serverResponse, username);
        send(client_socket, serverResponse, strlen(serverResponse), 0);

        //****End handshake****//

        //****Receive run user commands****//

        char command[128];
        while (strncmp(command, "exit", 4) != 0) { 

            //clear the command
            memset(command, 0, sizeof(command));

            recv(client_socket, &command, sizeof(command), 0);
            printf("Rec'd command: %s\n", command);
            system(command);
            
            if (strncmp(command, "exit", 4) == 0) {
                exit(0);
            }

        }
        

        close(client_socket);
    }


	close(server_socket);
    return 0;

}

