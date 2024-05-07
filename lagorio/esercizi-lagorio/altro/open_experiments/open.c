#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd;

    // con O_EXCL -> se il file esiste gia, il programma da errore.
    fd = open("example.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Write data to the file, or perform other operations
	// PREPARO LE VARIABILI NECESSARIE PER UTILIZZARE getline()
	char* buff = NULL; // creo un puntatore a char
	size_t len = 0; // creo una size_t per tenere conto della size di buff
	ssize_t line = getline(&buff, &len, stdin); // ssize_t e' il tipo restituito da getline
	if(line != -1){ // se getiline restituisce -1, vuol dire che ha fallito
		ssize_t wr = write(fd, buff, len); //
		if(wr == -1){
			perror("Write returned -1");
		}
	}else{
			perror("getline failed");
	}

	free(buff);
    close(fd);
    return 0;
}

