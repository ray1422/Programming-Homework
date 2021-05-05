#pragma once
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199309L
#endif
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#include "astring.h"
#include "color.h"
#include "method.h"
#define nil NULL
static inline int str_eq(const char *const x, const char *const y) {
    if (x == y) return 1;
    if (x == nil || y == nil) return 0;
    return !strcmp(x, y);
}
static inline int astr_eq(const AString *const x, const AString *const y) {
    if (x == y) return 1;
    if (x == nil || y == nil) return 0;
    return !astring_cmp(x, y);
}

#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC 1
#endif