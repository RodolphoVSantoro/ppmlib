# Compiler
CC=gcc

# Flags
CFLAGS=-Wall -Wextra -Werror -pedantic -ansi -lm -std=c2x

default:
	$(CC) -o main main.c libppm/*.c $(CFLAGS)

run: default
	./main
