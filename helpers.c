//
// Created by adeshchoudhar on 18/03/21.
//

#include "helpers.h"

bool is_file(char *file) {
    if (access(file, F_OK) == -1)
        return false;
    return true;
}

void print_block(char *block_name) {
    printf("\n");
    printf("+===========+\n");
    printf("|   %s    |\n", block_name);
    printf("+===========+\n");
    printf("\n");
}

ARGS parse_arguments(int argc, char *argv[]) {
    if (argc < 1 || argc > 5) {
        printf("Usage: Wrong Number Of Arguments!\n");
    }

    ARGS args = {.option = -1, .method = "", .word = "", .file = "", .success = false};
    switch (argc) {
        case 1: {
            args.option = 0;
            args.method = DEFAULT;
            args.success = true;
            break;
        }
        case 2: {
            if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
                args.option = 1;
                args.method = DEFAULT;
                print_block("HELP");
                printf("<0> Usage: ./Dictionary\n");
                printf("<1> Usage: ./Dictionary [-h/--help]\n");
                printf("<2> Usage: ./Dictionary [--TRIE/--HASH]\n");
                printf("<3> Usage: ./Dictionary -s [<word>/<file>]\n");
                printf("<4> Usage: ./Dictionary -s [--TRIE/--HASH] [<word>/<file>]\n");
                printf("\n");
                printf("* TRIE would be DEFAULT.\n");
                printf("\n");
                args.success = true;
            }
            else if (!strcmp(argv[1], "--TRIE") || !strcmp(argv[1], "--HASH")) {
                args.option = 2;
                args.method = argv[1];
                args.success = true;
            }
            break;
        }
        case 3: {
            args.option = 3;
            args.method = DEFAULT;
            if (!strcmp(argv[1], "-s")) {
                if (is_file(argv[2])) {
                    args.file = argv[2];
                }
                else {
                    args.word = argv[2];
                }
                args.success = true;
            }
            break;
        }
        case 4: {
            args.option = 4;
            if (!strcmp(argv[1], "-s")) {
                if (!strcmp(argv[2], "--TRIE") || !strcmp(argv[2], "--HASH")) {
                    args.method = argv[2];
                    if (is_file(argv[3])) {
                        args.file = argv[3];
                    }
                    else {
                        args.word = argv[3];
                    }
                    args.success = true;
                }
            }
            break;
        }
        default: {
            break;
        }
    }

    return args;
}

double get_time(clock_t start, clock_t stop) {
    double time = ((double)(start - stop)) / (CLOCKS_PER_SEC / 1000.0);
    return time;
}

void print_time_stats(char method, double load_time, double check_time, double unload_time) {
    double total_time = load_time + check_time + unload_time;

    if (method == 'T' || method == 't') {
        print_block("TRIE");
    }
    else if (method == 'H' || method == 'h'){
        print_block("HASH");
    }

    printf("TIME IN LOAD: %.2lf ms\n", load_time);
    printf("TIME IN CHECK: %.2lf ms\n", check_time);
    printf("TIME IN UNLOAD: %.2lf ms\n", unload_time);
    printf("TOTAL TIME: %.2lf ms\n", total_time);

    printf("\n");
}
