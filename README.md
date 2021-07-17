# Dictionary

## DSA Mini Project

Dictionary is a project written majorly in C along with a minimal Python script.<br/><br/>
Takes help of a text file as a knowledge base (DICTIONARY) and performs various functions depending upon command-line
arguments and input

## Prerequisites

- gcc-11
- cmake (>=3.17)


## Usage

First change the directory to the root directory of project, then

> mkdir cmake-build <br/>
> cd cmake-build <br/>
> cmake .. <br/>
> make <br/>
> ./Dictionary -h

This will provide you all the help page or valid commands as shown below for using various features of Dictionary.

```
+===========+
|   HELP    |
+===========+

<0> HELP        = Usage: ./Dictionary [-h/--help]
<1> MEANINGS    = Usage: ./Dictionary
<2> GUESS       = Usage: ./Dictionary -g <word>
<3> SPELL-CHECK = Usage: ./Dictionary -s [--HASH/--TRIE] [<word>/<file>]
<4> COMPARE     = Usage: ./Dictionary -c [<word>/<file>]
```

Use these commands for respective features.

## Features

- ### MEANING:<br/>
  Basic functionality of providing meaning of a word. Only the API call part is handled by a Python
  Script. The free external API used here is:<br/>

> https://dictionaryapi.dev/

- ### GUESS:<br/>

  Suggests words according to longest valid prefix in input argument.<br/>
  Uses `TRIE` data structure to perform this feature.<br/><br/>

- ### SPELL-CHECK:<br>

  Takes extra compulsory option `--HASH` or `--TRIE` to select respective data structure.<br/>
  Displays various parameters regarding time and memory.<br/>

  - If inputted a word checks validity/spelling of that word.<br/>
  - If inputted a file checks spelling of all the words and list down all the misspelled words
    in [misspelled.txt](misspelled.txt)<br/><br/>

- ### COMPARE:<br/>
  Compares and helps to visualize how much time and memory is used while performing spell-checking process. Gives a
  complete analysis and statistics in terminal and visualization is done by graphs using `gnuplot` pipeline

## Structure of Project

![structure](media/structure.png)

## PPT

[Dictionary](Dictionary.pptx)

## Mentor

Srida Kalamkar Ma'am

## Author

Adesh Shahadeo Choudhar<br/>
MIS: 111903008
