/*server*/

/*STRUCT TO DO: 

  SOCKET() -> BIND() -> LISTEN() -> ACCEPT()

*/

#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>


int main(){

    int connector = socket(
            AF_INET, 
            SOCK_STREAM, 
            0
        )



    return 0;

}


