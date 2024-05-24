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
		// child
		if(execl("/usr/bin/ls", "ls","-l",  (char *)NULL) == -1)
			fail_errno("exec() failed");
		// test per ricordarmi se da qui in poi viene eseguito o no:
		printf("ffffffffffffffff\n"); // NO, NON viene eseguito.
	}else{
		// father - wait for child
		if(wait(&wstatus) == -1)
			fail_errno("wait() failed");
		else{
			if(WIFEXITED(wstatus))
				printf("child exited normally with exit status %d\n", WEXITSTATUS(wstatus));
		}	
	}
	return 0;
}
