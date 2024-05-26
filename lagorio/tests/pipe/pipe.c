#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>

unsigned int s = 256;
char* buf;
char *buf2;

int main() {
	
	buf = (char*)malloc(s*sizeof(char));
	buf2 = (char*)malloc(s*sizeof(char));
	int fd[2]; 
	pipe(fd); // fd[0] =  input ||| fd[1] =  output

	
	pid_t pid = fork();
	if(pid < 0){
		perror("fork");
		exit(EXIT_FAILURE);
	}
	
	if(pid != 0){ // PADRE
		close(fd[0]); // AL PADRE NON SERVE L'INPUT.
		printf("Cosa vuoi passare nella pipe (al figlio di questo processo)?\n");
		fgets(buf, s , stdin); // PRENDO L'INPUT DALL'UTENTE.
		write(fd[1], buf, strlen(buf)+1); // il +1 e' per l'\n
		close(fd[1]); // qua credo che si possa chiudere la pipe perche' forse la stringa e' stata gia salvata in un buffer del pipe, ma non ne sono sicuro.
		wait(NULL); // aspetto il figlio.
		
	}else{ // FIGLIO
		close(fd[1]); // al figlio non serve la write (output)
		read(fd[0], buf2, s); // scrivo fd[0] in buf2 con size s
		printf("%s", buf2); // stampo buf2
		close(fd[0]); // chiudo la pipe
	}	
	
	free(buf);
	free(buf2);

	return 0;
}
