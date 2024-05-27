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
#include <unistd.h>
#include <errno.h>

void fail(const char *str) {
    fprintf(stderr, "%s\n", str);
    exit(EXIT_FAILURE);
}

void fail_errno(const char *str) {
    perror(str);
    exit(EXIT_FAILURE);
}

void allocCheck(void *ptr) {
    if (!ptr) fail_errno("memory allocation failed");
}

int isStringExit(const char *str) {
    return (strcmp(str, "exit\n") == 0 || strcmp(str, "exit") == 0);
}

//  __  __       _       
// |  \/  | __ _(_)_ __  
// | |\/| |/ _` | | '_ \
// | |  | | (_| | | | | |
// |_|  |_|\__,_|_|_| |_|

int main() {
    const int sz = 256;
    const char *nano = "nano-shell $ ";
    char *userInput = calloc(sz, sizeof(char));
    allocCheck(userInput);

    while (1) {
        printf("%s", nano);
        if (fgets(userInput, sz, stdin) == NULL) {
            free(userInput);
            exit(EXIT_SUCCESS);
        }

        if (isStringExit(userInput)) {
            free(userInput);
            exit(EXIT_SUCCESS);
        }

        userInput[strcspn(userInput, "\n")] = 0; // Remove newline character

        char *path = getenv("PATH");
        if (!path) fail("getenv() failed");

        char *token = strtok(path, ":");
        char commandPath[sz];
        int found = 0;

        while (token) {
            snprintf(commandPath, sz, "%s/%s", token, userInput);
            if (access(commandPath, X_OK) == 0) {
                found = 1;
                break;
            }
            token = strtok(NULL, ":");
        }

        if (found) {
            pid_t pid = fork();
            if (pid == -1) {
                fail_errno("fork failed");
            } else if (pid == 0) {
                execl(commandPath, userInput, (char *)NULL);
                fail_errno("execl failed");
            } else {
                if (wait(NULL) == -1) {
                    fail_errno("wait failed");
                }
            }
        } else {
            fprintf(stderr, "%s: command not found\n", userInput);
        }
    }

    free(userInput);
    return 0;
}




















