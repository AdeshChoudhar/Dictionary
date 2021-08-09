//
// Created by adeshchoudhar on 18/03/21.
//

#include "hash.h"

void hash_init() {
    for (int i = 0; i < H; i++) {
        HASH[i] = NULL;
    }
}

unsigned long hash_count = 0;
unsigned long hash_memory = 0;

hash_node *hash_new_node() {
    hash_node *new_node = malloc(sizeof(hash_node));
    if (!new_node) {
        hash_unload();
        return NULL;
    }
    hash_memory += sizeof(hash_node);

    new_node->next = NULL;
    return new_node;
}

// Posted on reddit by 'delipity'
// https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/cf9nlkn/
unsigned int hash_index(char *word) {
    unsigned int hash = 0;
    for (int i = 0, n = (int) strlen(word); i < n; i++) {
        hash = (hash << 2) ^ word[i];
    }
    return hash % H;
}

bool hash_load(char *dictionary) {
    FILE *file = fopen(dictionary, "r");
    if (!file) {
        return false;
    }

    char word[MAX + 1];
    while (fscanf(file, "%s", word) != EOF) {
        hash_node *node = hash_new_node();
        if (!node) {
            hash_unload();
            return false;
        }
        strcpy(node->word, word);
        unsigned int hi = hash_index(word);
        if (!HASH[hi]) {
            HASH[hi] = node;
        } else {
            node->next = HASH[hi];
            HASH[hi] = node;
        }
        hash_count += 1;
    }

    fclose(file);
    return true;
}

bool hash_check(char *word) {
    unsigned int index = hash_index(word);
    hash_node *current_node = HASH[index];
    while (current_node) {
        if (!strcmp(current_node->word, word)) {
            return true;
        }
        current_node = current_node->next;
    }
    return false;
}

void hash_unload() {
    for (int i = 0; i < H; i++) {
        hash_node *current_node = HASH[i];
        if (!current_node) {
            continue;
        }
        while (current_node->next) {
            hash_node *tmp = current_node;
            current_node = current_node->next;
            free(tmp);
        }
        free(current_node);
    }
}

DATA hash_spell_check(bool is_file, char *input) {
    unsigned int file_count = 0, misspelled_count = 0;
    clock_t load_start, load_stop, check_start, check_stop, unload_start, unload_stop;
    double load_time, check_time, unload_time;

    hash_init();

    load_start = clock();
    if (!hash_load(DICTIONARY)) {
        throw_error("Dictionary could not be loaded!\n");
    }
    load_stop = clock();

    check_start = clock();
    if (is_file) {
        if (check_file("../misspelled.txt")) {
            system("rm ../misspelled.txt");
        }

        FILE *input_file = fopen(input, "r");
        FILE *output_file = fopen("../misspelled.txt", "w");
        if (!input_file || !output_file) {
            throw_error("File could not be opened!\n");
        }

        char word[MAX + 1];
        int index = 0, c;
        for (c = fgetc(input_file); c != EOF; c = fgetc(input_file)) {
            if (isalnum(c) || c == '\'' || c == '.' || c == '\\' || c == '-') {
                word[index++] = (char) tolower(c);
            } else if ((c == ' ' && index) || (c == '\n' && index) /*|| (c == '-' && index)*/) {
                word[index] = '\0';
                file_count += 1;
                index = 0;

                clean(word);
                if (!hash_check(word)) {
                    fprintf(output_file, "%s\n", word);
                    misspelled_count += 1;
                }
            }
            if (index > MAX) {
                for (c = fgetc(input_file); c != EOF; c = fgetc(input_file));
            }
        }

        fclose(input_file);
        fclose(output_file);
    } else {
        int index = 0;
        char word[MAX + 1], c;
        for (; input[index] != '\0' && index < MAX; index++) {
            c = input[index];
            if (isalnum(c) || c == '\'' || c == '-' || c == '.' || c == '\\') {
                word[index] = input[index];
            }
        }
        word[index] = '\0';
        clean(word);
        misspelled_count = !hash_check(word);
    }
    check_stop = clock();

    unload_start = clock();
    hash_unload();
    unload_stop = clock();

    load_time = get_time(load_start, load_stop);
    check_time = get_time(check_start, check_stop);
    unload_time = get_time(unload_start, unload_stop);

    DATA data = {is_file, hash_count, file_count, misspelled_count, load_time, check_time, unload_time, hash_memory};
    return data;
}
