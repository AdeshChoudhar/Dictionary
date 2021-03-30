//
// Created by adeshchoudhar on 18/03/21.
//

#include "trie.h"

void trie_init() {
    TRIE = NULL;
}

unsigned int trie_count = 0;

bool trie_load(char *dictionary) {
    FILE *file = fopen(dictionary, "r");
    if (!file) {
        return false;
    }
    char word[MAX + 1];
    while (fscanf(file, "%s", word) != EOF) {
        // TODO
    }

    fclose(file);
    return true;
}

bool trie_check(char *word) {
    return true;
}

bool trie_unload() {
    return true;
}

DATA trie_spell_check(bool is_file, char *input) {
    DATA data = {.is_file = is_file, .word_count = trie_count};
    return data;
}
