/*client*/

/*
    
   SOCKET() -> CONNECT()

*/
#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024


int main(int argc, char* argv[]){

    if (argc != 2) {

        fprintf(stderr, "Usage: %s IP_Server\n", argv[0]);
        exit(1);
    
    }


    int client_connector;
    FILE *file;
    char buffer[BUFFER_SIZE];


    if((client_connector = socket(AF_INET, SOCK_STREAM, 0)) < 0){

        perror("Client socket error"); 
        exit(1);

    }


    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);


    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9999); 
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);



    if((connect(client_connector, (struct sockaddr *) &server_addr, addr_len )) < 0){

        perror("Connection with server failed\n");
        close(client_connector);
        exit(1);

    }

    
    file = fopen("Google.html", "wb");

    if (file == NULL){

        perror("File was not found");
        close(client_connector);
        exit(1);

    }

    ssize_t bytes_received;
    size_t  total = 0;

    while ((bytes_received = recv(client_connector, buffer, BUFFER_SIZE, 0)) > 0) {

        fwrite(buffer, 1, (size_t)bytes_received, stdout);
        fwrite(buffer, 1, (size_t)bytes_received, file);
        total += (size_t)bytes_received;
    
    }

    fclose(file);
    close(client_connector);

    pid_t process = fork();

    if (process < 0){

        perror("Fork error");
        exit(1);

    }

    if (process == 0){

        execlp("zen-browser", "zen-browser", "Google.html", (char *) NULL);

        perror("Exec error");
        _exit(1);

    }

     
    wait(NULL);

    return 0;
}

