//
// Created by adeshchoudhar on 18/03/21.
//

#ifndef DICTIONARY_TRIE_H
#define DICTIONARY_TRIE_H

#include "helpers.h"

#define T 36

typedef struct trie_node {
    bool end;
    struct trie_node *children[T];
} trie_node;

trie_node *TRIE;

void trie_init();

trie_node *new_trie_node();

bool trie_load(char *);

bool trie_check(const char *);

void trie_unload(trie_node *);

DATA trie_spell_check(bool, char *);

#endif //DICTIONARY_TRIE_H
