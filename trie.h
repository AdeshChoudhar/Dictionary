//
// Created by adeshchoudhar on 18/03/21.
//

#ifndef DICTIONARY_TRIE_H
#define DICTIONARY_TRIE_H

#include "helpers.h"

#define T 54

typedef struct trie_node {
    char c;
    struct trie_node *children[T];
    bool is_leaf;
} trie_node;

trie_node *TRIE;

void trie_init();

bool trie_load(char *);

bool trie_check(char *);

bool trie_unload();

DATA trie_spell_check(bool, char *);

#endif //DICTIONARY_TRIE_H
