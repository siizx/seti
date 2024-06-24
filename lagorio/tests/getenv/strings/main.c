#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

	char* tmp = "$HOME";
	char aux[sizeof(&tmp)-1]; // -1 perche' voglio togliere $
	for(int i=1; i<sizeof(&tmp); i++){
		aux[i-1] = tmp[i];
	}
	tmp = getenv(aux);
	if(!tmp) printf("getenv() failed");

	printf("%s\n", tmp);

	exit(EXIT_SUCCESS);
}
