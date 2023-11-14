#include <unistd.h>
#include <stdio.h>

int main()
{

    int forked = fork();
    pid_t pid = getpid();

    if (forked < 0)
    {
        printf("Errore nella fork\n");
    }
    else if (forked == 0)
    {
        int parent = getppid();
        printf("Child: Il mio PID e': %d\n", pid);
        printf("Child: Il PID del mio processo padre è %d\n", parent);
    }
    else
    {
        printf("Parent: Il mio PID è %d\n", pid);
        printf("Parent: Il PID del mio figlio è %d\n", forked);
    }

    return 0;
}