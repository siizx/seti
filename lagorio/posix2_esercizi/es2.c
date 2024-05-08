#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main()
{

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
    }
    else if (pid == 0)
    {

        char path[512] = "/bin/"; // Ensure it's large enough
        char buffer[256];

        if (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            printf("%s", buffer);
            buffer[strcspn(buffer, "\n")] = 0;
        }

        strcat(path, buffer);

        execl(path, "", NULL);
        perror("execl"); // Se execve() ritorna, allora c'è stato un errore
        printf("Child: Sono il processo figlio\n");
    }
    else
    {
        int status;
        if (wait(&status) < 0)
        { // wait() attende la terminazione del processo figlio
            perror("wait");
            exit(-1);
        }
        if (WIFEXITED(status))
        {                                                                         // WIFEXITED() ritorna true se il processo figlio è terminato normalmente
            printf("Child process exited with status %d\n", WEXITSTATUS(status)); // WEXITSTATUS() ritorna lo status del processo figlio
        }
    }

    return 0;
}