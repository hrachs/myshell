#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int main() {
    signal(SIGINT, sigint_handler);
    char *command = NULL;
    size_t len = 0;

    while (1) {
        printf("> ");
        ssize_t read = getline(&command, &len, stdin);
        if (read == -1 || command == NULL) {
            perror("getline error");
            free(command);
            exit(EXIT_FAILURE);
        }
        command[strcspn(command, "\n")] = 0;
        call_history(command);

        char *args[MAX_ARGS];
        token(command, args);

        if (strcmp(args[0], "exit") == 0) {
            free(command);
            myexit();
        } else if (strcmp(args[0], "history") == 0) {
            myhistory();
        } else if (strcmp(args[0], "echo") == 0) {
            myecho(args);
        } else if (strcmp(args[0], "cd") == 0) {
            mycd(args[1]);
        } else {
            exec(args);
        }
    }
    return 0;
}
