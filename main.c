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
            // TODO: TRIE
            break;
        }
        case 3: {
            if (!strcmp(args.method, "--TRIE")) {
                // TODO: TRIE

            } else {
                DATA data;
                if (args.is_file) {
                    data = hash_spell_check(args.is_file, args.file);
                } else {
                    data = hash_spell_check(args.is_file, args.word);
                }
                time_stats(args.method, data.is_file, data.word_count, data.file_count, data.misspelled_count, data.load_time, data.check_time, data.unload_time);
            }
            break;
        }
        default: {
            break;
        }
    }

    return 0;
}

