#include <stdio.h>

#include <netdb.h>

#include <netinet/in.h>

#include <unistd.h>

#include <stdlib.h>

#include <time.h>

#include <string.h>

#include <sys/socket.h>

#include <sys/types.h>

#include <stdbool.h>

#include <unistd.h>

#define MAX 100

#define PassLength 4

#define PORT 8080

#define SA struct sockaddr 







//First attack -buffer attack

bool checkPasswordB(char* submitted)

{

bool valid = 0;

char str[6]={0};
strcpy(str,submitted);

if(strcmp(str,"6480")==0)

    valid=1;

printf("buffer : str (%s), valid (%d)/n",str,valid);

return valid;

}



//timing attack

bool checkPassword(char* real, char* submitted)

{





for(int i=0 ; i< PassLength; i++){

     sleep(1);

   if(*real++ != *submitted++)

         return false;



  }

   return true;

}







void func(int sockfd) 

{ 

        char real[PassLength+1]="6480";

	char buff[MAX]; 

	int n; 

          int type;

         



	// infinite loop for chat 

	for (;;) { 

		



		// read the message from client and copy it in buffer 

                  bzero(buff, MAX); 

		read(sockfd, buff, sizeof(buff)); 



               

// buffer attack- then buffr hold 1

if(strcmp(buff,"1")==0){


//delete the data from buffer
 bzero(buff, MAX);

read(sockfd, buff, sizeof(buff)); 





if(checkPasswordB(buff)){
//delete the data from buffer

  bzero(buff, MAX); 
  //send back with buffer sucsess

  strcpy(buff,"password correct");

}



else{
//delete the data from buffer
bzero(buff, MAX); 
//send back with buffer worng

strcpy(buff,"password incorrect");



}



write(sockfd, buff, sizeof(buff)); 



}

else  if(strcmp(buff,"2")==0){





               read(sockfd, buff, sizeof(buff)); 

                printf("password From client: %s\n", buff); 

                if(checkPassword(real,buff)){

                

                 bzero(buff, MAX); 

                 strcpy(buff,"password correct");

                 write(sockfd, buff, sizeof(buff)); 



                }

                else{

                   bzero(buff, MAX); 

                  strcpy(buff,"password incorrect");

                  write(sockfd, buff, sizeof(buff)); 

                }



                



		// if msg contains "Exit" then server exit and chat ended. 

		if (strncmp("exit", buff, 4) == 0) { 

			printf("Server Exit...\n"); 

			break; 

		} 

	} 

} 

}

// Driver function 

int main() 

{ 

	int sockfd, connfd, len; 

	struct sockaddr_in servaddr, cli; 



	// socket create and verification 

	sockfd = socket(AF_INET, SOCK_STREAM, 0); 

	if (sockfd == -1) { 

		printf("socket creation failed...\n"); 

		exit(0); 

	} 

	else

		printf("Socket successfully created..\n"); 

	bzero(&servaddr, sizeof(servaddr)); 



	// assign IP, PORT 

	servaddr.sin_family = AF_INET; 

	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 

	servaddr.sin_port = htons(PORT); 



	// Binding newly created socket to given IP and verification 



	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 

		printf("socket bind failed...\n"); 

		exit(0); 

	} 

	else

		printf("Socket successfully binded..\n"); 



	// Now server is ready to listen and verification 

	if ((listen(sockfd, 5)) != 0) { 

		printf("Listen failed...\n"); 

		exit(0); 

	} 

	else

		printf("Server listening..\n"); 

	len = sizeof(cli); 



	// Accept the data packet from client and verification 

	connfd = accept(sockfd, (SA*)&cli, &len); 

	if (connfd < 0) { 

		printf("server acccept failed...\n"); 

		exit(0); 

	} 

	else

		printf("server acccept the client...\n"); 



	// Function for chatting between client and server 

	func(connfd); 



	// After chatting close the socket 

	close(sockfd); 

} 









