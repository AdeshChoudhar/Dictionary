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
            printf("\nWORD: ");
            scanf("%45s", word);
            clean(word);
            meaning(argv[0], word);
            break;
        }
        case 2: {
            if (!strcmp(args.method, "--TRIE")) {
                trie_guess(args.input);
            } else if (!strcmp(args.method, "--TERN")){
                tern_guess(args.input);
            }
            break;
        }
        case 3: {
            DATA data;
            if (!strcmp(args.method, "--HASH")) {
                data = hash_spell_check(args.is_file, args.input);
            } else if (!strcmp(args.method, "--TRIE")) {
                data = trie_spell_check(args.is_file, args.input);
            } else if (!strcmp(args.method, "--TERN")){
                data = tern_spell_check(args.is_file, args.input);
            } else {
                break;
            }
            statistics(args.method, data);
            break;
        }
        case 4: {
            DATA hash_data, trie_data, tern_data;
            hash_data = hash_spell_check(args.is_file, args.input);
            trie_data = trie_spell_check(args.is_file, args.input);
            tern_data = tern_spell_check(args.is_file, args.input);
            compare(hash_data, trie_data, tern_data);
            break;
        }
        default: {
            throw_error("HELP: ./Dictionary [-h/--help]");
        }
    }

    return 0;
}
