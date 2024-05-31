#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void run_ps(int pipefd[]) {
    // Close the read end of the pipe in the ps process
    close(pipefd[0]);
    // Redirect stdout to the write end of the pipe
    dup2(pipefd[1], STDOUT_FILENO);
    // Close the write end of the pipe as it's duplicated now
    close(pipefd[1]);
    // Execute ps aux
    execlp("ps", "ps", "aux", NULL);
    // If execlp fails
    perror("execlp");
    exit(EXIT_FAILURE);
}

void run_grep(int pipefd[]) {
    // Close the write end of the pipe in the grep process
    close(pipefd[1]);
    // Redirect stdin to the read end of the pipe
    dup2(pipefd[0], STDIN_FILENO);
    // Close the read end of the pipe as it's duplicated now
    close(pipefd[0]);
    // Execute grep bash
    execlp("grep", "grep", "bash", NULL);
    // If execlp fails
    perror("execlp");
    exit(EXIT_FAILURE);
}

int main() {
    int pipefd[2];
    pid_t pid1, pid2;

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork the first child for ps
    if ((pid1 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // In the first child process
        run_ps(pipefd);
    }

    // Fork the second child for grep
    if ((pid2 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        // In the second child process
        run_grep(pipefd);
    }

    // Close both ends of the pipe in the parent process
    close(pipefd[0]);
    close(pipefd[1]);

    // Wait for both child processes to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
