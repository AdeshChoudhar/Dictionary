# Dictionary

## DSA Mini Project

Dictionary is a project written majorly in C along with a minimal Python script.  
It takes help of a text file as a knowledge base (DICTIONARY). After processing that data, depending upon command-line
arguments and user input it performs respective functions.

## Prerequisites

- gcc-11
- cmake (>=3.17)

## Abbreviations used

- HASH: Hash Table
- TRIE: Trie
- TERN: Ternary Search Tree

## Usage

First change the directory to the root directory of project, then
> mkdir cmake-build  
> cd cmake-build  
> cmake ..  
> make  
> ./Dictionary -h

This will provide you all the help page or valid commands as shown below for using various features.

```
+===========+
|   HELP    |
+===========+

<0> HELP        = Usage: ./Dictionary [-h/--help]
<1> MEANINGS    = Usage: ./Dictionary
<2> GUESS       = Usage: ./Dictionary -g [--TRIE/--TERN] <word>
<3> SPELL-CHECK = Usage: ./Dictionary -s [--HASH/--TRIE/--TERN] [<word>/<file>]
<4> COMPARE     = Usage: ./Dictionary -c [<word>/<file>]
```

## Features

- ### MEANING:
  Basic functionality of providing meaning of a word. The Python script is handling only the API call part. The free
  external API used here is:

> https://dictionaryapi.dev/

- ### GUESS:
  Suggest words according to the longest valid prefix in input argument.  
  Uses `TRIE` or `TERN` data structure to perform this feature.

- ### SPELL-CHECK:
  Takes extra compulsory option `--HASH` or `--TRIE` or `--TERN` to select respective data structure.  
  Displays various parameters regarding time and memory.
    - If inputted a word, it checks validity/spelling of that word.
    - If inputted a file, it checks spelling of all the words and list down all the misspelled words
      in [misspelled.txt](misspelled.txt)

- ### COMPARE:
  Compares and helps to visualize time and memory required while performing spell-checking process by all three data
  structures. Gives a complete analysis and statistics in terminal and visualization with by graphs using `gnuplot`
  pipeline.

## Structure of Project

![flowchart](flowchart.png)

## Mentor

Srida Kalamkar Ma'am

## Author

Adesh Shahadeo Choudhar  
MIS: 111903008
