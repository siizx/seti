#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


size_t size = 256;

int main(int argc, char *argv[]){

	if(argc < 2){
		fprintf(stderr, "Manca un argomento.\n");
		return 1;
	}
	
	
	char * filename = argv[1];
	unsigned int fdwrite;
	
	//if((fdwrite = open(filename, O_WRONLY | O_TRUNC)) < 0){
	if((fdwrite = open(filename, O_WRONLY | O_APPEND)) < 0) { // append vuole anche wronly
		fprintf(stderr,"Open of file, failed.\n");
		return 1;
	}

	char buf[size];
	
	printf("Cosa vuoi scrivere nel file?\n");
	///////scanf("%s", buf); questo mi salva solo una parola...
	fgets(buf, size, stdin); // questo salva tutta la frase.
	printf("\n");
	
	
	if(write(fdwrite, buf, strlen(buf)) < 0) {
		fprintf(stderr, "Write failed.\n");
		return 1;
	}
	
	close(fdwrite);

}
