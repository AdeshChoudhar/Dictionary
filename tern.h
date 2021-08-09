//
// Created by adeshchoudhar on 26/07/21.
//

#ifndef DICTIONARY_TERN_H
#define DICTIONARY_TERN_H

#include "helpers.h"

typedef struct tern_node {
    bool end;
    char character;
    struct tern_node *left;
    struct tern_node *middle;
    struct tern_node *right;
} tern_node;

tern_node *TERN;

void tern_init();
tern_node *tern_new_node(char);
tern_node *tern_insert(tern_node *, const char *);

bool tern_load(char *);
bool tern_check(const char *);
void tern_unload(tern_node *);

void tern_traversal(tern_node *, const char *);
void tern_guess(const char *);
DATA tern_spell_check(bool, char *);

#endif //DICTIONARY_TERN_H
