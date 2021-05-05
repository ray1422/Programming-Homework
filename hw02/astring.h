#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct AString {
    char* val;
    int len;
    int hashcode;
} AString;

int astring_cmp(const AString* const a, const AString* const b);
static inline int astring_cmp_for_qsort(const void* const a,
                                        const void* const b) {
    return astring_cmp(*(AString**)a, *(AString**)b);
}
AString* astring_new(const char* const s);
void astring_del(AString* s);