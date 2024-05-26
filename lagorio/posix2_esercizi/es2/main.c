// Chiede all’utente il nome di un file, usando per esempio fgets(3),
// ed esegue /bin/nome-inserito-dall’utente
// • Attenzione: non deve cercare in tutto il PATH
// • Usate valgrind/sanitizer per controllare l’uso della memoria
// – In generale, abituatevi a testare i vostri programmi con input “strani” a piacere.
// Per esempio,stringa vuota, stringhe contenenti caratteri non stampabili, 
// stringhe lunghissime.

//  ____            __      _   _        _ 
// |  _ \ ___ _ __ / _| ___| |_| |_ ___ | |
// | |_) / _ \ '__| |_ / _ \ __| __/ _ \| |
// |  __/  __/ |  |  _|  __/ |_| || (_) |_|
// |_|   \___|_|  |_|  \___|\__|\__\___/(_)
// (direi)...                                        

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
	char* full_path = calloc(sz, sizeof(char)); // FULL PATH - sz*elements of size N (char = 1 byte)
			// Qua uso calloc perche' a strncat() serve leggere \0.
			// malloc alloca la memoria ma non la pulisce, cosi' quando full_path arriva a strncat, 
			// non sa dove finisce la stringa. allora mantenendo malloc() avremmo dovuto mettere
			// \0 alla posizione 0. invece con calloc, non abbiamo questo problema perche' 
			// inizializza la memoria a \0.
	check_malloc(full_path);
	char* filename = malloc(sz);
	check_malloc(filename);

	// prendo l'input dall'utente:
	printf("Che file vuoi eseguire da /bin/ ?\n");
	filename = fgets(filename, sz, stdin);
	if(filename == NULL)
		fail("fgets() failed");
	filename[strcspn(filename, "\n")] = 0; // questo rimuove \n in filename (colpa di fgets)
	// strcspn(a,b) = scansiona 'a' fino a che non trova 'b' e ritorna il numero della posizione
	// di 'b' in 'a'

	// metto insieme le stringhe concatenandole:
	dbg_str_int("strlen(full_path) =", strlen(full_path)); // strlen = 0
	strncat(full_path, path_suffix, sz - strlen(full_path) -1);
	strncat(full_path, filename, sz - strlen(full_path) -1);
				// sz memoria totale allocata, - lunghezza di strlen (solo \0), 
				// -1 perche' deve avere lo spazio per terminare la stringa con \0
	if(debug)printf("Verra' eseguito il file '%s':\n", full_path);
	
	// FORK()
	pid_t pid = fork();
	if(pid == -1){
		// prima libero la memoria e poi chiamo fail errno.
		free(filename);
		free(full_path);
		fail_errno("fork() failed");
	}
	else if(pid == 0){
		// figlio - eseguo il file
		if(execl(full_path, filename,(char*)NULL) == -1){
			// libero la memoria e POI chiamo fail_errno():
			free(filename);
			free(full_path);
			fail_errno("execl() failed");
		}
	}
	// qui solo il padre dovrebbe vedere - (pid > 0)
	// libero la memoria che non mi serve piu':
	free(filename);
	free(full_path);
	// ora controllo lo stato di uscita del figlio:
	int wstatus;
	if(wait(&wstatus) == -1)
		fail_errno("wait() failed");
	if(WIFEXITED(wstatus))
		dbg_str_int("child exited with exit status", WEXITSTATUS(wstatus));

	dbg_str("Padre: return 0;\n");
	return 0;
}
