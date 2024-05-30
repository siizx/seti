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

bool debug = false;

void dbgStr(char* str){
	if(debug)
	printf("%s\n", str);
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
	
	char *path; // questa variabile e' quella che daro' in pasto ad strtok. 
//	allocCheck(path);
	path = strdup(pathBackup);
	if(!path) fail_errno("strdup() failed"); // strdup check

	
	while(1){ // NANO LOOP

		bool found = false; // bool dedicato all'uso di access()
		char userInput[sz]; // non ci credo... la memoria dinamica mi stava facendo diventare pazzo.
		dbgStr(path); // stampo l'intero path che sara' argomento di strtok
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

		char command_path_final[sz]; // qui salvero' il path valido.
		
		while(token && !found){ // cerco userinput nei paths
			
			char command_path[sz];
			command_path[0] = '\0';
			strcat(command_path, token);
			strcat(command_path, "/"); // mancava lo slash delle directories...
			strcat(command_path, userInput);
			// ORA ho il command_path e' aggiornato e andiamo a vedere se il comando esiste
			// usando access().
			int access_res = access(command_path, X_OK);
			if(!access_res) { // se access_res == 0 vuol dire success
				found = true;
				strncpy(command_path_final, command_path, sizeof(command_path) -1);
			}
			else if(access_res == -1);// dbgStr(stderr, "access() failed. Probably because the file doesn't exist.\n");
			token = strtok(NULL, ":");
			//printf("~token after strtok(NULL,del): %s\n", token);
		
		} // token() trovato o path finito.
		
		if(found){ 	// found == true:
			// fork()
			pid_t pid = fork();
			if(pid == -1) fail_errno("fork() failed");
			else if(pid == 0){
				if(execl(command_path_final, userInput, NULL) == -1) fail_errno("execl() failed.");
			}
			
			int wstatus;
			wait(&wstatus);
			
			free(path);
			path = strdup(pathBackup);	
			allocCheck(path);
		}// fine fork() | found == true
		else if(!found){
			printf("nessun eseguibile trovato.\n");
			free(path);
			path = strdup(pathBackup);	
		}
	} // FINE NANO LOOP

	free(path);
	return 0;
}
