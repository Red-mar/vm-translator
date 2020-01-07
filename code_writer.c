#include "code_writer.h"
#include "string.h"
#include "stdio.h"
#include "file.h"

static FILE* file;

int init_writer(const char* filepath) {
    if(file != NULL) {
        fclose(file);
    }
    file = fopen(filepath, "w");
    if(file == NULL) {
        puts("Bad file.");
        return 1;
    }
    return 0;
}

int write_command(command* command) {
    if (command->type == NULL) {
        return 1;
    }
    printf("Got cmd: %s arg1: %s arg2: %d\n", command->type, command->arg1, command->arg2);
    if (strcmp(command->type, "C_ARITHMETIC") == 0) {
        write_arithmetic(command, buffer);

    }
    if (strcmp(command->type, "C_POP") == 0) {

    }
    if (strcmp(command->type, "C_PUSH") == 0) {

    }


    return 0;
}

int write_arithmetic(command* command) {
    if(strcmp(command->arg1, "add") == 0 ) {


    }
    // add
    // A=SP get memory address
    // D=M  put it in d
    // @R13
    // M=D  get the value
    //
    // A
    //
    // A=SP
    // D=D+M
}
