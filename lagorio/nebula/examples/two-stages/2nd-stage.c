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
	printf("And I'm root too!\n");
}

