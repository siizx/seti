<<<<<<< HEAD
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#define debug 1

void dbg(char* str) {
    if (debug) printf("%s\n", str);
}

void fail(char* str) {
    fprintf(stderr, "%s\n", str);
    exit(EXIT_FAILURE);
}

void fail_errno(char* str) {
    perror(str);
    exit(EXIT_FAILURE);
}

void execPs(int pipefd[], const char ps[], const char psArg[], const char psCommandPath[]) {
    pid_t pid = fork(); // FORK()
    if (pid == -1) fail_errno("fork() failed");

    if (pid == 0) { // FIGLIO
        close(pipefd[0]); // Close the read end of the pipe in the ps process
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) fail_errno("dup2() ps failed");
        close(pipefd[1]); // Close the write end of the pipe after duplicating
        execl(psCommandPath, ps, psArg, NULL); // Execute ps aux
        fail_errno("execl(ps) failed");
    }
}

void execGrep(int pipefd[], const char grep[], const char grepCommandPath[], const char bash[]) {
    pid_t pid = fork(); // FORK()
    if (pid == -1) fail_errno("fork() failed");

    if (pid == 0) { // FIGLIO
        close(pipefd[1]); // Close the write end of the pipe in the grep process
        if (dup2(pipefd[0], STDIN_FILENO) == -1) fail_errno("dup2() grep failed");
        close(pipefd[0]); // Close the read end of the pipe after duplicating
        execl(grepCommandPath, grep, bash, NULL); // Execute grep bash
        fail_errno("execl(grep) failed");
    }
}

int main() {
    const int stdoutBackup = dup(STDOUT_FILENO);
    const int stdinBackup = dup(STDIN_FILENO);
    const char psCommandPath[] = "/usr/bin/ps";
    const char grepCommandPath[] = "/usr/bin/grep";
    const char ps[] = "ps";
    const char psArg[] = "aux";
    const char grep[] = "grep";
    const char bash[] = "bash";

    int pipefd[2];
    if (pipe(pipefd) == -1) fail_errno("pipe() failed");

    execPs(pipefd, ps, psArg, psCommandPath);
    execGrep(pipefd, grep, grepCommandPath, bash);

    close(pipefd[0]); // Close both ends of the pipe in the parent process
    close(pipefd[1]);

    wait(NULL); // Wait for both child processes to finish
    wait(NULL);

    if (dup2(stdoutBackup, STDOUT_FILENO) == -1) fail_errno("dup2 restore stdout failed");
    if (dup2(stdinBackup, STDIN_FILENO) == -1) fail_errno("dup2 restore stdin failed");

    close(stdoutBackup); // Close the backup file descriptors
    close(stdinBackup);

    return 0;
}

=======
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
>>>>>>> bac7ffa84f13f96cb75f0147d7b29cc6afff4f94
