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
	const char* pathBackup = getenv("PATH"); // qui salvo il path, ma questa variabile non la 
											// uso con strtok, altrimenti da problemi nei loop
											// della nano bash che non ho voglia di debuggare. 
											// insomma aggiro il problema per ora...
	if(!pathBackup) exit(EXIT_SUCCESS); // controllo che getenv sia andata a buon fine.
	char * nano = "nano-shell $ ";
	bool found = false; // bool dedicato all'uso di access()
	
	char *path; // questa variabile e' quella che daro' in pasto ad strtok. 
//	allocCheck(path);
	path = strdup(pathBackup);
	if(!path) fail_errno("strdup() failed"); // strdup check

	
	while(1){ // NANO LOOP
		char* userInput ;//= (char*)malloc(sz * sizeof(char)); 
	//	dbgStr(path); // stampo l'intero path che sara' argomento di strtok
		printf(nano); // stampo "nano-shell $ "
		fgets(userInput, sz -1, stdin); // -1 perche' viene aggiunto \0
		if(feof(stdin)){
			clearerr(stdin);
			printf("\n");
			break;	
		}
		else if(isStringExit(userInput)){ 
			break;
		}
		else if(isStringEmpty(userInput)){ 
			
			free(path);
			path = strdup(pathBackup);	
			allocCheck(path);
			continue; 
		}
		userInput[strcspn(userInput,"\n")] = '\0'; //rimpiazzo \n con \0
		char* token = strtok(path, ":");
		// printf("~token after strtok(path,del): %s\n", token);
		


		do{ // cerco userinput nei paths
			
			
			

			token = strtok(NULL, ":");
			//printf("~token after strtok(NULL,del): %s\n", token);
			// access(,X_OK);
		
		}while(token && !found); // token() trovato o path finito.

		//strcat( // access result

		// dbgStr(userInput); // stampo user input 
		
		// fork()
		pid_t pid = fork();
		if(pid == -1) fail_errno("fork() failed");
		else if(pid == 0){
			//execl( // PRIMA DEVO CONCATENARE...:w
			break; // da cancellare, provvisorio
		}
		
		int wstatus;
		wait(&wstatus);
		
		free(path);
		path = strdup(pathBackup);	
		allocCheck(path);
	} // FINE NANO LOOP

	free(path);
	return 0;
}
