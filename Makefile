CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC = main.c
OBJ = $(SRC:.c=.o)
EXEC = main

all: $(EXEC)

start: $(EXEC)
	./$(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean

