#include "code_writer.h"
#include "string.h"
#include "stdio.h"
#include "file.h"

static FILE* file;
static int label_i = 0;

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

int write_pop(command* command) {
    return 0;
}

int write_push(command* command) {
    printf("Writing Push: %s", command->arg2);
    char* code = malloc(1024);
    strcat(code, "@");
    strcat(code, command->arg2);
    strcat(code, "\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M-1\n");
    fwrite(code, strlen(code), 1, file);

    free(code);
    return 0;
}

int write_command(command* command) {
    if (command->type == NULL) {
        return 1;
    }
    printf("Got cmd: %s arg1: %s arg2: %s\n", command->type, command->arg1, command->arg2);
    if (strcmp(command->type, "C_ARITHMETIC") == 0) {
        write_arithmetic(command);

    }
    if (strcmp(command->type, "C_POP") == 0) {
        write_pop(command);

    }
    if (strcmp(command->type, "C_PUSH") == 0) {
        write_push(command);
    }


    return 0;
}

int write_arithmetic(command* command) {
    char* pop_code = "@SP\nM=M+1\nA=M\nD=M\n@ARG\nA=M\nM=D\n";
    char* code = malloc(1024);
    strcat(code, pop_code);
    strcat(code, "@ARG\nA=M\nD=M\n@SP\nA=M\n");


    if(strcmp(command->arg1, "add") == 0 ) {
        strcat(code, "D=D+M\n");
    }
    if(strcmp(command->arg1, "sub") == 0 ) {
        strcat(code, "D=D-M\n");
    }
    if(strcmp(command->arg1, "and") == 0 ) {
        strcat(code, "D=D&M\n");
    }
    if(strcmp(command->arg1, "or") == 0 ) {
        strcat(code, "D=D|M\n");
    }
    if(strcmp(command->arg1, "add") == 0 ) {
        sprintf(code, "@CMP_EQ%d\nD;JEQ\nD=0\n@CMP_EQ%d_END\n0;JMP",
                label_i, label_i);
    }

    // Push D to curr stack
    strcat(code, "@SP\nA=M\nM=D\n@SP\nM=M-1\n");
    fwrite(code, strlen(code), 1, file);
    return 0;
}
