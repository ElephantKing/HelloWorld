#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 40000

void handConn(int sockconn)
{
	char sendBuff[256], recvBuff[256];
	bzero(sendBuff, 256);
	bzero(recvBuff, 256);
	int recvLen = 0;
	while( (recvLen = read(sockconn, recvBuff, 256)) > 0)
	{
		printf("i have recv %s\n",recvBuff);
		write(sockconn, recvBuff, recvLen);
	}
}
int main(int argc, char const *argv[])
{
	int sockconn, socklisten;
	struct sockaddr_in servaddr;
	pid_t pid;
	socklisten = socket(AF_INET, SOCK_STREAM, 0);
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	bind(socklisten, (struct sockaddr*)&servaddr,sizeof(servaddr));
	listen(socklisten, 5);
	while(1)
	{
		sockconn = accept(socklisten, NULL, NULL);
		if((pid = fork()) == 0)
		{
			close(socklisten);
			handConn(sockconn);
			close(sockconn);
		}
		close(sockconn);
	}
	return 0;
}