SHELL=/bin/bash
CC?=gcc
CFLAGS=-O2 -Wall
LD_FLAGS=-lcrypto
OBJDIR=/tmp
SRC=$(wildcard *.c)
OBJS=$(patsubst %.c,${OBJDIR}/%.o,${SRC})
TARGET=bin/hw02

DBG_LD_FLAGS=-lcrypto
DBG_CFLAGS=-g -fsanitize=undefined -fsanitize=address -fsanitize=leak -Wall
DBG_OBJDIR=/tmp/dbg
DBG_OBJS=$(patsubst %.c,${DBG_OBJDIR}/%.o,${SRC})
DBG_TARGET=bin/hw02_debug

all: ${TARGET}
debug: ${DBG_TARGET}


${TARGET}: ${OBJS}
	mkdir -p ./bin
	${CC} ${OBJS} -o $@ ${CFLAGS} ${LD_FLAGS}


${DBG_TARGET}: ${DBG_OBJS}
	mkdir -p ./bin
	${CC} ${DBG_OBJS} -o $@ ${DBG_CFLAGS} ${DBG_LD_FLAGS}


${OBJDIR}/%.o: %.c *.h
	${CC} -c $< ${CFLAGS} -o $@


${DBG_OBJDIR}/%.o: %.c *.h
	mkdir -p ${DBG_OBJDIR}
	${CC} -c $< ${DBG_CFLAGS} -o $@


clean:
	rm -f ${TARGET} ${OBJS}
	rm -f ${DBG_TARGET} ${DBG_OBJS}