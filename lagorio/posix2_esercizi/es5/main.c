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

void execPs(int pipefd[], const char ps[], const char psArg[],const char psCommandPath[]){

	close(pipefd[0]); // chiudo l'fd di lettura

	pid_t pid = fork(); // FORK()
	if(pid == -1) fail_errno("fork() failed");
	// fork succeeded: procedo con la gestione dei file descriptors.
	if(!pid){ // FIGLIO
		if(dup2(pipefd[1], STDIN_FILENO) == -1) fail_errno("dup2() ps failed");
		if(execl(psCommandPath, ps, psArg, NULL) == -1) fail_errno("execl(ps) failed");
	}
}

void execGrep(int pipefd[], const char grep[], const char grepCommandPath[], const char bash[]){

	close(pipefd[1]); // chiudo l'fd di scrittura
	pid_t pid = fork(); // FORK()
	if(pid == -1) fail_errno("fork() failed");
	// fork succeeded: procedo con la gestione dei file descriptors.
	if(!pid){ // FIGLIO
		if(dup2(STDOUT_FILENO, pipefd[0]) == -1) fail_errno("dup2() grep failed");
		if(execl(grepCommandPath, grep, bash, NULL) == -1) fail_errno("grep() failed");
	}
}

int main(){
	
	const int stdoutBackup = dup(STDOUT_FILENO);
	const int stdinBackup = dup(STDIN_FILENO);
	const char path[] = "/usr/bin/";
	const char ps[] = "ps";
	const char psArg[] = "aux";
	const char grep[] = "grep";
	const char bash[] = "bash";
	const int sz = 256;
	const char psCommandPath[] = "/usr/bin/ps";
	const char grepCommandPath[] = "/usr/bin/grep";
	
	int pipefd[2];	
	if(pipe(pipefd) == -1) fail_errno("pipe() failed");
	
	execPs(pipefd, ps, psArg, psCommandPath);
	execGrep(pipefd, grep, grepCommandPath, bash);
	wait(NULL);	
	wait(NULL);

	close(pipefd[0]);
	close(pipefd[1]);
	if(!pid){ // FIGLIO
				
	}

	if(dup2(stdoutBackup, STDOUT_FILENO) == -1) fail_errno("dup2 restore stdout failed");
	if(dup2(stdinBackup, STDIN_FILENO) == -1) fail_errno("dup2 restore stdin failed");
	return 0;
}
