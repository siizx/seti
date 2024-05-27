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
#include <fcntl.h>

// ############## DEBUG ###################
bool debug = true;

void dbgStr(char* str){
	if(debug) printf("%s\n",str);
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

// ########### STRINGS CHECKING FUNCTIONS ################

void exitSuccess(){
	printf("\n");
	exit(EXIT_SUCCESS);
}

int isStringExit(char* str){
	if(atoi(str) == EOF || strcmp(str, "exit\n") == 0){ 
		dbgStr("user exited the program.");
		return 1;
	} else return 0;
}

int isStringEmpty(char* str){
	if(strcmp(str, " \n") == 0 || strcmp(str, "\n") == 0 || strcmp(str, "") == 0 || strcmp(str, "\t") == 0) return 0;
	else return 1;
}

//  __  __       _       
// |  \/  | __ _(_)_ __  
// | |\/| |/ _` | | '_ \
// | |  | | (_| | | | | |
// |_|  |_|\__,_|_|_| |_|

int main(){
	
	const int sz = 256; // char* max allocation size
	char* partialPath = "/bin/";
	char* nano = "nano-shell $ ";
	char* PATH = getenv("PATH");	
	if(!PATH) fail("getenv() failed\n");

	char* userInput = calloc(sz, sizeof(char)); // user input memory allocation
	allocCheck(userInput); // check is calloc succeded

	do{
		printf(nano); // nano-shell $
		userInput = fgets(userInput, sizeof(userInput) -1, stdin); // USER INPUT
		if(userInput == NULL) {
			free(userInput);
			exitSuccess();
		}
		else if(isStringExit(userInput)) {
			free(userInput);
			exitSuccess();
		}
		// la stringa ha passato i check. proseguo con l'esecuzione:
		
		char* token; // stringa per salvare i singoli paths
		char* delim = ":"; // delimitatore
		token = strtok(PATH,delim); // token dove salvo i singoli path una volta parsato PATH
					// praticamente la stringa intera di PATH viene salvata in un buffer da strtok()
					// quindi token lo posso usare per salvare i suoi risultati.
		while(token && !isStringEmpty(userInput)){
			dbgStr(token);
			token = strtok(NULL, delim);
		}
		// trovato access -> eseguo fork e exec:




		userInput[0] = '\0';
		free(token);
		PATH = getenv("PATH");
		//token = calloc(sizeof(PATH)+1, sizeof(char));
		//allocCheck(token);
		//if(strcpy(token, PATH) <= 0) fail("strcpy() failed");
	// end nano loop
	}while(atoi(userInput) != EOF && strcmp(userInput, "exit\n"));
		
	// libero la memoria che non mi serve piu'
	free(userInput);
	return 0;
}






















