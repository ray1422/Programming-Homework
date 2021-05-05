#include <openssl/md5.h>

#include "neo.h"
#include "uni.h"

/*
    NULL return for fail
    hashed_str len MD5_DIGEST_LENGTH * 2 + 1
*/
char *gen_unique_str(char *hashed_str) {
    struct timespec now = {0, 0};
    clock_gettime(CLOCK_MONOTONIC, &now);
    char buf[8192];
    unsigned char hash[MD5_DIGEST_LENGTH];
    char *inp = buf;
    sprintf(buf, "%ld", now.tv_nsec);
    MD5_CTX context;
    MD5_Init(&context);
    MD5_Update(&context, inp, strlen(inp));
    MD5_Final(hash, &context);
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        hashed_str[i * 2] = hash[i] % 32 + 65;
        hashed_str[i * 2 + 1] = hash[i] / 32 + 65;
    }
    hashed_str[MD5_DIGEST_LENGTH * 2] = '\0';
    return hashed_str;
}
