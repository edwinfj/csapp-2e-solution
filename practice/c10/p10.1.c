#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	int fd1, fd2;

	fd1 = open("p10.1", O_RDONLY, 0);
	close(fd1);

	fd2 = open("p10.1", O_RDONLY, 0);
	printf("fd2 = %d\n", fd2);
	exit(0);
}
