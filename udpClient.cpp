#include <iostream>

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
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
	char recvBuf[512];
	char sendBuf[512];

	int sock = socket( PF_INET, SOCK_DGRAM, 0 );
	if(sock < 0)
	{
		perror("socket	erro");
		exit(1);
	}

	struct sockaddr_in peerSer;
	bzero( &peerSer, sizeof( peerSer ) );
	peerSer.sin_family = AF_INET;
	inet_pton( AF_INET, ip, &peerSer.sin_addr );
	peerSer.sin_port = htons( port );
	socklen_t peerSerLength = sizeof( peerSer );
	
	for(;;)
	{
		memset(recvBuf, 0, sizeof( recvBuf ));		
		memset(sendBuf,0,sizeof(sendBuf));

		std::cin>>sendBuf;
		sendto(sock, sendBuf, strlen(sendBuf), 0, (struct sockaddr *)&peerSer, sizeof(peerSer));		

		data_read = recvfrom(sock, recvBuf, 1023, 0, (struct sockaddr*)&peerSer, 						&peerSerLength);
		recvBuf[data_read] = 0;

		std::cout<<"echo from:"<<recvBuf<<std::endl;
	}
	

	close(sock);
	

	return 0;
}
