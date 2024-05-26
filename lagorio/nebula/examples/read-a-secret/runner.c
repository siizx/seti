#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "common.h"

int main()
{
	char buf[256];
	int fd = open(SECRET_FILENAME, O_RDONLY);
	if (fd<0) {
		perror("open");
		exit(EXIT_FAILURE);
	}
	ssize_t n = read(fd, buf, sizeof(buf));
	if (n<0) {
		perror("read");
		exit(EXIT_FAILURE);
	}
	printf("The secret is %ld byte(s) long.\n", (long)n);
	uid_t uid = getuid();
	gid_t gid = getgid();
	printf("Dropping privileges...\n");
	if (setresgid(gid, gid, gid)) {
		perror("setresgid");
		exit(EXIT_FAILURE);
	}
	if (setresuid(uid, uid, uid)) {
		perror("setresuid");
		exit(EXIT_FAILURE);
	}
	execl("./stealer", "stealer", NULL);
}
