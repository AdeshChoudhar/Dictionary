//
// Created by adeshchoudhar on 18/03/21.
//

#include "helpers.h"
#include "spell.h"


int main(int argc, char *argv[]) {
    if (!parse_arguments(argc, argv).success) {
        print_block("ERR!");
        printf("HELP: ./Dictionary [-h/--help]\n\n");
        return 1;
    }



    return 0;
}

