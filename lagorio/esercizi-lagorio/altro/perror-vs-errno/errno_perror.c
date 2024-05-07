#include <stdio.h>
#include <errno.h>

int main() {
    FILE *fp;

    // Attempt to open a file that doesn't exist
    fp = fopen("nonexistent_file.txt", "r");

    if (fp == NULL) {
        // Using perror to print error message
        perror("Error opening file");

        // Using errno for custom error handling
        if (errno == ENOENT) {
            printf("File not found\n");
        } else {
            printf("Error opening file: Unknown error\n");
        }

        // Additional error handling or cleanup
        return 1; // Exit with error status
    }

    // File opened successfully
    printf("File opened successfully\n");

    fclose(fp); // Close the file
    return 0; // Exit with success status
}

