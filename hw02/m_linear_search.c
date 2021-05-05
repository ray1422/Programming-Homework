#include <string.h>

#include "neo.h"
#include "uni.h"

typedef struct LinearArray {
    int cap;
    int len;
    AString** arr;
} LinearArray;

static void* array_constructor(int s) {
    LinearArray* l = malloc(sizeof(LinearArray));
    l->arr = malloc(s * sizeof(char*));
    l->cap = s;
    l->len = 0;
    return l;
}
static void array_deconstructor(void* n) {
    LinearArray* l = n;
    for (int i = 0; i < l->len; i++) astring_del(l->arr[i]);
    free(l->arr);
    free(l);
}

/*
 * @return 0: success, 1: n is nil, 2: fulled
 */
static int array_add(void* n, const char* v) {
    if (n == nil) return 1;
    LinearArray* l = n;
    if (l->len >= l->cap) return 2;
    l->arr[l->len++] = astring_new(v);
    return 0;
}
static int array_query(void* n, const char* v_val) {
    if (n == nil) return 0;
    AString* v = astring_new(v_val);
    LinearArray* l = n;
    for (int i = 0; i < l->len; i++) {
        if (astring_cmp(v, l->arr[i]) == 0) {
            astring_del(v);
            return 1;
        }
    }
    astring_del(v);
    return 0;
}
Method m_linear_search = (Method){.constructor = array_constructor,
                                  .add = array_add,
                                  .query = array_query,
                                  .deconstructor = array_deconstructor};