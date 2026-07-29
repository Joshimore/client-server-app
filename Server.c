/*server*/

/*STRUCT TO DO: 

  SOCKET()done -> BIND()done -> LISTEN()done -> ACCEPT()

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>


int main(){

    int connector; 
    struct sockaddr_in name;
    int sockfd;

    //socket initialization SOCKET()
    if((connector = socket(AF_INET, SOCK_STREAM, 0)) < 0){

       perror("Socket malfunction"); 
       exit(1);

    }

    memset(&name, 0, sizeof(name));

    name.sin_family = AF_INET;
    name.sin_port = htons(9999); 
    name.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind init BIND()
    if (bind(connector, (struct sockaddr *) &name, sizeof(name)) < 0) {
        
        perror("bind failed");
        exit(1);
    }

    //listen init LISTEN()
    listen(connector, 1);

//    accept()



    return 0;

}


