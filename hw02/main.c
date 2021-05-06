#include <string.h>

#include "method.h"
#include "neo.h"
#include "uni.h"
#include "utils.h"

Method method;
typedef enum HashAlgo { H_NULL } HashAlgo;
HashAlgo hash_algorithm = H_NULL;
int data_size = (int)1e5;
char* (*str_gen)(char*) = gen_unique_str;
int parse_args(int argc, char* argv[]) {
    if (argc < 2) {
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
        } else if (str_eq(argv[1], "treap")) {
            // Treap
            method = m_treap;
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
    if (argc >= 4) {
        str_gen = gen_unique_mono_str;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if (parse_args(argc, argv)) {
        fprintf(stderr, "usage: %s <method> [size] [monotonic]\n", argv[0]);
        exit(1);
    }
    printf("size: %d\n", data_size);
    // generating data
    int query_idx = 0;
    int test_size = data_size / 10;
    double insert_mean = 0., query_mean = 0.;
    for (int i = 0; i < 3; i++) {  // 測 3 次
        char** query_pool =calloc(data_size, sizeof(char*));
        double insert_cost = 0., query_cost = 0.;
        void* data = method.constructor(data_size);
        double md5_cost = 0., md5_cost_local = 0.;
        TIMER(insert_cost, {
            char buf[8192];
            method.add(data, "hello");
            for (int i = 0; i < data_size - 1; i++) {
                TIMER(md5_cost_local, {
                    str_gen(buf);
                    if (rand() % 5 == 1) {
                        query_idx += 1;
                        query_idx %= test_size;
						if (query_pool[query_idx] != nil) free(query_pool[query_idx]);
                        query_pool[query_idx] = strdup(buf);
                    }
                });
                assert(method.add(data, buf) == 0);
                md5_cost += md5_cost_local;
            }
        });
        assert(method.query(data, "hello") == 1);
        TIMER(query_cost, {
            for (int i = 0; i < test_size; i++) {
                if (query_pool[i] == nil) break;
                assert(method.query(data, query_pool[i]) == 1);
            }
        });
        for (int i = 0; i < test_size; i++) {
            if (query_pool[i] == nil) continue;
            free(query_pool[i]);
        }
        method.deconstructor(data);
        insert_cost -= md5_cost;  // 減去生成 md5 的時間
        insert_mean = (insert_mean * i + insert_cost) / (i + 1);
        query_mean = (query_mean * i + query_cost) / (i + 1);
        fprintf(stderr,
                "\r"
                "(%d / 3) "
                "ins_time: %.4lfs, ins_mean: %.4lfs, que_time: %.4lfs, "
                "que_mean: %.4lfs, gen: %.4lfs",
                i+1, insert_cost, insert_mean, query_cost, query_mean, md5_cost);
        free(query_pool);
    }
    fprintf(stderr, "\n\n");
}
