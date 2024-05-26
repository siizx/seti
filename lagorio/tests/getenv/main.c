#include <stdio.h>
#include <stdlib.h>

int main() {
    // Retrieve the value of the PATH environment variable
    char *path = getenv("PATH");
    
    // Check if the PATH environment variable exists
    if (path == NULL) {
        fprintf(stderr, "PATH environment variable not found.\n");
        return EXIT_FAILURE;
    }
    
    // Print the value of the PATH environment variable
    printf("PATH: %s\n", path);
    
    return EXIT_SUCCESS;
}

