//
// Created by adeshchoudhar on 18/03/21.
//

#include "helpers.h"

bool check_file(char *file) {
    if (access(file, F_OK) == -1) {
        return false;
    }
    return true;
}

ARGS parse(int argc, char *argv[]) {
    ARGS args = {.option = -1, .method = "", .word = "", .file = "", .is_file = false, .success = false};
    switch (argc) {
        case 1: {
            args.option = 0;
            args.success = true;
            break;
        }
        case 2: {
            if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
                args.option = 1;
                args.success = true;
            }
            break;
        }
        case 3: {
            if (!strcmp(argv[1], "-g")) {
                args.word = argv[2];
                args.option = 2;
                args.success = true;
            } else if (!strcmp(argv[1], "-c")) {
                if (check_file(argv[2])) {
                    args.is_file = true;
                    args.file = argv[2];
                } else {
                    args.word = argv[2];
                }
                args.option = 3;
                args.success = true;
            }
            break;
        }
        case 4: {
            if (!strcmp(argv[1], "-s")) {
                if (!strcmp(argv[2], "--HASH") || !strcmp(argv[2], "--TRIE")) {
                    if (check_file(argv[3])) {
                        args.is_file = true;
                        args.file = argv[3];
                    } else {
                        args.word = argv[3];
                    }
                    args.method = argv[2];
                    args.option = 4;
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

void meanings(const char word[]) {
    char command[MAX + 30 + 1] = {'p', 'y', 't', 'h', 'o', 'n', ' ', '.', '.', '/', 's', 'c', 'r', 'i', 'p', 't', 's',
                                  '/', 'm', 'e', 'a', 'n', 'i', 'n', 'g', 's', '.', 'p', 'y', ' '};
    for (int i = 0; i < MAX + 1; i++) {
        command[30 + i] = word[i];
    }

    printf("\n");
    system(command);
}

void help() {
    print_block("HELP");
    printf("<0> Usage: ./Dictionary\n");
    printf("<1> Usage: ./Dictionary [-h/--help]\n");
    printf("<2> Usage: ./Dictionary -g <word>\n");
    printf("<3> Usage: ./Dictionary -c [<word>/<file>]\n");
    printf("<4> Usage: ./Dictionary -s [--HASH/--TRIE] [<word>/<file>]\n");
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

double get_time(clock_t start, clock_t stop) {
    double time = ((double) (stop - start)) / (CLOCKS_PER_SEC / 1000.0);
    return time;
}

void statistics(char *method, DATA data) {
    double total_time = data.load_time + data.check_time + data.unload_time;

    if (!strcmp(method, "--TRIE")) {
        print_block("TRIE");
    } else if (!strcmp(method, "--HASH")) {
        print_block("HASH");
    }

    printf("WORDS IN DICTIONARY: %u\n\n", data.word_count);

    if (data.is_file) {
        double text_correctness = ((double) (data.file_count - data.misspelled_count) / data.file_count) * 100;
        printf("WORDS IN FILE: %u\n", data.file_count);
        printf("MISSPELLED WORDS: %u\n", data.misspelled_count);
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

void compare(DATA hash_data, DATA trie_data) {
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
        print_block("ERR!");
        printf("File could not be opened!\n");
    }

    double hash_data_total_time, trie_data_total_time;
    hash_data_total_time = hash_data.load_time + hash_data.check_time + hash_data.unload_time;
    trie_data_total_time = trie_data.load_time + trie_data.check_time + trie_data.unload_time;

    fprintf(time_file, "%lf %lf\n", 3.5, hash_data.load_time);
    fprintf(time_file, "%lf %lf\n\n", 4.5, trie_data.load_time);
    fprintf(time_file, "%lf %lf\n", 7.5, hash_data.check_time);
    fprintf(time_file, "%lf %lf\n\n", 8.5, trie_data.check_time);
    fprintf(time_file, "%lf %lf\n", 11.5, hash_data.unload_time);
    fprintf(time_file, "%lf %lf\n\n", 12.5, trie_data.unload_time);
    fprintf(time_file, "%lf %lf\n", 15.5, hash_data_total_time);
    fprintf(time_file, "%lf %lf\n\n", 16.5, trie_data_total_time);

    fprintf(memory_file, "%d %lu\n", 2, hash_data.memory);
    fprintf(memory_file, "%d %lu\n", 4, trie_data.memory);

    fprintf(time_gp, "set key default\n");
    fprintf(time_gp, "set style fill solid\n");
    fprintf(time_gp, "set boxwidth 1\n");
    fprintf(time_gp, "set title 'Time Analysis'\n");
    fprintf(time_gp, "set ylabel 'Time (in ms)'\n");
    fprintf(time_gp, "set xrange [0:20]\n");
    fprintf(time_gp, "set xtics ('load time' 4, 'check time' 8, 'unload time' 12, 'total time' 16,)\n");
    fprintf(time_gp, "plot '../data/time.dat' every 2 using 1:2 with boxes ls 1 title 'HASH',"
                     "'../data/time.dat' every 2::1 using 1:2 with boxes ls 2 title 'TRIE'\n");

    fprintf(memory_gp, "set title 'Memory Analysis'\n");
    fprintf(memory_gp, "set ylabel 'Memory (in bytes)'\n");
    fprintf(memory_gp, "set xrange [0: 6]\n");
    fprintf(memory_gp, "set xtics ('hash memory' 2, 'trie memory' 4,)\n");
    fprintf(memory_gp, "set key default\n");
    fprintf(memory_gp, "set boxwidth 0.5\n");
    fprintf(memory_gp, "set style fill solid\n");
    fprintf(memory_gp, "plot '../data/memory.dat' every 2 using 1:2 with boxes ls 1 title 'HASH', "
                       "'../data/memory.dat' every 2::1 using 1:2 with boxes ls 2 title 'TRIE'\n");

    fclose(time_file);
    fclose(memory_file);
    fclose(time_gp);
    fclose(memory_gp);
}
