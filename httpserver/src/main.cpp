#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char msg[] = "Hello";
int main()
{
	int conn, listener, bytes_read;
	struct sockaddr_in addr;
	char buf[1024];

	conn = socket(AF_INET, SOCK_DGRAM, 0);
	if (conn < 0)
	{
		perror("socket");
		exit(1);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(2345);
	addr.sin_addr.s_addr = htons(INADDR_ANY);
	if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("bind_");
		exit(2);
	}
	listen(listener, 1);
	while (1)
	{
		conn = accept(listener, NULL, NULL);
		if (conn < 0)
		{
			perror("accept");
			exit(3);
		}
		while (1)
		{
			bytes_read = recv(conn, buf, 1024, 0);
			if (bytes_read <= 0)
				break;
			send(conn, buf, bytes_read, 0);
		}
		close(conn);
	}
}