#include <string.h>

#include "astring.h"
#include "method.h"
#include "neo.h"
#include "uni.h"

typedef struct BinaryArray {
    int sorted;
    int cap;
    int len;
    AString** arr;
} BinaryArray;

static void* array_constructor(int s) {
    BinaryArray* l = malloc(sizeof(BinaryArray));
    if (l == NULL) return NULL;
    l->arr = malloc(s * sizeof(AString*));
    l->cap = s;
    l->len = 0;
    l->sorted = 0;
    return l;
}
static void array_deconstructor(void* n) {
    BinaryArray* l = n;
    for (int i = 0; i < l->len; i++) astring_del(l->arr[i]);
    free(l->arr);
    free(l);
}

/*
 * @return 0: success, 1: n is nil, 2: fulled
 */
static int array_add(void* n, const char* v) {
    if (n == nil) return 1;
    BinaryArray* l = n;
    if (l->len >= l->cap) return 2;
    l->arr[l->len++] = astring_new(v);
    l->sorted = 0;
    return 0;
}
static int array_query(void* n, const char* v_tmp) {
    if (n == nil) return 0;
    AString* v = astring_new(v_tmp);
    BinaryArray* l = n;
    if (l->sorted == 0) {
        qsort(l->arr, l->len, sizeof(l->arr[0]), astring_cmp_for_qsort);
        l->sorted = 1;
    }
    AString** arr = l->arr;
    // drunk, may be BUGGY
    // binary search
    int high = l->len, low = 0, mid;
    if (high == low) {
        astring_del(v);
        return 0;
    }
    do {
        mid = (high + low) / 2;
        while (mid >= l->len) mid--;
        // fprintf(stderr, "%d %s\n", mid, arr[mid]->val);
        if (high - low == 1) {
            if (low < l->len && astring_cmp(v, arr[mid]) == 0) {
                astring_del(v);
                return 1;
            } else {
                astring_del(v);
                return 0;
            }
        }
        const int cmp_result = astring_cmp(v, arr[mid]);
        if (cmp_result == 0) {
            astring_del(v);
            return 1;
        }
        if (cmp_result < 0) {
            high = mid;
        } else {
            low = mid + 1;
        }
    } while (1);

    astring_del(v);
    return 0;
}
Method m_binary_search = (Method){.constructor = array_constructor,
                           .add = array_add,
                           .query = array_query,
                           .deconstructor = array_deconstructor};