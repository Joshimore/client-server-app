/*server*/

/*STRUCT TO DO: 

  SOCKET()done -> BIND()done -> LISTEN()done -> ACCEPT()

*/

#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>


int main(){

    int connector, client_socket; 
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    //socket initialization SOCKET()
    if((connector = socket(AF_INET, SOCK_STREAM, 0)) < 0){

       perror("Socket malfunction"); 
       exit(1);

    }

    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(9999); 
    client_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind init BIND()
    if (bind(connector, (struct sockaddr *) &client_addr, addr_len) < 0) {
        
        perror("bind failed");
        exit(1);
    }
        
        //listen init LISTEN()
        listen(connector, 5);

        printf("Server started...\n");
        
        sleep(3);
        
        printf("Listening port 9999\n");

        for (;;) {
            
            socklen_t addr_len = sizeof(client_addr);
            
            //accept init ACCEPT()
           if ((client_socket = accept(connector, (struct sockaddr *) &client_addr, &addr_len)) < 0){           
           
               perror("accept"); 
               continue; 
           }

        

            close(client_socket);      
        }

        close(connector);


    return 0;

}


