#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>


int main(){





 open("yolo.txt", O_RDONLY);
 int err = errno;
	// QUESTO non funziona. a quanto pare, perror() e exit() devono essere consecutivi perche' esca scritto anche l'errore errno in stringa!
	//fprintf(stderr,"! ERRNO = %d\n\n", err);
	// exit(EXIT_FAILURE);
	

	// cosi' funziona perche' sono consecutivi.
// 	perror("yolo");
//  	exit(EXIT_FAILURE);

//	testo non consecutivi:

// 	perror("yolo");
//	printf(" polo\n");
//  	exit(EXIT_FAILURE);
// UUUUUHHHH???!?
// POLO VIENE STAMPATO PER ULTIMO, WTF?

 	perror("yolo\n");
	printf(" polo\n");
  	exit(EXIT_FAILURE);
// sembra che gli errori abbiano la precedenza sullo stdout, polo rimane in un buffer e viene stampato DOPO che tutti gli errori sono stati stampati.
	return 0;
}

