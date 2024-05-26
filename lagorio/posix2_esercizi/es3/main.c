// All’infinito:
//	 (a) stampa un prompt (per esempio, la stringa "nano-shell $") sullo standard-output
//	 (b) chiede all’utente il nome di un file
//	 (c) se l’utente inserisce exit o EOF (premendo ctrl-D all’inizio di una nuova linea), ]
// 		esce con exit status EXIT_SUCCESS
// 	 (d) esegue /bin/nome-inserito-dall’utente, dando un appropriato messaggio di errore se l’esecuzione
// 		 fallisce. Per stampare il messaggio di errore, vedete perror(3)
// 	 (e) aspetta la terminazione del processo figlio, vedete wait(2)
// • cosa succede se non utilizzate wait?
// • Possibile migliorie: potrebbe cercare in tutto il PATH



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>

// ############## DEBUG ###################
bool debug = true;

void dbgStr(char* str){
	if(debug) printf(str);
}

void dbgStrInt(char* str, int num){
	if(debug) printf("s% %d\n", str, num);
}

// ############## FAIL ####################

void fail(char* str){
	fprintf(stderr, str);
	exit(EXIT_FAILURE);
}

void fail_errno(char* str){
	perror(str);
	exit(EXIT_FAILURE);
}

// ############## MALLOC/CALLOC CHECK

void allocCheck(char* ptr){
	if(!ptr) fail_errno("memory allocation failed");
}

void stringCheck(char* str){
	if(strcmp(str, "") == 0) printf("Empty strings are not valid.");
}

int main(){
	
	const int sz = 256; // char* max allocation size
	char* partialPath = "/bin/";
	char* nano = "nano-shell $ ";
	char* userInput = calloc(sz, sizeof(char)); // user input memory allocation
	allocCheck(userInput); // check is calloc succeded

	do{
		printf(nano); // nano-shell $
		userInput = fgets(userInput, sizeof(userInput) -1, stdin); // USER INPUT
		if(!userInput) fail("fgets() failed)"); // check if null
		else stringCheck(userInput); // check if string is ok

	}while(atoi(userInput) != EOF && userInput != "exit");
		

	return 0;
}






















