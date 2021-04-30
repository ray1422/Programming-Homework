#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include <stdlib.h>
#include "yah.h"
int arr[LEN];

int main(int argc, char* argv[]) {
	for (int i = 0; i < LEN; i++) {
		arr[i] = rand();
	}
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
	for (int i = 0; i < LEN; i++) {
		printf("%d\n", arr[i]);
	}
}
