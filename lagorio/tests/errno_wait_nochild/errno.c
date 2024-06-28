#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){

	int pid;

	int proc = fork();
	if(proc == 0) {
			sleep(2);
			exit(EXIT_SUCCESS);
	}else{
	
	pid = wait(NULL);
	printf("pid = %d\n", pid);
	perror("errno"); // perror aggiunge automaticamente ": *error*\n".


	}
		exit(EXIT_SUCCESS);
}
