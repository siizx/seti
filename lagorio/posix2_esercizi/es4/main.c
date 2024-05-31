// Esegue il comando ls -l > filename;
// ovvero esegue il comando ls con argomento -l redirezionando il suo
// standard-output nel file di nome filename, che riceverete come primo argomento 
// dalla linea di comando (ovvero, argv[1]);
// oltre alle system-call gi`a usate per gli esercizi precedenti,
// vi serviranno close(2) e dup(2), oppure dup2(2).

// PER MANCANZA DI TEMPO implementero' in maniera "pigra", concentrandomi sulle nuove system call.
 
//  _____     _   _        _ 
// |  ___|_ _| |_| |_ ___ | |
// | |_ / _` | __| __/ _ \| |
// |  _| (_| | |_| || (_) |_|
// |_|  \__,_|\__|\__\___/(_)
                          

#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>

#define debug  0

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

int main(int argc, char* argv[]){
	
	if(argc != 2) fail("Errore: nessun/troppi argomento/i. Questo programma ha bisogno di un nome di un file a cui verra' reindirizzato l'output\n");

	int sz = 256;
	char path_ls[] = "/usr/bin/ls";
	char list[] = "ls";
	char argo[] = "-l";
	char filename[sz];

	strcpy(filename, argv[1]);

	dbg(filename);
	
	pid_t pid = fork(); // FORK()

	// DUP
	int stdout_fd_backup = dup(STDOUT_FILENO);
	if (stdout_fd_backup == -1) fail_errno("dup() failed");
	
	// OPEN
	int fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if(fd == -1) fail_errno("open() failed");
	
	if(pid == -1) fail_errno("fork() failed\n"); // se fork e' fallita, esco.
	else if(!pid){ // FIGLIO
		// redireziono l'output nel file scelto
		if(dup2(fd,STDOUT_FILENO) == -1) fail_errno("dup2() failed");
		// eseguo il comando:
		if(execl(path_ls, list, argo, NULL) == -1) fail_errno("execl() failed");
	} // FINE FIGLIO
	// DA QUI IN POI: PADRE
	int wstatus;
	wait(&wstatus);
	// metto a posto stdout:
	if(dup2(STDOUT_FILENO, stdout_fd_backup) == -1) fail_errno("dup2() failed");
	// qui controllo il codice di uscita del figlio (da aggiungere)
	
	close(fd);
	close(stdout_fd_backup);
	
	dbg("~fatto\n");
	return 0;
}
