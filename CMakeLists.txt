cmake_minimum_required(VERSION 3.17)
project(Dictionary C)

set(CMAKE_C_STANDARD 11)

add_executable(Dictionary
        main.c spell.c spell.h trie.c trie.h helpers.c helpers.h)
