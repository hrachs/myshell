#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void sigint_handler(int signal) {
    printf("\n");
    myexit();
}
int main() {
    signal(SIGINT, sigint_handler);
    char *command = NULL;
    size_t len = 0;

    while (1) {
        printf("> ");
        ssize_t read = getline(&command, &len, stdin); // read line from stdion under this function works malloc or realloc
        if (read == -1 || command == NULL) {
            perror("getline error");
            free(command);
            exit(EXIT_FAILURE);
        }
        command[strcspn(command, "\n")] = 0;
        call_history(command);

        char *args[MAX_ARGS];
        token(command, args);

        if(builtins(args) == 0){

        }else{
            exec(args);
        }
    }
    free(command);
    return 0;
}
