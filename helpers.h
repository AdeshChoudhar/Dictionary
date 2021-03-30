//
// Created by adeshchoudhar on 18/03/21.
//

#ifndef DICTIONARY_HELPERS_H
#define DICTIONARY_HELPERS_H

#define DEFAULT "--TRIE"
#define DICTIONARY "../dictionaries/large"
#define MAX 45

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

typedef struct {
    int option;
    char *method;
    char *word;
    char *file;
    bool is_file;
    bool success;
} ARGS;

typedef struct {
    bool is_file;
    unsigned int word_count;
    unsigned int file_count;
    unsigned int misspelled_count;
    double load_time;
    double check_time;
    double unload_time;
} DATA;

bool is_this_a_file(char *);

ARGS parse_arguments(int, char *[]);

void print_block(char *block_name);

void help();

void get_meanings(const char []);

bool is_number(char []);

void clean(char []);

double get_time(clock_t, clock_t);

void time_stats(char *, bool file, unsigned int, unsigned int, unsigned int, double, double, double);

#endif //DICTIONARY_HELPERS_H
