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

	listener = socket(AF_INET, SOCK_STREAM, 0);
	if (listener < 0)
	{
		perror("socket");
		exit(1);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(2345);
	addr.sin_addr.s_addr = INADDR_ANY;//INADDR_LOOPBACK;//
	int errBind = bind(listener, (struct sockaddr *)&addr, sizeof(addr));
	if (errBind < 0)
	{
		close(listener);
		perror("bind");
		exit(2);
	}
	int errListen = listen(listener, 1);
	if (errListen == -1)
	{
		close(listener);
		perror("listen");
		exit(3);
	}
	while (1)
	{
		conn = accept(listener, 0, 0);
		if (conn < 0)
		{
			close(listener);
			perror("accept");
			exit(4);
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