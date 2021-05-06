#include "astring.h"
static int astring_hashcode(char *str) {
    int l = strlen(str);
    if (l > 6) l = 6;
    int hashcode = 0;
    for (int i = 0; i < l; i++) {
        if (hashcode > 2147483647 / 100) hashcode %= 100007;
        hashcode *= 31;
        hashcode += str[i];
    }
    return hashcode;
}

AString *astring_new(const char *const s) {
    AString *str = malloc(sizeof(AString));
    str->val = strdup(s);
    str->len = strlen(s);
    str->hashcode = astring_hashcode(str->val);
    return str;
}
void astring_del(AString *s) {
    free(s->val);
    free(s);
}
int astring_cmp(const AString *const a, const AString *const b) {
    int hd = a->hashcode - b->hashcode;
    if (hd) return hd;
    return strcmp(a->val, b->val);
}
