#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

const char *path = "hello.txt";

int main()
{
	int fd;
	void *addr;
	struct stat statbuf;
   
	if ((fd = open(path, O_RDWR)) == -1) {
		fprintf(stderr, "open error\n");
		exit(1);
	}

	if (fstat(fd, &statbuf) == -1) {
		fprintf(stderr, "fstat error\n");
		exit(1);
	}

	if ((addr = mmap(NULL, statbuf.st_size, PROT_WRITE, MAP_SHARED, fd, \
					0)) == MAP_FAILED) {
		fprintf(stderr, "mmap error\n");
		exit(1);
	}

	(*(char *)addr) = 'J';
	if (msync(addr, statbuf.st_size, MS_ASYNC) == -1) {
		fprintf(stderr, "msync error\n");
		exit(1);
	}

	return 0;
}
