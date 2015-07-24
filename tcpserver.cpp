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
	//char sendBuf[512];
	
	struct sockaddr_in address;
	bzero( &address, sizeof( address ) );
	address.sin_family = AF_INET;
	inet_pton( AF_INET, ip, &address.sin_addr );
	address.sin_port = htons( port );

	int listenfd = socket( PF_INET, SOCK_STREAM, 0 );
	assert( listenfd >= 0 );

	int ret = bind( listenfd, ( struct sockaddr* )&address, sizeof( address ) );
	assert( ret != -1 );

	ret = listen( listenfd, 5 );
	assert( ret != -1 );

	struct sockaddr_in client_address;
	socklen_t client_addrlength = sizeof( client_address );
	int sockfd = accept( listenfd, ( struct sockaddr* )&client_address, &client_addrlength );
	if( sockfd < 0 )
	{
	  std::cout<<"accept erro"<<std::endl;
	}
	else
	{
	  for(;;)
	  {   
			memset(recvBuf, 0, sizeof( recvBuf ));
			
		   data_read = recv(sockfd,recvBuf,sizeof(recvBuf),0);

			if(data_read == 0) break;
			
			recvBuf[data_read] = 0;
		   std::cout<<"from:"<<inet_ntoa(client_address.sin_addr)<<" send:"<<recvBuf<<std::endl;

			send(sockfd,recvBuf,sizeof(recvBuf),0);
	  }
	}

	close(sockfd);
	close(listenfd);

	return 0;
}
