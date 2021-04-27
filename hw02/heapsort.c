#include "yah.h"
#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int idx = 0;
static inline int left(int i) {return 2 * i + 1 ;}
static inline int right(int i) {return 2 * i + 2;}
static inline int parent (int i) {assert(i>0); return (i-1) / 2;}

static inline void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void downSwap(int heap[], int i) {
    if (i*2+1 >= idx) return;
    // printf("down! p: %d, l: %d, r: %d\n", heap[i], heap[left(i)], heap[right(i)]);
    if (right(i) >= idx) {
        swap(&heap[i], &heap[left(i)]);
    };
    if (heap[i] > heap[left(i)] && heap[i] > heap[right(i)]) return;
    if (heap[left(i)] > heap[right(i)]) {
        swap(&heap[i], &heap[left(i)]);
        downSwap(heap, left(i));
    } else {
        swap(&heap[i], &heap[right(i)]);
        downSwap(heap, right(i));
    }
}

static inline int pop(int heap[]) {
    assert(idx > 0);
    int r = heap[0];
    if (idx == 1) {idx = 0; return r;}
    idx--;
    heap[0] = heap[idx];
    downSwap(heap, 0);
    return r;
}

static inline void push(int heap[], int v) {
    // printf("push[%d] %d\n", idx, v);
    int i = idx;
    while (i > 0 && heap[parent(i)] < v) {
        heap[i] = heap[parent(i)];
        i = parent(i);
    }
    heap[i] = v;
    idx++;

}

void heapsort(int heap[]) {
    srand(time(0));
    for (int i = 0; i < LEN; i++) {
        push(heap, heap[i]);
    }
    for (int i = 0 ; i < LEN; i++) {
        heap[LEN - i - 1] = pop(heap);
    }
}

