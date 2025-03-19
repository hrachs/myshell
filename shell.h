#ifndef SHELL_H
#define SHELL_H

#define PWD_BUFF 100
#define MAX_VARIABLES 100
#define MAX_HISTORY 1024
#define MAX_ARGS 30

typedef struct {
    char *key;
    char *value;
} variable_t;

void set_variable(char* key, char* value);
void unset_variable(char* key);
void print_variables();
void mypwd();
void mycd(char *path);
void myecho(char *args[MAX_ARGS]);
void myexit();
void myhistory();
int call_history(const char *command);
void token(char *command, char *args[MAX_ARGS]);
int exec(char *args[MAX_ARGS]);
void sigint_handler(int signal);

#endif
