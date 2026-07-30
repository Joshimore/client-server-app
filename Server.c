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
   
    printf("Server socket initialized\n");
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

    printf("Bind to port 9999\n");
    sleep(1);
        
        //listen init LISTEN()
        if(listen(connector, 5) < 0){

           perror("listen error"); 
           exit(1);
        }
        
        sleep(2);        
        printf("Listening...\n");

        while(1){
            
            socklen_t addr_len = sizeof(server_addr);
            
            //accept init ACCEPT()
           if ((client_socket = accept(connector, (struct sockaddr *) &server_addr, &addr_len)) < 0){           
           
               perror("Server accept error"); 
               continue; 
           }

           printf("Client connected\n");

            pid_t process = fork();

            if (process < 0){

                printf("Fork error");
                close(client_socket);
                continue;

            }

            if(process == 0){

                close(connector);

                file = fopen("Google.html", "rb");

                if (file == NULL) {

                    perror("File not found");
                    close(client_socket);
                    _exit(1);

                } 

            

            size_t n;

            while ((n = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
                
                if (send(client_socket, buffer, n, 0) < 0){

                    perror("Error while sending a message");
                    break;

                }
           
            }
    
            fclose(file);
            close(client_socket);

            printf("File was uploaded to a client\n");


            exit(1);

             
        }
        close(client_socket);

    }

    return 0;

}


