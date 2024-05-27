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
    return (strcmp(str, "exit\n") == 0);
}

int isStringEmpty(const char *str) {
    return (strcmp(str, "\n") == 0 || strcmp(str, " \n") == 0 || strcmp(str, "	\n") == 0);
}

int main() {
    const int sz = 256;
    const char *nano = "nano-shell $ ";
    char *userInput = calloc(sz, sizeof(char));
    allocCheck(userInput);
    char *mainPath = getenv("PATH");
    if (!mainPath) fail("getenv() failed");

    while (1) {
        printf("%s", nano);
        if (fgets(userInput, sz, stdin) == NULL) {
            free(userInput);
            printf("\n");
            exit(EXIT_SUCCESS);
        }

        if (isStringExit(userInput)) {
            free(userInput);
            exit(EXIT_SUCCESS);
        }
		if(isStringEmpty(userInput)) continue;
        userInput[strcspn(userInput, "\n")] = 0; // Remove newline character

        char *path = strdup(mainPath);
        allocCheck(path);

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
                free(path);
                fail_errno("fork failed");
            } else if (pid == 0) {
                execl(commandPath, userInput, (char *)NULL);
                fail_errno("execl failed");
            } else {
                if (wait(NULL) == -1) {
                    free(path);
                    fail_errno("wait failed");
                }
            }
        } else {
            fprintf(stderr, "%s: command not found\n", userInput);
        }

        free(path);
    }

    free(userInput);
    return 0;
}
