#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "yah.h"
int arr[LEN];
struct timespec diff(struct timespec start, struct timespec end) {
	struct timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}

int main(int argc, char* argv[]) {
	FILE *nilstm = fopen("/dev/null", "r");
	setvbuf( nilstm, malloc(8192000), _IOFBF, 8192000);
	for (int i = 0; i < LEN; i++) {
		arr[i] = rand();
	}
	fprintf(stderr, "data generated. start sorting:\n");
	struct timespec start, end;
	double time_used;
	clock_gettime(CLOCK_MONOTONIC, &start);
	if (!strcmp(basename(argv[0]), "mergesort")) {
		puts("m* sort");
		mergesort(arr);
	} else if (!strcmp(basename(argv[0]), "quicksort")) {
		puts("q* sort");
		quicksort(arr);

	} else if (!strcmp(basename(argv[0]), "heapsort")) {
		puts("heapsort");
		heapsort(arr);
	} else {abort();}
	clock_gettime(CLOCK_MONOTONIC, &end);
	fprintf(stderr, "done!\n");
	struct timespec temp = diff(start, end);
	
	time_used = temp.tv_sec + (double) temp.tv_nsec / 1000000000.0;
	printf("Time = %f s\n", time_used);
	
	for (int i = 0; i < LEN; i++) {
		fprintf(nilstm, "%d\n", arr[i]);
	}
	fclose(nilstm);
}
