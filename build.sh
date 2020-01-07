#!/usr/bin/env bash

echo "Building Stuff."

DEBUG_FLAGS="-fsanitize=leak -g"
SOURCE="main.c hash_table.c file.c parser.c command_table.c command.c code_writer.c"


gcc $DEBUG_FLAGS -Wall $SOURCE -o main
