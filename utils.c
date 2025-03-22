#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void myhistory() {
    int fd = open("/home/history.txt", O_RDONLY);
    if (fd < 0) {
        perror("Error opening history file");
        return;
    }
    char buffer[MAX_HISTORY];
    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        printf("%s", buffer);
    }
    if (bytes_read < 0) {
        perror("Error reading history file");
    }
    close(fd);
}

int call_history(const char *command) {
    int fd = open("/home/history.txt", O_WRONLY | O_APPEND | O_CREAT, 0666);
    if (fd < 0) {
        perror("Error opening history file");
        return -1;
    }
    dprintf(fd, "%s\n", command); //printf ---> d in descriptor
    close(fd);
    return 0;
}


