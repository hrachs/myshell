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

int builtins(char *args[]){
    if (strcmp(args[0], "exit") == 0) {
        
        myexit();
        return 0;
    } else if (strcmp(args[0], "history") == 0) {
        myhistory();
        return 0;
    } else if (strcmp(args[0], "echo") == 0) {
        myecho(args);
        return 0;
    } else if (strcmp(args[0], "cd") == 0) {
        mycd(args[1]);
        return 0;
    }else if (strcmp(args[0], "set") == 0) {
            if (args[1] == NULL) {
                printf("Usage: set NAME=VALUE\n");
                               }
            char *key = strtok(args[1], "=");
            char *value = strtok(NULL, "");
            return 0;
            if (key && value) {
                set_variable(key, value);
                return 0;
            } else {
                printf("Invalid format. Use NAME=VALUE\n");
                return 0;
            }
    } else if (strcmp(args[0], "unset") == 0) {
            if (args[1] == NULL) {
                printf("Usage: unset NAME\n");
                return 0;
            }
            unset_variable(args[1]);
            return 0;
    }else if (strcmp(args[0], "help") == 0) {
        help(args);
        return 0;
    }else if (strcmp(args[0], "pwd") == 0) {
        mypwd();
        return 0;
    }else if (strcmp(args[0], "env") == 0) {
        print_variables();
        return 0;
    }
    return 1;
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
