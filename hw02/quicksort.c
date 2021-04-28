#include <pthread.h>

#include "yah.h"

struct args {
    int *data;
    int left;
    int right;
};
static void swp(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
static void *quicksort_c(void *);

void quicksort(int arr[]) {
    quicksort_c(&(struct args){.data = arr, .left = 0, .right = LEN - 1});
}

static void *quicksort_c(void *v_args) {
    struct args *args = v_args;
    int *data = args->data, left = args->left, right = args->right;
    int pivot, i, j;
    if (left >= right) {
        return NULL;
    }
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
        if (i > j) {
            break;
        }
        swp(&data[i], &data[j]);
    }
    swp(&data[left], &data[j]);
    if (right - left > 125000) {
        pthread_t p1, p2;
        pthread_create(&p1, NULL, quicksort_c, &(struct args){.data = data, .left = left, .right = j - 1});
        pthread_create(&p2, NULL, quicksort_c, &(struct args){.data = data, .left = j + 1, .right = right});
        pthread_join(p1, NULL);
        pthread_join(p2, NULL);
    } else {
        quicksort_c(&(struct args){.data = data, .left = left, .right = j - 1});
        quicksort_c(&(struct args){.data = data, .left = j + 1, .right = right});
    }
    return NULL;
}
