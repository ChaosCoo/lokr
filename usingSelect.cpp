#include <iostream>

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
//using namespace std;

int main(int argc, char* argv[])
{
	const char* ip = "127.0.0.1";
	int port = 10002;
	int data_read = 0;
	char recvBuf[512];
	fd_set fds;
	int maxfdp = 0;
	char buf[10] = "";
	int keyboard; 
	char c;
	//char sendBuf[512];
	
	keyboard = open("/dev/tty",O_RDONLY | O_NONBLOCK);
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

	maxfdp = sockfd > keyboard ? sockfd : keyboard;
	
	if( sockfd < 0 )
	{
	  std::cout<<"accept erro"<<std::endl;
	}
	else
	{
	  for(;;)
	  {   
			memset(recvBuf, 0, sizeof( recvBuf ));
			memset(buf, 0, sizeof( buf ));
			FD_ZERO(&fds);
			FD_SET(sockfd,&fds);
			FD_SET(0,&fds);
			//FD_SET(keyboard,&fds);

			select(maxfdp+1,&fds,&fds,NULL,NULL);
			
			if(FD_ISSET(sockfd,&fds))
			{

				/*if(FD_ISSET(0,&fds))
			{
				
				fread(buf,9,1,stdin);
				write(1,buf,strlen(buf));
			}*/
				data_read = recv(sockfd,recvBuf,sizeof(recvBuf),0);
				
				
				if(data_read == 0) break;
			
				recvBuf[data_read] = 0;
				std::cout<<"from:"<<inet_ntoa(client_address.sin_addr)<<" send:"<<recvBuf<<std::endl;

				send(sockfd,recvBuf,sizeof(recvBuf),0);
			}
			
			
			
		   
	  }
	}

	close(sockfd);
	close(listenfd);

	return 0;
}
