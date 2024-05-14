#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#define SERVER_TCP_PORT    5750
#define BUFLEN 256
#define MAX 90
int flag=0;

int func(int sockfd)
{
    char buff[MAX];
    int n;
    
    for(;;)
    {
    if(flag==1)
    break;
    bzero(buff,MAX);
    n= read(sockfd,buff,sizeof(buff));
    printf("Messege from client is =%s",buff);
    bzero(buff ,MAX);
    n=0;
    printf("Enter message to be send to client :/n");    
    
    fgets(buff,sizeof(buff),stdin);
    n=strlen(buff);
    if(strncmp("exit",buff,4)==0)
    {
    printf("Server Exit/n");
    flag=1;
    break;
    }
    else
    {
    write(sockfd,buff,sizeof(buff));
    bzero(buff,MAX);
    }
    }//for loop
    }
int main(int argc,char**argv)
 {
 int yes=1;
 int sd,new_sd,client_len,port;
 struct sockaddr_in server,client;
 char buff[BUFLEN];
 
 port =atoi(argv[1]); //port=5750
 if((sd = socket(AF_INET, SOCK_STREAM, 0))==-1)
     {
        fprintf(stderr,"can't create a socket\n");
        exit(1);
     }
     server.sin_family = AF_INET;
     server.sin_port = port;
     server.sin_addr.s_addr =htonl(INADDR_ANY);
     
     if(setsockopt(sd,SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) ==-1)
         {
          perror("setsockopt");
          exit(1);
        }
    
    if(bind(sd, (struct sockaddr *)&server, sizeof(server)) ==-1)
     {
           fprintf(stderr, "can't bind name to socket\n");
           exit(1);
   }
   listen(sd,5);
     while(1)
     {
         client_len = sizeof(client);
      if((new_sd = accept(sd, (struct sockaddr *) &client, &client_len))==-1)
      {
         fprintf(stderr,"can't accept client\n");
          exit(1);
      }
      func(new_sd);
      close(new_sd);
      }
  close(sd);
  return(0);
      }
