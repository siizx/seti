#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>


int main(){
	
	pid_t pid = fork();
	
	if(pid < 0) {
		perror("fallita la fork");
		return -1;
	}
	
	
	if(pid == 0){
		pid_t thispid = getpid();
		printf("Sono il figlio, con pid #%d\n", thispid);
	}else{
		pid_t thispid = getpid();
		printf("Sono il padre con pid #%d\n", thispid);
		wait(NULL);
	}


	return 0;
}
