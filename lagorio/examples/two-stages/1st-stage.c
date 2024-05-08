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
	uid_t uid = geteuid();
	if (uid) {
		printf("Why I'm not root? Why?!?!?\n");
		exit(EXIT_FAILURE);
	}
	printf("Wooo, I'm root!\n");
	gid_t gid = getegid();
	if (setresgid(gid, gid, gid)) {
		perror("setresgid");
		exit(EXIT_FAILURE);
	}
	if (setresuid(uid, uid, uid)) {
		perror("setresuid");
		exit(EXIT_FAILURE);
	}
	execl("./2nd-stage", "2nd-stage", NULL);
	perror("exec");
}
