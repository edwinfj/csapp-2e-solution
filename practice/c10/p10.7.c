#include "csapp.h"

int main(int argc, char **argv)
{
	int n;
	rio_t rio;
	char buf[MAXLINE];

	Rio_readinitb(&rio, STDIN_FILENO);
	while((n = rio_readnb(&rio, buf, MAXLINE)) != 0)
		rio_writen(STDOUT_FILENO, buf, n); 

}
