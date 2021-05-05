#pragma once
typedef struct Method {
    void* (*constructor)(int size);
    int (*add)(void* data, const char*);    // non-zero return if error
    int (*query)(void* data, const char*);  // 1 if found, 0 if not found
    void (*deconstructor)(void* data);
} Method;

extern Method m_binary_search, m_linear_search, m_bst, m_llist;

