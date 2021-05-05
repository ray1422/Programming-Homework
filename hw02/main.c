#include "method.h"
#include "neo.h"
#include "uni.h"
Method method;
typedef enum HashAlgo { H_NULL } HashAlgo;
HashAlgo hash_algorithm = H_NULL;
int data_size = (int)1e5;
int parse_args(int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }
    if (argc >= 4) {
        fprintf(stderr, "sorry, hash is not implemented yet.\n");
        return 1;
    }
    if (argc >= 2) {
        if (str_eq(argv[1], "linear") || str_eq(argv[1], "line") ||
            str_eq(argv[1], "linear_search")) {
            // linear search
            method = m_linear_search;
        } else if (str_eq(argv[1], "bin_search") ||
                   str_eq(argv[1], "binary_search")) {
            // binary search
            method = m_binary_search;
        } else if (str_eq(argv[1], "llist") || str_eq(argv[1], "linked_list")) {
            // linked list
            method = m_llist;
        } else if (str_eq(argv[1], "bst") || str_eq(argv[1], "BST")) {
            // binary search tree
            method = m_bst;
        } else {
            fprintf(stderr, C_RED "unknown method: %s\n" C_RESET, argv[1]);
            fprintf(stderr, C_GRN);
            fprintf(stderr, "available methods: ");
            fprintf(stderr, C_YEL);
            fprintf(stderr, "bst linked_list binary_search linear_search\n");
            fprintf(stderr, C_RESET);

            return 1;
        }
    }
    if (argc >= 3) {
        data_size = atof(argv[2]);
        if (data_size < 1) {
            fprintf(stderr, "invalid size!\n");
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if (parse_args(argc, argv)) {
        fprintf(stderr, "usage: %s <method> [size] [hash_algorithm]\n",
                argv[0]);
        exit(1);
    }
    // generating data
    for (int i = 0; i < 10; i++) {
        printf("generating data.. (%d)\n", data_size);
        char buf[8192];
        void* data = method.constructor(data_size);
        method.add(data, "hello");
        for (int i = 0; i < data_size - 1; i++) {
            gen_unique_str(buf);
            assert(method.add(data, buf) == 0);
        }
        printf("%d\n", method.query(data, "hello"));
        method.deconstructor(data);
    }
}
