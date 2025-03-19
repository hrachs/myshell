CC = gcc
CFLAGS = -Wall -Wextra

all: mysh

mysh: main.o builtins.o executor.o utils.o
	$(CC) $(CFLAGS) -o mysh main.o builtins.o executor.o utils.o

%.o: %.c shell.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o mysh
