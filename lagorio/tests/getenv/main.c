#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    // Retrieve the value of the PATH environment variable
    char *pathBackup = getenv("PATH");
    char* singlePath = calloc(sizeof(256), sizeof(char));
	char* user = calloc(sizeof(256), sizeof(char));

    // Check if the PATH environment variable exists
   	if (pathBackup == NULL) {
       	fprintf(stderr, "PATH environment variable not found.\n");
       	exit(EXIT_FAILURE);
   	}

	while(1){
    
		printf("PD $ ");
		fgets(user, sizeof(user) -1, stdin);
		if(atoi(user) == EOF || strcmp(user, "exit")){
			
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		strcpy(singlePath, pathBackup);

		printf("Path intero: %s\n", singlePath);
		while(singlePath){
			strtok(singlePath, ":");
			printf("%s\n",singlePath);
		}

    	// Print the value of the PATH environment variable

    }
     exit(EXIT_SUCCESS);
}

