//
// Created by adeshchoudhar on 18/03/21.
//

#ifndef DICTIONARY_HASH_H
#define DICTIONARY_HASH_H

#include "helpers.h"

#define H 1000

typedef struct hash_node {
    char word[MAX + 1];
    struct hash_node *next;
} hash_node;

hash_node *HASH[H];

void hash_init();

unsigned int hash_index(char *);

bool hash_load(char *);

bool hash_check(char *);

bool hash_unload();

DATA hash_spell_check(bool, char *);

#endif //DICTIONARY_HASH_H
