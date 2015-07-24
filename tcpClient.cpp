#include <iostream>

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <assert.h>
//using namespace std;

int main(int argc, char* argv[])
{
	const char* ip = "127.0.0.1";
	int port = 10002;
	int data_read = 0;
	char recvBuf[512];
	char sendBuf[512];

	struct sockaddr_in address;
	bzero( &address, sizeof( address ) );
	address.sin_family = AF_INET;
	inet_pton( AF_INET, ip, &address.sin_addr );
	address.sin_port = htons( port );

	int sock = socket( PF_INET, SOCK_STREAM, 0 );

	connect(sock,(struct sockaddr *)&address,sizeof(address));

	for(;;)
	{  
		memset(recvBuf, 0, sizeof( recvBuf ));		
		memset(sendBuf,0,sizeof(sendBuf));

		std::cin>>sendBuf;
		send(sock,sendBuf,sizeof(sendBuf),0);
		
		data_read = recv(sock,recvBuf,sizeof(recvBuf),0);
		recvBuf[data_read] = 0;
		std::cout<<"echo from:"<<recvBuf<<std::endl;
	}
	

	close(sock);

	return 0;
}
