#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command_table.h"

int parse_vm(char** buffer) {
    init_command_ht();

    char* code = (char *) malloc(4096);

    int i = 0;
    int total = 0;
    char c = ' ';
    while(c != '\0') {
        c = ' ';
        i = 0;
        while (c != '\n') {
            c = (*buffer)[i + total];
            i++;
            if (c == '\0') goto break2;
        }
        if (c == '\0') break;
        char* line = (char*) malloc(4096);
        strncpy(line, (*buffer) + total, i);
        if (strcmp(line,"\n")==0) {
            total += i;
            free(line);
            continue;
        }
        total += i;
        command* command = new_command();
        // Parse it
        parse_line(&line, command);
        printf("Got cmd: %s arg1: %s arg2: %d\n", command->type, command->arg1, command->arg2);
        // Code Writer
        //
        //
        del_command(command);
        free(line);
    }
break2:;
    free(code);
    free_command_ht();
    return 0;
}

command* parse_line(char** line, command* command) {

    if( (*line)[0] == '/' && (*line)[1] == '/' ) return 0;

    int total = 0;
    int i = 0;

    int cmd_i = 0;
    char** command_parts = malloc(sizeof(char*)*10);

    char c = 'a';
    // Command seperated by whitespace
    while(c != '\n' && c != '\r' && c != '\0') {
        i = 0;
        char c = 'a';
        while(c != ' ' && c != '\n' && c != '\r') {
            c = (*line)[i + total];
            i++;
            if(c == '\0') goto break2;
        }
        char* word = (char*) malloc(4096);
        // i -1 to exclude the whitespace
        strncpy(word, (*line) + total, i - 1);
        if (strcmp(word,"") != 0) {
            command_parts[cmd_i] = strdup(word);
            cmd_i++;
        }

        free(word);
        total += i;
    }
break2:;

    command->type = strdup(command_parts[0]);
    if (command_parts[1] != NULL) {
        command->arg1 = strdup(command_parts[1]);
    }
    if (command_parts[2] != NULL) {
        command->arg2 = atoi(command_parts[2]);
    }

    while(cmd_i > 0) {
        cmd_i--;
        free(command_parts[cmd_i]);
    }
    free(command_parts);
    return command;
}
