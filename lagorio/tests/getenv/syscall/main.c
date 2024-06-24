#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {

	const int sz = 256;
	char* userInput = calloc(sz, sizeof(char));

	char* cwd = calloc(sz, sizeof(char)); 
	cwd = getcwd(cwd,sz);
	printf("ReetHard:%s$ ", cwd);
	fgets(userInput, sizeof(userInput) -1, stdin);
	printf("\n");	

	userInput[strcspn(userInput, "\n")] = 0;

	char* env = getenv(userInput);
	if (env != NULL) {
		printf("%s\n", env);
	} else {
		printf("Environment variable not found\n");
	}
	//free(env);
	free(cwd);
	free(userInput);
    exit(EXIT_SUCCESS);
}

