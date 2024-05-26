#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main() {

    const int s = 256;
    int fd = open("pippo.txt", O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);

    char *test = (char*)malloc(s * sizeof(char));
    char *buf = (char*)malloc(s * sizeof(char));

    int input_backup = dup(fileno(stdin));
    if (input_backup < 0) {
        perror("dup input");
        exit(EXIT_FAILURE);
    }

    int output_backup = dup(fileno(stdout));
    if (output_backup < 0) {
        perror("dup output");
        exit(EXIT_FAILURE);
    }

    printf("Enter a string: ");
    scanf("%s", test);
    printf("\n");

    dup2(fd, fileno(stdout));
    fprintf(stdout, "%s\n", test);
  
    // Close and reopen the file before reading
    close(fd);
    fd = open("pippo.txt", O_RDONLY);

    // Read the content into buf
    read(fd, buf, s);

    dup2(input_backup, fileno(stdin));
    dup2(output_backup, fileno(stdout));

    close(input_backup);
    close(output_backup);
    close(fd);

    printf("cat pippo.txt: %s", buf);

    free(test);
    free(buf);
    return 0;
}

