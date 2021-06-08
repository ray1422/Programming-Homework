SHELL = /bin/bash
CC ?= gcc
CFLAGS = -g -pthread -O3
SRC = $(wildcard *.c)
TARGET = $(patsubst %.c, %, $(SRC))

all: ${TARGET}

%:	%.c
	${CC} ${CFLAGS} $@.c -o $@

clean:
	rm -f ${TARGET}
