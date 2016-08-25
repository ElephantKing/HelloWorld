#include <time.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#define PORT 40000
int main()
{
	int sockconn, socklisten;
	struct sockaddr_in servaddr;
	char buff[256];
	time_t ticks;
	socklisten = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	bind(socklisten, (struct sockaddr*)&servaddr, sizeof(servaddr));
	listen(socklisten, 5);
	while(1)
	{
		sockconn = accept(socklisten, (struct sockaddr*)NULL, NULL);
		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		write(sockconn, buff, strlen(buff));
		close(sockconn);
	}
	return 0;
}
