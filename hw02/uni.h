#pragma once
#include <openssl/md5.h>
char *gen_unique_str(char *hashed);
char *gen_unique_mono_str(char *str);