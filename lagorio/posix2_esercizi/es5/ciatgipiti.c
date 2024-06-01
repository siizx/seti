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

