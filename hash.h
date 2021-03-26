//
// Created by adeshchoudhar on 18/03/21.
//

#ifndef DICTIONARY_HASH_H
#define DICTIONARY_HASH_H

#include "helpers.h"

#define N 1000

typedef struct hash_node {
    char word[MAX + 1];
    struct hash_node *next;
} hash_node;

hash_node *HASH[N];

typedef struct hash_process {
    bool is_file;
    unsigned int wc;
    unsigned int fc;
    unsigned int mc;
    double load_time;
    double check_time;
    double unload_time;
}hash_process;

void hash_init();

unsigned int hash_index(char *);

unsigned int hash_count();

bool hash_load(char *);

bool hash_check(char *);

bool hash_unload();

hash_process hash_spell_check(bool, char *);

#endif //DICTIONARY_HASH_H
