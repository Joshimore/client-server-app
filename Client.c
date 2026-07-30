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


int main(){


    int client_connector;


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

        perror("Client connect error");
        exit(1);

     }




    return 0;
}

