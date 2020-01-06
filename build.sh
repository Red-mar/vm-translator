#!/usr/bin/env bash

DEBUG_FLAGS="-fsanitize=leak -g"
SOURCE="main.c hash_table.c file.c parser.c command_table.c"


gcc $DEBUG_FLAGS -Wall $SOURCE -o main
