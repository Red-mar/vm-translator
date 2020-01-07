#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "parser.h"

int main(int argc, char** argv) {
    char* filepath = "";
    char* output_filename = "output.asm";

    if(argc < 2) {
        puts("Please put a file as the second argument.");
        return 1;
    }
    if(argc > 2) {
        output_filename = argv[2];
        puts(output_filename);
    }
    filepath = argv[1];

    FILE* file;

    file = fopen(filepath, "r");
    if(file == NULL) {
        puts("Bad file.");
        return 1;
    }

    char* buffer = (char*) malloc(4096);

    if(!read_file(file, &buffer, 4096)) {
        puts("Bad read file.");
        return 1;
    }

    parse_vm(&buffer);

    fclose(file);
    free(buffer);

    return 0;
}
