SHELL=/bin/bash
CC?=gcc

all: ./mergesort ./quicksort ./heapsort

help:
	echo run make run to measure the time of sorting algorithms.
./mergesort ./quicksort ./heapsort: main
	ln -s main ./mergesort
	ln -s main ./heapsort
	ln -s main ./quicksort
main:
	${CC} -o main *.c

clean:
	rm -f ./main ./mergesort ./quicksort ./heapsort

test: all
	time ./mergesort > /dev/null
	time ./quicksort > /dev/null
	time ./heapsort > /dev/null
