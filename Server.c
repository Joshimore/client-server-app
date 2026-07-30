/*server*/

/*STRUCT TO DO: 

  SOCKET()done -> BIND()done -> LISTEN()done -> ACCEPT()done

*/

#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 1024


int main(){

    int connector, client_socket; 
    FILE *file;
    char buffer[BUFFER_SIZE];


    //socket initialization SOCKET()
    if((connector = socket(AF_INET, SOCK_STREAM, 0)) < 0){

       perror("Server socket error"); 
       exit(1);

    }
   
    printf("Socket initialized\n");
    sleep(1);
    
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);
    

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9999); 
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind init BIND()
    if (bind(connector, (struct sockaddr *) &server_addr, addr_len) < 0) {
        
        perror("Server bind failed");
        exit(1);
    }

    printf("Bind is done\n");
    sleep(1);
        
        //listen init LISTEN()
        if(listen(connector, 5) < 0){

           perror("listen error"); 
        }

        printf("Server started...\n\n");
        
        sleep(2);
        
        printf("Listening port 9999\n");

        while(1){
            
            socklen_t addr_len = sizeof(server_addr);
            
            //accept init ACCEPT()
           if ((client_socket = accept(connector, (struct sockaddr *) &server_addr, &addr_len)) < 0){           
           
               perror("Server accept error"); 
               continue; 
           }

            pid_t process = fork();

            if (process < 0){

                printf("Fork error");
                exit(1);

            }

            file = fopen("Google.html", "rb");
            
            if (file == NULL) {

                perror("File not found");
                exit(1);
           
            } 

            while (fread(buffer, 1, BUFFER_SIZE, file) > 0) {
                
                send(client_socket, buffer, BUFFER_SIZE, 0);
           
            }

            close(client_socket);      
        }

        close(connector);


    return 0;

}


