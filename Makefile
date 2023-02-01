# Compiler
CC=gcc

# Flags
CFLAGS=-Wall -Wextra -Werror -pedantic -ansi -lm -std=c2x

default:
	$(CC) -o main main.c lib/arq.c lib/libppm.c lib/manipppm.c lib/criappm.c lib/listappm.c $(CFLAGS)
