#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command_table.h"
#include "code_writer.h"

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
        if(parse_line(&line, command) == 0) {
            write_command(command);
        }
        // Code Writer
        //
        del_command(command);
        free(line);
    }
break2:;
    free(code);
    free_command_ht();
    return 0;
}

int parse_line(char** line, command* command) {
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

            // stop if comment
            if(c == '/' && (*line)[i + total] == '/') {
                // if comment on the first line..
                if(total == 0) {
                    free(command_parts);
                    return 1;
                }
                // else there might be code
                break;
            }
        }
        char* word = (char*) malloc(4096);
        // i -1 to exclude the whitespace
        strncpy(word, (*line) + total, i - 1);

        // :/
        if (strcmp(word,"") != 0) {
            command_parts[cmd_i] = strdup(word);
            cmd_i++;
        }

        free(word);
        total += i;
    }
break2:;

    if (command_parts[0] != NULL) {
        command->type =  strdup(get_ht_item(command_ht, command_parts[0])->value);
        if (strcmp(command->type,"C_ARITHMETIC") == 0 ){
            command->arg1 = strdup(command_parts[0]);
        }
    }
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
    return 0;
}
