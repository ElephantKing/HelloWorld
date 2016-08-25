#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 40000
int main(int argc, char** argv)
{
	int sockconn;
	struct sockaddr_in servaddr;
	char buff[256];
    bzero(buff,256);
	sockconn = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	connect(sockconn, (struct sockaddr*)&servaddr,sizeof(servaddr));
	read(sockconn, buff, 256);
	printf("%d,%d,%s",strlen(buff),sizeof(buff),buff);
    return 0;
}
