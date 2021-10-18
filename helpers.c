//
// Created by adeshchoudhar on 18/03/21.
//

#include "helpers.h"

bool check_file(char *file_name) {
    return access(file_name, F_OK) == -1 ? false : true;
}

ARGS parse(int argc, char *argv[]) {
    ARGS args = {.option = -1, .method = "", .input = "", .is_file = false, .success = false};
    switch (argc) {
        case 1: {
            args.option = 1;
            args.success = true;
            break;
        }
        case 2: {
            if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
                args.option = 0;
                args.success = true;
            }
            break;
        }
        case 3: {
            if (!strcmp(argv[1], "-c")) {
                args.is_file = check_file(argv[2]);
                args.input = argv[2];
                args.option = 4;
                args.success = true;
            }
            break;
        }
        case 4: {
            if (!strcmp(argv[1], "-g")) {
                if (!strcmp(argv[2], "--TRIE") || !strcmp(argv[2], "--TERN")) {
                    args.input = argv[3];
                    args.method = argv[2];
                    args.option = 2;
                    args.success = true;
                }
            } else if (!strcmp(argv[1], "-s")) {
                if (!strcmp(argv[2], "--HASH") || !strcmp(argv[2], "--TRIE") || !strcmp(argv[2], "--TERN")) {
                    args.is_file = check_file(argv[3]);
                    args.input = argv[3];
                    args.method = argv[2];
                    args.option = 3;
                    args.success = true;
                }
            }
            break;
        }
        default: {
            break;
        }
    }
    return args;
}

void print_block(char *block_name) {
    printf("\n");
    printf("+===========+\n");
    printf("|   %s    |\n", block_name);
    printf("+===========+\n");
    printf("\n");
}

void throw_error(char *error_message) {
    print_block("ERR!");
    printf("%s\n\n", error_message);
    exit(1);
}

void help() {
    print_block("HELP");
    printf("<0> HELP        = Usage: ./Dictionary [-h/--help]\n");
    printf("<1> MEANINGS    = Usage: ./Dictionary\n");
    printf("<2> GUESS       = Usage: ./Dictionary -g [--TRIE/--TERN] <word>\n");
    printf("<3> SPELL-CHECK = Usage: ./Dictionary -s [--HASH/--TRIE/--TERN] [<word>/<file>]\n");
    printf("<4> COMPARE     = Usage: ./Dictionary -c [<word>/<file>]\n");
    printf("\n");
}

bool is_number(const char word[]) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (!isdigit(word[i])) {
            return false;
        }
    }
    return true;
}

void clean(char word[]) {
    int i, j;

    for (i = 0; word[i] != '\0'; i++) {
        word[i] = (char) tolower(word[i]);
    }

    char word_copy[MAX + 1];
    for (i = 0, j = 0; word[i] != '\0'; i++) {
        if (isalnum(word[i])) {
            word_copy[j++] = word[i];
        }
    }
    if (j == 0) {
        word_copy[j++] = 'a';
    }
    word_copy[j] = '\0';

    strcpy(word, word_copy);

    int length;
    for (length = 0; word[length] != '\0'; length++);

    if (is_number(word)) {
        word[0] = word[length - 1];
        word[1] = '\0';
        return;
    }

    if (length >= 3) {
        char th_word_copy[MAX - 1];
        for (i = 0; i < length - 2; i++) {
            th_word_copy[i] = word[i];
        }
        th_word_copy[i] = '\0';
        if (is_number(th_word_copy)) {
            word[0] = word[length - 3];
            word[1] = word[length - 2];
            word[2] = word[length - 1];
            word[3] = '\0';
            return;
        }
    }
}

void meaning(char *argv, char *word) {
    unsigned long length = 8 + strlen(argv) - 10 + 14 + strlen(word) + 1;
    char command[length];
    memset(command, '\0', length * sizeof(char));

    strcat(command, "python3 ");
    argv[strlen(argv) - 10] = '\0';
    strcat(command, argv);
    strcat(command, "../meaning.py ");
    strcat(command, word);

    printf("\n");
    system(command);
}

double get_time(clock_t start, clock_t stop) {
    return ((double) (stop - start)) / (CLOCKS_PER_SEC / 1000.0);
}

void statistics(char *method, DATA data) {
    double total_time = data.load_time + data.check_time + data.unload_time;

    if (!strcmp(method, "--HASH") || !strcmp(method, "--TRIE") || !strcmp(method, "--TERN")) {
        print_block(method + 2);
    }

    printf("\nWORDS IN DICTIONARY: %lu\n\n", data.word_count);

    if (data.is_file) {
        double text_correctness = ((double) (data.file_count - data.misspelled_count) / (double) data.file_count) * 100;
        printf("WORDS IN FILE: %lu\n", data.file_count);
        printf("MISSPELLED WORDS: %lu\n", data.misspelled_count);
        printf("TEXT CORRECTNESS: %.2f%%\n\n", text_correctness);
    } else {
        printf("SPELLING: %s\n\n", data.misspelled_count ? "INVALID" : "VALID");
    }

    printf("TIME IN LOAD: %.2lf ms\n", data.load_time);
    printf("TIME IN CHECK: %.2lf ms\n", data.check_time);
    printf("TIME IN UNLOAD: %.2lf ms\n", data.unload_time);
    printf("TOTAL TIME: %.2lf ms\n\n", total_time);

    printf("MEMORY: %.2lf MB\n\n", (double) (data.memory) / 1000000);
}

void compare(DATA hash_data, DATA trie_data, DATA tern_data) {
    statistics("--HASH", hash_data);
    printf("--------------------------------------------------------------------------------\n");
    statistics("--TRIE", trie_data);
    printf("--------------------------------------------------------------------------------\n");
    statistics("--TERN", tern_data);

    if (check_file("../data/time.dat")) {
        system("rm ../data/time.dat");
    }
    if (check_file("../data/memory.dat")) {
        system("rm ../data/memory.dat");
    }

    FILE *time_file = fopen("../data/time.dat", "w");
    FILE *memory_file = fopen("../data/memory.dat", "w");
    FILE *time_gp = popen(GNUPLOT, "w");
    FILE *memory_gp = popen(GNUPLOT, "w");
    if (!time_file || !memory_file || !time_gp || !memory_gp) {
        throw_error("File could not be opened!\n");
    }

    double hash_data_total_time, trie_data_total_time, tern_data_total_time;
    hash_data_total_time = hash_data.load_time + hash_data.check_time + hash_data.unload_time;
    trie_data_total_time = trie_data.load_time + trie_data.check_time + trie_data.unload_time;
    tern_data_total_time = tern_data.load_time + tern_data.check_time + tern_data.unload_time;

    fprintf(time_file, "%lf %lf\n", 2.0, hash_data.load_time);
    fprintf(time_file, "%lf %lf\n", 3.0, trie_data.load_time);
    fprintf(time_file, "%lf %lf\n\n", 4.0, tern_data.load_time);
    fprintf(time_file, "%lf %lf\n", 7.0, hash_data.check_time);
    fprintf(time_file, "%lf %lf\n", 8.0, trie_data.check_time);
    fprintf(time_file, "%lf %lf\n\n", 9.0, tern_data.check_time);
    fprintf(time_file, "%lf %lf\n", 12.0, hash_data.unload_time);
    fprintf(time_file, "%lf %lf\n", 13.0, trie_data.unload_time);
    fprintf(time_file, "%lf %lf\n\n", 14.0, tern_data.unload_time);
    fprintf(time_file, "%lf %lf\n", 17.0, hash_data_total_time);
    fprintf(time_file, "%lf %lf\n", 18.0, trie_data_total_time);
    fprintf(time_file, "%lf %lf\n\n", 19.0, tern_data_total_time);

    fprintf(time_gp, "set key default\n");
    fprintf(time_gp, "set style fill solid\n");
    fprintf(time_gp, "set boxwidth 1\n");
    fprintf(time_gp, "set title 'Time Analysis'\n");
    fprintf(time_gp, "set ylabel 'Time (in ms)'\n");
    fprintf(time_gp, "set xrange [0:25]\n");
    fprintf(time_gp, "set xtics ('load time' 3, 'check time' 8, 'unload time' 13, 'total time' 18)\n");
    fprintf(time_gp, "plot '../data/time.dat' every 2 using 1:2 with boxes ls 5 title 'HASH',"
                     "'../data/time.dat' every 2::1 using 1:2 with boxes ls 6 title 'TRIE',"
                     "'../data/time.dat' every 2::2 using 1:2 with boxes ls 7 title 'TERN'\n");


    fprintf(memory_file, "%lf %lu\n", 1.0, hash_data.memory);
    fprintf(memory_file, "%lf %lu\n", 2.0, trie_data.memory);
    fprintf(memory_file, "%lf %lu\n", 3.0, tern_data.memory);

    fprintf(memory_gp, "set title 'Memory Analysis'\n");
    fprintf(memory_gp, "set ylabel 'Memory (in bytes)'\n");
    fprintf(memory_gp, "set xrange [0: 4]\n");
    fprintf(memory_gp, "set xtics ('hash memory' 1, 'trie memory' 2, 'tern memory' 3)\n");
    fprintf(memory_gp, "set key default\n");
    fprintf(memory_gp, "set boxwidth 0.5\n");
    fprintf(memory_gp, "set style fill solid\n");
    fprintf(memory_gp, "plot '../data/memory.dat' every 2 using 1:2 with boxes ls 5 title 'HASH',"
                       "'../data/memory.dat' every 2::1 using 1:2 with boxes ls 6 title 'TRIE',"
                       "'../data/memory.dat' every 2::2 using 1:2 with boxes ls 7 title 'TERN'\n");

    fclose(time_file);
    fclose(memory_file);
    fclose(time_gp);
    fclose(memory_gp);
}
