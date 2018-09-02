#include "csapp.h"

int main(int argc, char **argv)
{
	int n, fd;
	rio_t rio;
	char buf[MAXLINE];

	if (argc == 2) {
		fd = open(argv[1], O_RDONLY, 0);
		dup2(fd, STDIN_FILENO);
	}

	Rio_readinitb(&rio, STDIN_FILENO);
	while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
		Rio_writen(STDOUT_FILENO, buf, n);

}
