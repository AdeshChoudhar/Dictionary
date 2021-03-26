//
// Created by adeshchoudhar on 18/03/21.
//

#include "helpers.h"

bool is_this_a_file(char *file) {
    if (access(file, F_OK) == -1)
        return false;
    return true;
}

ARGS parse_arguments(int argc, char *argv[]) {
    ARGS args = {.option = -1, .method = "", .word = "", .file = "", .is_file = false, .success = false};
    switch (argc) {
        case 1: {
            args.option = 0;
            args.success = true;
            break;
        }
        case 2: {
            if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
                args.option = 1;
                args.success = true;
            }
            break;
        }
        case 3: {
            if (!strcmp(argv[1], "-s")) {
                if (is_this_a_file(argv[2])) {
                    args.is_file = true;
                    args.file = argv[2];
                } else {
                    args.word = argv[2];
                }
                args.option = 2;
                args.method = DEFAULT;
                args.success = true;
            }
            break;
        }
        case 4: {
            if (!strcmp(argv[1], "-s")) {
                if (!strcmp(argv[2], "--TRIE") || !strcmp(argv[2], "--HASH")) {
                    if (is_this_a_file(argv[3])) {
                        args.is_file = true;
                        args.file = argv[3];
                    } else {
                        args.word = argv[3];
                    }
                    args.method = argv[2];
                    args.option = 3;
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

void print_block(char *block_name) {
    printf("\n");
    printf("+===========+\n");
    printf("|   %s    |\n", block_name);
    printf("+===========+\n");
    printf("\n");
}

void help() {
    print_block("HELP");
    printf("<0> Usage: ./Dictionary\n");
    printf("<1> Usage: ./Dictionary [-h/--help]\n");
    printf("<2> Usage: ./Dictionary -s [<word>/<file>]\n");
    printf("<3> Usage: ./Dictionary -s [--TRIE/--HASH] [<word>/<file>]\n");
    printf("\n");
    printf("* --TRIE would be DEFAULT.\n");
    printf("\n");
}

void get_meanings(char word[]) {
    char command[MAX + 30 + 1] = {'p', 'y', 't', 'h', 'o', 'n', ' ', '.', '.', '/', 's', 'c', 'r', 'i', 'p', 't', 's',
                                  '/', 'm', 'e', 'a', 'n', 'i', 'n', 'g', 's', '.', 'p', 'y', ' '};
    for (int i = 0; i < MAX + 1; i++) {
        command[30 + i] = word[i];
    }

    printf("\n");
    system(command);
}

void clean_word(char word[]) {
    int length;
    for(length = 0; word[length] != '\0'; length++);
    length += 1;

    bool number_flag = true;
    for (int i = 0; i < length - 1; i++) {
        if (!isdigit(word[i])) {
            number_flag = false;
            break;
        }
    }
    if (number_flag) {
        word[0] = '.';
        word[1] = '\0';
    }
}

double get_time(clock_t start, clock_t stop) {
    double time = ((double) (stop - start)) / (CLOCKS_PER_SEC / 1000.0);
    return time;
}

void time_stats(char *method, bool file, unsigned int wc, unsigned int fc, unsigned int mc, double load_time,
                double check_time, double unload_time) {
    double total_time = load_time + check_time + unload_time;

    if (!strcmp(method, "--TRIE")) {
        print_block("TRIE");
    } else if (!strcmp(method, "--HASH")) {
        print_block("HASH");
    }

    printf("WORDS IN DICTIONARY: %u\n", wc);
    printf("TIME IN LOAD: %.2lf ms\n", load_time);
    printf("TIME IN CHECK: %.2lf ms\n", check_time);
    printf("TIME IN UNLOAD: %.2lf ms\n", unload_time);
    printf("TOTAL TIME: %.2lf ms\n", total_time);

    printf("\n");
    if (file) {
        printf("WORDS IN FILE: %u\n", fc);
        printf("MISSPELLED WORDS: %u\n", mc);
    } else {
        printf("SPELLING: %s\n", mc ? "VALID" : "INVALID");
    }

    printf("\n");
}
