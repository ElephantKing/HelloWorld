#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 50000
void handEcho(int sockconn)
{
	char sendBuff[256],recvBuff[256];
	bzero(sendBuff, 256);
	bzero(recvBuff, 256);
	int sendLen = 0;
	
	while( fgets(sendBuff, 256, stdin) != NULL)
	{
		write(sockconn, sendBuff, strlen(sendBuff));
		printf("have send %s\n", sendBuff);
		if( read(sockconn, recvBuff, 256) > 0)
		{
			printf("echo %d,%d,%s\n",strlen(recvBuff), sizeof(recvBuff), recvBuff);
		}
	}

}
int main(int argc, char const *argv[])
{
	int sockconn;
	struct sockaddr_in servaddr;
	sockconn = socket(AF_INET, SOCK_STREAM, 0);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	connect(sockconn, (struct sockaddr*)&servaddr, sizeof(servaddr));
	handEcho(sockconn);
	close(sockconn);
	return 0;
}