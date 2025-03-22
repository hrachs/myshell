CC = gcc
CFLAGS = -Wall -Wextra
TARGET = mysh
OBJS = main.o builtins.o executor.o utils.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) 


