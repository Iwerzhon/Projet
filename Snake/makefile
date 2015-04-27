CC=gcc 
CFLAGS=-W -Wall -g -std=c99 
LDFLAGS=-lm 
SRC=$(wildcard *.c) 
OBJ=$(SRC:.c=.o) 
EXEC=main

all: $(EXEC)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)  
$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
clean:
	rm *.o
