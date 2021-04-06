//
// Created by adeshchoudhar on 18/03/21.
//

#ifndef DICTIONARY_HELPERS_H
#define DICTIONARY_HELPERS_H

#define DICTIONARY "../dictionaries/large"
#define MAX 45
#define GNUPLOT "gnuplot -persist"

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
    unsigned long int memory;
} DATA;

bool check_file(char *);

ARGS parse(int, char *[]);

void print_block(char *block_name);

void meanings(const char []);

void help();

bool is_number(const char []);

void clean(char []);

double get_time(clock_t, clock_t);

void statistics(char *, DATA);

void compare(DATA, DATA);

#endif //DICTIONARY_HELPERS_H
