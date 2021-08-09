//
// Created by adeshchoudhar on 26/07/21.
//

#include "tern.h"

unsigned int tern_count = 0;
unsigned long int tern_memory = 0;

void tern_init() {
    TERN = NULL;
}

tern_node *tern_new_node(char character) {
    tern_node *new_node = (tern_node *) malloc(sizeof(tern_node));
    if (!new_node) {
        tern_unload(TERN);
        return NULL;
    }
    tern_memory += sizeof(tern_node);

    new_node->end = false;
    new_node->character = character;
    new_node->left = NULL;
    new_node->middle = NULL;
    new_node->right = NULL;
    return new_node;
}

tern_node *tern_insert(tern_node *node, const char *word) {
    if (!node) {
        if (word && *word) {
            node = tern_new_node(*word);
            node->middle = tern_insert(node->middle, ++word);
            if (!node->middle) {
                node->end = true;
            }
        }
    } else if (*word == node->character) {
        node->middle = tern_insert(node->middle, ++word);
    } else if (*word < node->character) {
        node->left = tern_insert(node->left, word);
    } else {
        node->right = tern_insert(node->right, word);
    }
    return node;
}

bool tern_load(char *dictionary) {
    FILE *file = fopen(dictionary, "r");
    if (!file) {
        return false;
    }

    char word[MAX + 1];
    while (fscanf(file, "%s", word) != EOF) {
        TERN = tern_insert(TERN, word);
        tern_count += 1;
    }

    fclose(file);
    return true;
}

bool tern_check(const char *word) {
    tern_node *current_node = TERN, *previous_node = NULL;

    for (int i = 0; word[i] != '\0'; i++) {
        if (!current_node) {
            return false;
        }

        while (true) {
            previous_node = current_node;
            if (word[i] == current_node->character) {
                current_node = current_node->middle;
                break;
            } else if (word[i] < current_node->character) {
                current_node = current_node->left;
            } else {
                current_node = current_node->right;
            }
            if (!current_node) {
                return false;
            }
        }
    }

    return (previous_node && previous_node->end);
}

void tern_unload(tern_node *node) {
    if (!node) {
        return;
    }
    tern_unload(node->left);
    tern_unload(node->middle);
    tern_unload(node->right);
    free(node);
}

void tern_traversal(tern_node *node, const char *word) {
    if (node) {
        char word_copy[MAX + 1];
        int length;
        for (length = 0; word[length] != '\0'; length++) {
            word_copy[length] = word[length];
        }
        word_copy[length] = '\0';
        tern_traversal(node->left, word_copy);

        word_copy[length] = node->character;
        word_copy[length + 1] = '\0';
        if (node->end) {
            printf("%s\n", word_copy);
        }
        tern_traversal(node->middle, word_copy);

        strcpy(word_copy, word);
        tern_traversal(node->right, word_copy);
    }
}

void tern_guess(const char *word) {
    tern_init();

    if (!tern_load(DICTIONARY)) {
        throw_error("Dictionary could not be loaded!");
    }

    tern_node *current_head = TERN, *prefix_head = NULL, *previous_head = NULL;

    int i = 0;
    char word_copy[MAX + 1];
    while (word[i] != '\0') {
        if (current_head) {
            if (word[i] == current_head->character) {
                previous_head = current_head;
                current_head = current_head->middle;
                prefix_head = current_head;
                word_copy[i] = word[i];
                i += 1;
            } else if (word[i] < current_head->character) {
                current_head = current_head->left;
            } else {
                current_head = current_head->right;
            }
        } else {
            break;
        }
    }
    word_copy[i] = '\0';
    printf("\nVALID PREFIX: %s\n\n", word_copy);

    printf("DID YOU MEAN?\n\n");
    if (previous_head->end) {
        printf("%s\n", word_copy);
    }
    tern_traversal(prefix_head, word_copy);

    printf("\n");
    tern_unload(TERN);
}

DATA tern_spell_check(bool is_file, char *input) {
    unsigned int file_count = 0, misspelled_count = 0;
    clock_t load_start, load_stop, check_start, check_stop, unload_start, unload_stop;
    double load_time, check_time, unload_time;

    tern_init();

    load_start = clock();
    if (!tern_load(DICTIONARY)) {
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

        int index = 0, c;
        char word[MAX + 1];
        for (c = fgetc(input_file); c != EOF; c = fgetc(input_file)) {
            if (isalnum(c) || c == '\'' || c == '.' || c == '\\' || c == '-') {
                word[index++] = (char) tolower(c);
            } else if ((c == ' ' && index) || (c == '\n' && index)) {
                word[index] = '\0';
                clean(word);
                if (!tern_check(word)) {
                    fprintf(output_file, "%s\n", word);
                    misspelled_count += 1;
                }
                index = 0;
                file_count += 1;
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
        misspelled_count = !tern_check(word);
    }
    check_stop = clock();

    unload_start = clock();
    tern_unload(TERN);
    unload_stop = clock();

    load_time = get_time(load_start, load_stop);
    check_time = get_time(check_start, check_stop);
    unload_time = get_time(unload_start, unload_stop);

    DATA data = {is_file, tern_count, file_count, misspelled_count, load_time, check_time, unload_time, tern_memory};
    return data;
}
