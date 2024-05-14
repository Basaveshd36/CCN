#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define CHUNK 1024

void readfile(int new_sd)
	{
		char buf[CHUNK];
		int n;
		FILE *file;

		file = fopen("test.txt","r");
		if(file==NULL)
		{
		printf("\n Error in opening a file");
		}
		else
		{
		while(fgets(buf,sizeof(buf),file)!=NULL)
		{
			n=strlen(buf);
			write(new_sd,buf,n);
			bzero(buf,sizeof(buf));
		}
		}
		fclose(file);
	}

int main(int argc,char **argv)
{
	int n;
	int yes=1;
	int sd,new_sd,client_len,port;
	struct sockaddr_in server,client;
	char buf[1024];
		
	port = atoi(argv[1]);

	/*create a stream socket*/
	if((sd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		fprintf(stderr,"cant create a socket\n");
		exit(1);
	}

	/*bind an address to the socket*/

	server.sin_family = AF_INET;
	server.sin_port = port;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(setsockopt(sd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)==-1))
	{
		perror("setsockopt");
		exit(1);
	}
	
	if(bind(sd,(struct sockaddr*)&server,sizeof(server))==-1)
	{
		fprintf(stderr,"cant bind name to socket\n");
		exit(1);
	}

	/*queue up to 5 connect request*/

	listen(sd,5);
	while(1)
	{
		client_len = sizeof(client);
		if((new_sd = accept(sd,(struct sockaddr*)&client,&client_len)) == -1)
		{
			fprintf(stderr,"cant accept client\n");
			exit(1);
		}

		n = read(new_sd,buf,sizeof(buf));
		readfile(new_sd);
		close(new_sd);
	}

	close(sd);
	return(0);
	}
	

					
