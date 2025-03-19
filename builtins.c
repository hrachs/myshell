#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

variable_t variables[MAX_VARIABLES]; 
int var_count = 0;

void set_variable(char* key, char* value) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].key, key) == 0) {
            free(variables[i].value);  
            variables[i].value = strdup(value);  
            return;
        }
    }
    if (var_count < MAX_VARIABLES) {
        variables[var_count].key = strdup(key);
        variables[var_count].value = strdup(value);
        var_count++;
    } else {
        fprintf(stderr, "Max variable limit reached!\n");
    }
}

void unset_variable(char* key) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].key, key) == 0) {
            free(variables[i].key);   
            free(variables[i].value); 
            for (int j = i; j < var_count - 1; j++) {
                variables[j] = variables[j + 1];  
            }
            var_count--;
            return;
        }
    }
}

void print_variables() {
    for (int i = 0; i < var_count; i++) {
        printf("%s=%s\n", variables[i].key, variables[i].value);
    }
}

void mypwd() {
    char pwd[PWD_BUFF];
    if (getcwd(pwd, PWD_BUFF)) {
        printf("%s\n", pwd);
    } else {
        perror("getcwd error");
    }
}

void mycd(char *path) {
    if (path == NULL || chdir(path) != 0) {
        perror("cd error");
    }
}

void myecho(char *args[MAX_ARGS]) {
    for (int i = 1; args[i] != NULL; i++) {
        if (args[i][0] == '$') {
            char *var_name = args[i] + 1;
            int found = 0;
            for (int j = 0; j < var_count; j++) {
                if (strcmp(variables[j].key, var_name) == 0) {
                    printf("%s ", variables[j].value);
                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf("$%s ", var_name);
            }
        } else {
            printf("%s ", args[i]);
        }
    }
    printf("\n");
}

void myexit() {
    for (int i = 0; i < var_count; i++) {
        free(variables[i].key);
        free(variables[i].value);
    }
    remove("/home/history.txt");
    printf("Exiting shell...\n");
    exit(EXIT_SUCCESS);
}
