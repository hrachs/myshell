#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void token(char *command, char *args[MAX_ARGS]) {
    char *token = strtok(command, " ");
    int i = 0;
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
}

int exec(char *args[MAX_ARGS]) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork error");
        return -1;
    } else if (pid == 0) {
        execvp(args[0], args);
        perror("execvp error");
        exit(EXIT_FAILURE);
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
    return 1;
}
