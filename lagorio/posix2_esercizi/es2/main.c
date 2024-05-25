// Chiede all’utente il nome di un file, usando per esempio fgets(3),
// ed esegue /bin/nome-inserito-dall’utente
// • Attenzione: non deve cercare in tutto il PATH
// • Usate valgrind/sanitizer per controllare l’uso della memoria
// – In generale, abituatevi a testare i vostri programmi con input “strani” a piacere.
// Per esempio,stringa vuota, stringhe contenenti caratteri non stampabili, 
// stringhe lunghissime.

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool debug = false;

void dbg_str(char* str){
	if(debug){
		printf("%s\n", str);
	}
}

void dbg_str_int(char* str, int num){
	if(debug){
		printf("%s %d\n",str, num);
	}
}

int fail(char *str){
	fprintf(stderr, str);
	exit(EXIT_FAILURE);
}
int fail_errno(char *str){
	perror(str);
	exit(EXIT_FAILURE);
}

void check_malloc(void* ptr){
	if(ptr == NULL){
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
}

int main(){

	// Preparo variabili:
	unsigned int sz = 256;
	char* path_suffix = "/bin/"; // PATH SUFFIX 
	char* full_path = malloc(sz); // FULL PATH
	check_malloc(full_path);
	char* filename = malloc(sz);
	check_malloc(filename);
	char *fgets_res = malloc(sz); 
	check_malloc(fgets_res);

	// prendo l'input dall'utente:
	printf("Che file vuoi eseguire da /bin/ ?\n");
	filename = fgets(filename, sz, stdin);
	if(filename == NULL)
		fail("fgets() failed");
	filename[strcspn(filename, "\n")] = 0; // questo rimuove \n in filename (colpa di fgets)
	// strcspn(a,b) = scansiona 'a' fino a che non trova 'b' e ritorna il numero della posizione
	// di 'b' in 'a'

	// metto insieme le stringhe concatenandole:
	strncat(full_path, path_suffix, sz);
	strncat(full_path, filename, sz);
	if(debug)printf("Verra' eseguito il file '%s':\n", full_path);

	// FORK()
	pid_t pid = fork();
	if(pid == -1)
		fail_errno("fork() failed");
	else if(pid == 0){
		// figlio - eseguo il file
		if(execl(full_path, filename,(char*)NULL) == -1)
			fail_errno("execl() failed");
	}
	// qui solo il padre dovrebbe vedere - (pid > 0)
	int wstatus;
	if(wait(&wstatus) == -1)
		fail_errno("wait() failed");
	if(WIFEXITED(wstatus))
		dbg_str_int("child exited with exit status", WEXITSTATUS(wstatus));

	dbg_str("Padre: return 0;\n");
	return 0;
}
