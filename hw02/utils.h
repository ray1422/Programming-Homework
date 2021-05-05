#pragma once
#include <string.h>
#include <sys/time.h>
#include <time.h>
inline static struct timespec diff(struct timespec start, struct timespec end) {
    struct timespec temp;
    if ((end.tv_nsec - start.tv_nsec) < 0) {
        temp.tv_sec = end.tv_sec - start.tv_sec - 1;
        temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec - start.tv_sec;
        temp.tv_nsec = end.tv_nsec - start.tv_nsec;
    }
    return temp;
}
#define TIMER(v_double_var_assign, XXX)                        \
    do {                                                       \
        struct timespec start, end;                            \
        double time_used;                                      \
        clock_gettime(CLOCK_MONOTONIC, &start);                \
        XXX;                                                   \
        clock_gettime(CLOCK_MONOTONIC, &end);                  \
        struct timespec temp = diff(start, end);               \
        v_double_var_assign = time_used =                      \
            temp.tv_sec + (double)temp.tv_nsec / 1000000000.0; \
    } while (0)
