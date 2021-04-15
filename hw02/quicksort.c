#include "yah.h"

static void swp(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
static void quicksort_t(int *data, int left, int right); 

void quicksort(int arr[]) {
	quicksort_t(arr, 0, LEN - 1);
}


static void quicksort_t(int *data, int left, int right) {
	int pivot, i, j;
	if (left >= right) { return; }
	pivot = data[left];

	i = left + 1;
	j = right;

	while (1) {
		while (i <= right) {
			if (data[i] > pivot) {
				break;
			}

			i = i + 1;
		}

		while (j > left) {
			if (data[j] < pivot) {
				break;
			}

			j = j - 1;
		}

		if (i > j) { break; }

		swp(&data[i], &data[j]);
	}

	swp(&data[left], &data[j]);

	quicksort_t(data, left, j - 1);
	quicksort_t(data, j + 1, right);
}


