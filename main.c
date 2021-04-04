//
// Created by adeshchoudhar on 18/03/21.
//

#include "helpers.h"
#include "trie.h"
#include "hash.h"

int main(int argc, char *argv[]) {
    ARGS args = parse_arguments(argc, argv);
    if (!args.success) {
        print_block("ERR!");
        printf("HELP: ./Dictionary [-h/--help]\n\n");
        return 1;
    }

    switch (args.option) {
        case 0: {
            char word[MAX + 1];
            printf("word: ");
            scanf("%s", word);

            get_meanings(word);
            break;
        }
        case 1: {
            help();
            break;
        }
        case 2: {
            DATA hash_data, trie_data;
            if (args.is_file) {
                hash_data = hash_spell_check(args.is_file, args.file);
                trie_data = trie_spell_check(args.is_file, args.file);
            } else {
                hash_data = hash_spell_check(args.is_file, args.word);
                trie_data = trie_spell_check(args.is_file, args.word);
            }
            // TODO: COMPARE
            break;
        }
        case 3: {
            if (!strcmp(args.method, "--TRIE")) {
                DATA data;
                if (args.is_file) {
                    data = trie_spell_check(args.is_file, args.file);
                } else {
                    data = trie_spell_check(args.is_file, args.word);
                }
                time_stats(args.method, data);
            } else {
                DATA data;
                if (args.is_file) {
                    data = hash_spell_check(args.is_file, args.file);
                } else {
                    data = hash_spell_check(args.is_file, args.word);
                }
                time_stats(args.method, data);
            }
            break;
        }
        default: {
            break;
        }
    }

    return 0;
}

