// All’infinito:
//	 (a) stampa un prompt (per esempio, la stringa "nano-shell $") sullo standard-output
//	 (b) chiede all’utente il nome di un file
//	 (c) se l’utente inserisce exit o EOF (premendo ctrl-D all’inizio di una nuova linea), 
// 		 esce con exit status EXIT_SUCCESS
// 	 (d) esegue /bin/nome-inserito-dall’utente, dando un appropriato 
//       messaggio di errore se l’esecuzione
// 		 fallisce. Per stampare il messaggio di errore, vedete perror(3)
// 	 (e) aspetta la terminazione del processo figlio, vedete wait(2)
// • cosa succede se non utilizzate wait?
// • Possibile migliorie: potrebbe cercare in tutto il PATH

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>

bool debug = true;

void dbgStr(char* str){
	printf("%s\n", str);
}

void dbgStrInt(char* str, int num){
	printf("%s%d\n", str, num);
}

void fail(char* str){
	fprintf(stderr, str);
	exit(EXIT_FAILURE);
}

void fail_errno(char* str){
	perror(str);
	exit(EXIT_FAILURE);
}

bool isStringEmpty(char* str){
	return (strcmp(str, " \n") == 0 || strcmp(str, "\t\n") == 0 ||strcmp(str, "\n") == 0);
}


bool isStringExit(char* str){
	return (strcmp(str, "exit\n") == 0 || atoi(str) == EOF);
}

void allocCheck(char* ptr){
	if(!ptr){ 
		perror("memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
}

int main(){

	const int sz = 256;
	char* pathBackup = getenv("PATH");
	if(!pathBackup) exit(EXIT_SUCCESS);

	bool found = false; // bool dedicato all'uso di access()
	
	char *path; // = calloc(sizeof(pathBackup, sizeof(char))); // variabile da utilizzare con strtok()
//	allocCheck(path);
	path = strdup(pathBackup);
	if(!path) fail_errno("strdup() failed");
	
	dbgStr(path);

	free(path);
	return 0;
}
