#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int fd, ret;
	struct stat mstat;
	void *ptr;
	size_t size;
   
	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "open error\n");
		exit(1);
	}

	if (fstat(fd, &mstat) == -1) {
		fprintf(stderr, "fstat error\n");
		exit(1);
	}
	size = (size_t)mstat.st_size;

	ptr = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (ptr == MAP_FAILED) {
		fprintf(stderr, "mmap error\n");
		exit(1);
	}

	fwrite(ptr, size, 1, stdout);
	close(fd);

	return 0;
}
