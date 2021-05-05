#include <string.h>

#include "method.h"
#include "neo.h"
#include "uni.h"

typedef struct Node {
    AString* val;
    struct Node *left, *right;
} Node;
typedef struct BST {
    Node* top;
} BST;
static Node* node_new(AString* astr) {
    Node* n = malloc(sizeof(Node));
    n->left = n->right = nil;
    n->val = astr;
    return n;
}

static void node_del(Node* n) {
    if (n == nil) return;
    node_del(n->left);
    node_del(n->right);
    if (n->val != nil) astring_del(n->val);
    free(n);
}

static void* bst_constructor() {
    BST* bst = malloc(sizeof(BST));
    bst->top = nil;
    return bst;
}
static void bst_deconstructor(void* n) {
    if (n == nil) return;
    BST* bst = n;
    Node* top = bst->top;
    node_del(top);
    free(bst);
}

static Node* bst_insert_astr(Node* top, AString* v) {
    if (top == nil) {
        top = node_new(v);
    } else if (astring_cmp(v, top->val) <= 0) {
        top->left = bst_insert_astr(top->left, v);
    } else {
        top->right = bst_insert_astr(top->right, v);
    }
    return top;
}

static int bst_insert(void* n, const char* const v_val) {
    BST* bst = n;
    if (n == nil) return 1;
    bst->top = bst_insert_astr(bst->top, astring_new(v_val));
    return 0;
}
static Node* bst_query_astr(Node* top, AString* v) {
    if (top == nil) return nil;
    int cmp_res = astring_cmp(v, top->val);
    if (cmp_res == 0) {
        return top;
    }
    if (cmp_res < 0) {
        return bst_query_astr(top->left, v);
    } else {
        return bst_query_astr(top->left, v);
    }
}
static int bst_query(void* n, const char* v_val) {
    BST* bst = n;
    AString* v = astring_new(v_val);
    Node* ret = bst_query_astr(bst->top, v);
    astring_del(v);
    return ret != nil;
}
Method m_bst = (Method){.constructor = bst_constructor,
                        .add = bst_insert,
                        .query = bst_query,
                        .deconstructor = bst_deconstructor};