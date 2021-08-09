//
// Created by adeshchoudhar on 18/03/21.
//

#include "hash.h"
#include "trie.h"
#include "tern.h"

int main(int argc, char *argv[]) {
    ARGS args = parse(argc, argv);
    if (!args.success) {
        throw_error("HELP: ./Dictionary [-h/--help]");
    }

    switch (args.option) {
        case 0: {
            help();
            break;
        }
        case 1: {
            char word[MAX + 1];
            printf("\nword: ");
            scanf("%45s", word);
            clean(word);
            meaning(argv[0], word);
            break;
        }
        case 2: {
            if (!strcmp(args.method, "--TRIE")) {
                trie_guess(args.word);
            } else {
                tern_guess(args.word);
            }
            break;
        }
        case 3: {
            DATA data;
            if (!strcmp(args.method, "--HASH")) {
                if (args.is_file) {
                    data = hash_spell_check(args.is_file, args.file);
                } else {
                    data = hash_spell_check(args.is_file, args.word);
                }
            } else if (!strcmp(args.method, "--TRIE")) {
                if (args.is_file) {
                    data = trie_spell_check(args.is_file, args.file);
                } else {
                    data = trie_spell_check(args.is_file, args.word);
                }
            } else {
                if (args.is_file) {
                    data = tern_spell_check(args.is_file, args.file);
                } else {
                    data = tern_spell_check(args.is_file, args.word);
                }
            }
            statistics(args.method, data);
            break;
        }
        case 4: {
            DATA hash_data, trie_data, tern_data;
            if (args.is_file) {
                hash_data = hash_spell_check(args.is_file, args.file);
                trie_data = trie_spell_check(args.is_file, args.file);
                tern_data = tern_spell_check(args.is_file, args.file);
            } else {
                hash_data = hash_spell_check(args.is_file, args.word);
                trie_data = trie_spell_check(args.is_file, args.word);
                tern_data = tern_spell_check(args.is_file, args.word);
            }
            compare(hash_data, trie_data, tern_data);
            break;
        }
        default: {
            throw_error("HELP: ./Dictionary [-h/--help]");
        }
    }

    return 0;
}
