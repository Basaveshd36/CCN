#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define BUFLEN 256
#define MAX 90


int func(int sockfd)
{
    char buff[MAX];
    int n;
    
    for(;;)
    {
    bzero(buff,MAX);
   printf("Enter the message to be sent:/n"); 
    
    n=0;
     fgets(buff,sizeof(buff),stdin);
    n=strlen(buff);
    if(strncmp(buff,"exit",4)==0)
    {
    printf("Client Exit...../n");
   
    break;
    }
    n=strlen(buff);
    write(sockfd,buff,n);
    bzero(buff,sizeof(buff));
    read(sockfd,buff,sizeof(buff));
    printf("Message from server:%s",buff);
    }
    }
int main(int argc ,char**argv)
 {
 int n;
 int sd,port;
 char buff[BUFLEN];
 
 struct sockaddr_in server;
 
 
 port =atoi(argv[1]); //port=5750
 if((sd = socket(AF_INET, SOCK_STREAM, 0))==-1)
     {
        fprintf(stderr,"can't create a socket\n");
        exit(1);
     }
     
     server.sin_family = AF_INET;
     server.sin_port = port;
     server.sin_addr.s_addr =inet_addr("127.0.0.1");
    
    
    if(connect(sd, (struct sockaddr *)&server, sizeof(server)) ==-1)
     {
           fprintf(stderr, "can't connect\n");
           exit(1);
   }
   
      func(sd);
     
  close(sd);
  return(0);
      }
      
