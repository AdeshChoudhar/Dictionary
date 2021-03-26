//
// Created by adeshchoudhar on 18/03/21.
//

#include "hash.h"

void hash_init() {
    for (int i = 0; i < N; i++) {
        HASH[i] = NULL;
    }
}

// From Github by 'choaimeloo'
unsigned int hash_index(char *word) {
    unsigned int hash = 0;
    for (unsigned int i = 0, n = strlen(word); i < n; i++) {
        hash = (hash << 2) ^ word[i];
    }
    return hash % N;
}

unsigned int hc = 0;

unsigned int hash_count() {
    return hc;
}

bool hash_load(char *dictionary) {
    FILE *file = fopen(dictionary, "r");
    if (!file) {
        return false;
    }

    char word[MAX + 1];
    while (fscanf(file, "%s", word) != EOF) {
        hash_node *node = malloc(sizeof(hash_node));
        if (!node) {
            hash_unload();
            return false;
        }

        strcpy(node->word, word);
        unsigned int hi = hash_index(word);

        if (HASH[hi] == NULL) {
            HASH[hi] = node;
            hc++;
        } else {
            node->next = HASH[hi];
            HASH[hi] = node;
            hc++;
        }
    }

    fclose(file);
    return true;
}

bool hash_check(char *word) {
    for (int i = 0; i < MAX + 1; i++) {
        word[i] = (char)tolower(word[i]);
    }
    unsigned int hi = hash_index(word);

    hash_node *current_node = HASH[hi];
    while(current_node) {
        if (!strcmp(current_node->word, word)) {
            return true;
        }
        current_node = current_node->next;
    }
    return false;
}

bool hash_unload() {
    for (int i = 0; i < N; i++) {
        hash_node *current_node = HASH[i];
        if (current_node == NULL) {
            continue;
        }

        while (current_node->next) {
            hash_node *tmp = current_node;
            current_node = current_node->next;
            free(tmp);
        }
        free(current_node);
    }
    return true;
}

hash_process hash_spell_check(bool is_file, char *input) {
    unsigned int wc = 0, fc = 0, mc = 0;
    clock_t load_start = 0, load_stop = 0, check_start = 0, check_stop = 0, unload_start = 0, unload_stop = 0;
    double load_time = 0, check_time = 0, unload_time = 0;

    hash_init();

    load_start = clock();
    hash_load(DICTIONARY);
    load_stop = clock();

    wc = hash_count();

    check_start = clock();
    if (is_file) {
        if (is_this_a_file("../misspelled.txt")) {
            system("rm ../misspelled.txt");
        }

        FILE *input_file = fopen(input, "r");
        FILE *output_file = fopen("../misspelled.txt", "w");
        if (!input_file || !output_file) {
            printf("File could not be opened!\n");
        }

        char word[MAX + 1];
        int index = 0, c;
        for (c = fgetc(input_file); c != EOF; c = fgetc(input_file)) {
            if (isalnum(c) || c == '\'' || c == '-') {
                word[index++] = (char)tolower(c);
            }
            else if ((c == ' ' && index) || (c == '\n' && index)) {
                word[index] = '\0';
                fc += 1;
                index = 0;

                clean_word(word);

                if (!hash_check(word)) {
                    fprintf(output_file, "%s\n", word);
                    mc += 1;
                }
            }

            if (index > MAX) {
                for (c = fgetc(input_file); c != EOF; c = fgetc(input_file));
            }
        }

        fclose(input_file);
        fclose(output_file);
    } else {
        mc = !hash_check(input);
    }
    check_stop = clock();

    unload_start = clock();
    hash_unload();
    unload_stop = clock();

    load_time = get_time(load_start, load_stop);
    check_time = get_time(check_start, check_stop);
    unload_time = get_time(unload_start, unload_stop);

    hash_process hp = {is_file, wc, fc, mc, load_time, check_time, unload_time};

    return hp;
}