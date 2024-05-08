#include <unistd.h>
#include <stdio.h>

int main()
{

    pid_t forked = fork();

    if (forked == -1)
    {
        perror("fork failed.");
        return 0;
    }
    else if (forked == 0)
    {
    }

    return 0;
}