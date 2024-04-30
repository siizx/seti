#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int file_descriptor;

    file_descriptor = open("test.txt", O_RDONLY);
    if (file_descriptor < 0) {
        perror("Errore nell'apertura del file");
        return 1;
    }

    printf("Il file è stato aperto correttamente.\n");

    if (close(file_descriptor) < 0) {
        perror("Errore nella chiusura del file");
        return 1;
    }

    printf("FD closed.\n");
    printf("%d\n",file_descriptor);

    return 0;
}

