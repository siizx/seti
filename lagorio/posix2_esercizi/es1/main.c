// Esegue il comando ls -l, attraverso l’uso di fork(2) ed exec(3). 
// Notate che exec(3) documenta una
// famiglia di funzioni e scegliete quella che vi sembra pi`u comoda per il vostro caso.
// • Serve usare wait(2) in questo caso? Perch´e?
//       perche' altrimenti il processo figlio diventerebbe zombie.
// • S`ı, lo sappiamo che esiste system(3); no, non potete usarla. 
// In compenso, re-implementarsi system potrebbe essere un utile esercizio.

#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int fail(char * str){
	printf("%s\n", str);
	return EXIT_FAILURE;
}
int fail_errno(char* str){
	perror(str);
	return EXIT_FAILURE;
}	
int wstatus = 0;
int main(){

	pid_t pid = fork();

	if(pid == -1)
		fail_errno("failed fork()");
	else if(pid == 0){
		if(execl("/usr/bin/ls", "ls","-l",  (char *)NULL) == -1)
			fail_errno("exec() failed");
	}else{
		// wait for child
		if(wait(&wstatus) == -1)
			fail_errno("wait() failed");
		else{
			if(!WIFEXITED(wstatus)){
				char str[256];
				sprintf(str, "wait failed with exit status %d", WEXITSTATUS(wstatus));
				fail_errno(str);
			}
			else printf("child exited normally.\n"); 
		}	
	}
	return 0;
}
