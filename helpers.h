//
// Created by adeshchoudhar on 18/03/21.
//

#ifndef DICTIONARY_HELPERS_H
#define DICTIONARY_HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>

#define DICTIONARY "../dictionaries/large"
#define MAX 45
#define GNUPLOT "gnuplot -persist"

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
    unsigned long word_count;
    unsigned long file_count;
    unsigned long misspelled_count;
    double load_time;
    double check_time;
    double unload_time;
    unsigned long memory;
} DATA;

bool check_file(char *);
ARGS parse(int, char *[]);

void print_block(char *);
void throw_error(char *);

void help();

bool is_number(const char []);
void clean(char []);

void meaning(char *, char *);

double get_time(clock_t, clock_t);
void statistics(char *, DATA);
void compare(DATA, DATA, DATA);

#endif //DICTIONARY_HELPERS_H
