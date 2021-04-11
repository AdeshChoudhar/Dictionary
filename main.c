//
// Created by adeshchoudhar on 18/03/21.
//

#include "trie.h"
#include "hash.h"

int main(int argc, char *argv[]) {
    ARGS args = parse(argc, argv);
    if (!args.success) {
        print_block("ERR!");
        printf("HELP: ./Dictionary [-h/--help]\n\n");
        return 1;
    }

    switch (args.option) {
        case 0: {
            char word[MAX + 1];
            printf("\nword: ");
            scanf("%s", word);

            clean(word);

            meanings(word);
            break;
        }
        case 1: {
            help();
            break;
        }
        case 2: {
            trie_guess(args.word);
            break;
        }
        case 3: {
            DATA hash_data, trie_data;
            if (args.is_file) {
                hash_data = hash_spell_check(args.is_file, args.file);
                trie_data = trie_spell_check(args.is_file, args.file);
            } else {
                hash_data = hash_spell_check(args.is_file, args.word);
                trie_data = trie_spell_check(args.is_file, args.word);
            }

            statistics("--HASH", hash_data);
            printf("--------------------------------------------------------------------------------\n");
            statistics("--TRIE", trie_data);
            compare(hash_data, trie_data);
            break;
        }
        case 4: {
            DATA data;
            if (!strcmp(args.method, "--TRIE")) {
                if (args.is_file) {
                    data = trie_spell_check(args.is_file, args.file);
                } else {
                    data = trie_spell_check(args.is_file, args.word);
                }

                statistics(args.method, data);
            } else {
                if (args.is_file) {
                    data = hash_spell_check(args.is_file, args.file);
                } else {
                    data = hash_spell_check(args.is_file, args.word);
                }

                statistics(args.method, data);
            }
            break;
        }
        default: {
            break;
        }
    }

    return 0;
}

