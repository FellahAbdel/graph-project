CC = gcc -g

CFLAGS = -Wall -Wextra -W
LDFLAGS = -lm

EXEC = prog

all : $(EXEC)

prog: relations.c
	$(CC) relations.c -o prog

clean:
	rm $(EXEC)