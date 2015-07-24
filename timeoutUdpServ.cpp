#include <iostream>

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
//using namespace std;

int main(int argc, char* argv[])
{
	
	const char* ip = "127.0.0.1";
	int port = 10001;
	int data_read = 0;
	char recvBuf[1024];
	struct timeval timeout={4,0};

	struct sockaddr_in address;
	bzero( &address, sizeof( address ) );
	address.sin_family = AF_INET;
	inet_pton( AF_INET, ip, &address.sin_addr );
	address.sin_port = htons( port );

	int sock = socket( PF_INET, SOCK_DGRAM, 0 );
	if(sock < 0)
	{
		perror("socket	erro");
		exit(1);
	}

	setsockopt(sock,SOL_SOCKET,SO_SNDTIMEO,&timeout,sizeof(timeout));
	setsockopt(sock,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout));

	int ret = bind( sock, ( struct sockaddr* )&address, sizeof( address ) );
	if(ret < 0)
	{
		perror("bind erro");
		exit(1);
	}


	struct sockaddr_in client_address;
	socklen_t client_addrlength = sizeof( client_address );
	
	for(;;)
	{
		memset(recvBuf, 0, sizeof( recvBuf ));		

		data_read = recvfrom(sock, recvBuf, 1023, 0, (struct sockaddr*)&client_address, 						&client_addrlength);

		if(data_read == 0)	break;

		recvBuf[data_read] = 0;

		std::cout<<inet_ntoa(client_address.sin_addr)<<":"<<ntohs(client_address.sin_port)<<" says:"<<recvBuf;
		

		sendto(sock, recvBuf, data_read, 0, (struct sockaddr *)&client_address, sizeof(client_address));
	}
	

	close(sock);
	

	return 0;
}
