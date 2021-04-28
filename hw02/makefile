SHELL=/bin/bash
CC?=gcc

all: ./mergesort ./quicksort ./heapsort

help:
	echo run make run to measure the time of sorting algorithms.
./mergesort ./quicksort ./heapsort: main
	ln -sf main ./mergesort
	ln -sf main ./heapsort
	ln -sf main ./quicksort
main: $(wildcard *.c) $(wildcard *.h)
	${CC} -o main *.c -O2 -pthread

clean:
	rm -f ./main ./mergesort ./quicksort ./heapsort

test: all
	time ./mergesort > /dev/null
	time ./quicksort > /dev/null
	time ./heapsort > /dev/null
