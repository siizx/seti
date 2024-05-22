// Chiede all’utente il nome di un file, usando per esempio fgets(3),
// ed esegue /bin/nome-inserito-dall’utente
// • Attenzione: non deve cercare in tutto il PATH
// • Usate valgrind/sanitizer per controllare l’uso della memoria
// – In generale, abituatevi a testare i vostri programmi con input “strani” a piacere.
// Per esempio,stringa vuota, stringhe contenenti caratteri non stampabili, 
// stringhe lunghissime.

#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

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
	printf("Hai scelto: %s", filename);
	filename[strcspn(filename, "\n")] = 0; // questo rimuove \n in filename (colpa di fgets)

	strncat(full_path, path_suffix, sz);
	strncat(full_path, filename, sz);
//	sprintf(full_path,"%s %s", path_suffix, filename);
	printf("Verra' eseguito il file '%s'\n", full_path);



	// 





	return 0;
}
