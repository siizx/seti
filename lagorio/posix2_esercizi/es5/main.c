// Esegue il comando ps aux | grep bash, usando, oltre a quella gi`a 
// usate precedentemente, la system-call pipe(2).
// ANCHE QUEST ULTIMO ESERCIZIO verra' implementato in maniera 'pigra' per mancanza di tempo.

#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>

#define debug 1

void dbg(char* str){
        if(debug) printf("%s\n",str);
}

void fail(char* str){
        fprintf(stderr, "%s", str);
        exit(EXIT_FAILURE);
}

void fail_errno(char* str){
        perror(str);
        exit(EXIT_FAILURE);
}

int main(){

	const char path[] = "/usr/bin/";
	const char ps[] = "ps";
	const char ps_arg[] = "aux";
	const char grep[] = "grep";
	const char bash[] = "bash";
	const int sz = 256;
	const char psCommandPath[] = "/usr/bin/ls";
	const char grepCommandPath[] = "/usr/bin/grep";
	
	pid_t pid = fork(); // FORK()
	if(pid == -1) fail_errno("fork() failed");
	
	// fork succeeded: procedo con la gestione dei file descriptors.
	int pipefd[2];
	if(pipe(pipefd) == -1) fail_errno("pipe() failed");
	

	if(!pid){ // FIGLIO
		
	}


	return 0;
}
