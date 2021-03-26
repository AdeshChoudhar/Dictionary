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
            // time_stats(args.method, process.is_this_a_file, process.wc, process.fc, process.mc, process.load_time, process.check_time, process.unload_time);
            break;
        }
        case 3: {
            if (!strcmp(args.method, "--TRIE")) {
                // TODO: TRIE

            } else {
                hash_process process;
                if (args.is_file) {
                    process = hash_spell_check(args.is_file, args.file);
                }
                else {
                    process = hash_spell_check(args.is_file, args.word);
                }
                time_stats(args.method, process.is_file, process.wc, process.fc, process.mc, process.load_time, process.check_time, process.unload_time);
            }
            break;
        }
        default: {
            break;
        }
    }

    return 0;
}

