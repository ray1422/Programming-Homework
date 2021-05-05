#include <string.h>

#include "method.h"
#include "neo.h"
#include "uni.h"

typedef struct Node {
    AString* val;
    int rnd;
    struct Node *left, *right;
} Node;
typedef struct Treap {
    Node* top;
} Treap;
static Node* node_new(AString* astr) {
    Node* n = malloc(sizeof(Node));
    n->left = n->right = nil;
    n->val = astr;
    n->rnd = rand();
    return n;
}

static void node_del(Node* n) {
    if (n == nil) return;
    node_del(n->left);
    node_del(n->right);
    if (n->val != nil) astring_del(n->val);
    free(n);
}

static void* treap_constructor() {
    Treap* treap = malloc(sizeof(Treap));
    treap->top = nil;
    return treap;
}
static void treap_deconstructor(void* n) {
    if (n == nil) return;
    Treap* treap = n;
    Node* top = treap->top;
    node_del(top);
    free(treap);
}
static void treap_rotate_l(Node** a) {
    // d = 0
    Node* b = *a;
    *a = (*a)->right;
    b->right = (*a)->left;
    (*a)->left = b;
}
static void treap_rotate_r(Node** a) {
    Node* b = *a;
    *a = (*a)->left;
    b->left = (*a)->right;
    (*a)->right = b;
}
static Node* treap_insert_astr(Node* top, AString* v) {
    if (top == nil) {
        top = node_new(v);
    } else if (astring_cmp(v, top->val) <= 0) {
        top->left = treap_insert_astr(top->left, v);
        if (top->rnd > top->left->rnd) treap_rotate_r(&top);
    } else {
        top->right = treap_insert_astr(top->right, v);
        if (top->rnd > top->right->rnd) treap_rotate_l(&top);
    }
    return top;
}

static int treap_insert(void* n, const char* const v_val) {
    Treap* treap = n;
    if (n == nil) return 1;
    treap->top = treap_insert_astr(treap->top, astring_new(v_val));
    return (treap->top == nil);
}
static Node* treap_query_astr(Node* top, AString* v) {
    if (top == nil) return nil;
    int cmp_res = astring_cmp(v, top->val);
    if (cmp_res == 0) {
        return top;
    }
    if (cmp_res < 0) {
        return treap_query_astr(top->left, v);
    } else {
        return treap_query_astr(top->right, v);
    }
}
static int treap_query(void* n, const char* v_val) {
    Treap* treap = n;
    AString* v = astring_new(v_val);
    Node* ret = treap_query_astr(treap->top, v);
    astring_del(v);
    return ret != nil;
}
Method m_treap = (Method){.constructor = treap_constructor,
                          .add = treap_insert,
                          .query = treap_query,
                          .deconstructor = treap_deconstructor};