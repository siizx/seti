#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "common.h"

int main()
{
	printf("Trying to steal the secret...\n");
	char buf[256];
	int fd = open(SECRET_FILENAME, O_RDONLY);
	if (fd<0) {
		perror("open");
		exit(EXIT_FAILURE);
	}
	ssize_t n = read(fd, buf, sizeof(buf)-1);
	if (n<0) {
		perror("read");
		exit(EXIT_FAILURE);
	}
	buf[n] = 0;
	printf("The secret is: %s\n", buf);
}
