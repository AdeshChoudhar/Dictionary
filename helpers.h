//
// Created by adeshchoudhar on 18/03/21.
//

#ifndef DICTIONARY_HELPERS_H
#define DICTIONARY_HELPERS_H

#define DEFAULT "TRIE"
#define DICTIONARY "../words.txt"

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

typedef struct {
    int option;
    char *method;
    char *word;
    char *file;
    bool success;
}ARGS;

bool is_file(char *);
void print_block(char *block_name);
ARGS parse_arguments(int, char *[]);
double get_time(clock_t, clock_t);
void print_time_stats(char, double, double, double);

#endif //DICTIONARY_HELPERS_H
