//
// Created by adeshchoudhar on 18/03/21.
//

#include "trie.h"

void trie_init() {
    TRIE = new_trie_node();
}

unsigned int trie_count = 0;
unsigned long int trie_memory = 0;

trie_node *new_trie_node() {
    trie_node *new_node = (trie_node *) malloc(sizeof(trie_node));
    if (!new_node) {
        trie_unload(TRIE);
        return NULL;
    }
    trie_memory += sizeof(trie_node);

    new_node->end = false;
    for (int i = 0; i < T; i++) {
        new_node->children[i] = NULL;
    }
    return new_node;
}

bool trie_load(char *dictionary) {
    FILE *file = fopen(dictionary, "r");
    if (!file) {
        return false;
    }
    char word[MAX + 1];
    while (fscanf(file, "%s", word) != EOF) {
        trie_node *current_node = TRIE, *new_node;
        for (int i = 0, c; word[i] != '\0'; i++) {
            c = (int) word[i];
            if (48 <= c && c <= 57) {
                c -= 48;
            } else if (97 <= c && c <= 122) {
                c -= 87;
            } else {
                continue;
            }

            if (current_node->children[c] == NULL) {
                new_node = new_trie_node();
                if (!new_node) {
                    trie_unload(TRIE);
                    return false;
                }
                current_node->children[c] = new_node;
            }
            current_node = current_node->children[c];
        }
        current_node->end = true;
        trie_count++;
    }

    fclose(file);
    return true;
}

bool trie_check(const char *word) {
    trie_node *current_node = TRIE;
    for (int i = 0, c; word[i] != '\0'; i++) {
        c = (int) word[i];
        if (48 <= c && c <= 57) {
            c -= 48;
        } else if (97 <= c && c <= 122) {
            c -= 87;
        } else {
            return false;
        }

        if (current_node->children[c] == NULL) {
            return false;
        }
        current_node = current_node->children[c];
    }

    if (current_node != NULL && current_node->end) {
        return true;
    }
    return false;
}

void trie_unload(trie_node *node) {
    for (int i = 0; i < T; i++) {
        if (node->children[i] != NULL) {
            trie_unload(node->children[i]);
        }
    }
    free(node);
}

DATA trie_spell_check(bool is_file, char *input) {
    unsigned int file_count = 0, misspelled_count = 0;
    clock_t load_start, load_stop, check_start, check_stop, unload_start, unload_stop;
    double load_time, check_time, unload_time;

    trie_init();

    load_start = clock();
    if (!trie_load(DICTIONARY)) {
        print_block("ERR!");
        printf("Dictionary could not be loaded!\n");
        exit(1);
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
            print_block("ERR!");
            printf("File could not be opened!\n");
        }

        char word[MAX + 1];
        int index = 0, c;
        for (c = fgetc(input_file); c != EOF; c = fgetc(input_file)) {
            if (isalnum(c) || c == '\'' || c == '.' || c == '\\' || c == '-') {
                word[index++] = (char) tolower(c);
            } else if ((c == ' ' && index) || (c == '\n' && index)) {
                word[index] = '\0';
                file_count += 1;
                index = 0;

                clean(word);

                if (!trie_check(word)) {
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
        char word[MAX + 1], c;
        int index = 0;
        for (; input[index] != '\0' && index < MAX; index++) {
            c = input[index];
            if (isalnum(c) || c == '\'' || c == '-' || c == '.' || c == '\\') {
                word[index] = input[index];
            }
        }
        word[index] = '\0';

        clean(word);

        misspelled_count = !trie_check(word);
    }
    check_stop = clock();

    unload_start = clock();
    trie_unload(TRIE);
    unload_stop = clock();

    load_time = get_time(load_start, load_stop);
    check_time = get_time(check_start, check_stop);
    unload_time = get_time(unload_start, unload_stop);

    DATA data = {is_file, trie_count, file_count, misspelled_count, load_time, check_time, unload_time, trie_memory};
    return data;
}
