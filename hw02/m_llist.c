#include <string.h>

#include "neo.h"
#include "uni.h"

typedef struct Node {
    AString* val;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node *head, *tail;
} LinkedList;

static void* linked_list_constructor() {
    LinkedList* l = malloc(sizeof(LinkedList));
    Node* n = malloc(sizeof(Node));
    l->head = l->tail = n;
    n->next = NULL;
    n->val = NULL;
    return l;
}
static void linked_list_deconstructor(void* n) {
    LinkedList* l = n;
    Node* cur = l->head;
    while (cur != nil) {
        if (cur->val != nil) astring_del(cur->val);
        Node* next = cur->next;
        free(cur);
        cur = next;
    }
    free(n);
}

static int linked_list_add(void* n, const char* v) {
    if (n == nil) return 1;
    LinkedList* l = n;
    Node* cur = l->tail;
    cur->next = malloc(sizeof(Node));
    if (cur->next == nil) return 1;
    cur = cur->next;
    cur->val = astring_new(v);
    cur->next = nil;
    l->tail = cur;
    return 0;
}
static int linked_list_query(void* n, const char* v_val) {
    if (n == nil) return 0;
    AString* v = astring_new(v_val);
    LinkedList* l = n;
    Node* cur = l->head;
    while ((cur = cur->next) != nil) {
        if (astr_eq(cur->val, v)) {
            astring_del(v);
            return 1;
        }
    }
    astring_del(v);
    return 0;
}
Method m_llist = (Method){.constructor = linked_list_constructor,
                          .add = linked_list_add,
                          .query = linked_list_query,
                          .deconstructor = linked_list_deconstructor};