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
        parse_line(&line);
        free(line);
    }
break2:;
    free(code);
    free_command_ht();
    return 0;
}

int parse_line(char** line) {

    if( (*line)[0] == '/' && (*line)[1] == '/' ) return 0;

    int total = 0;
    int i = 0;

    int cmd_i = 0;

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
            ht_item* cmd = get_ht_item(command_ht, word);
            if(cmd != NULL) {
                printf("%s is a command %s\n",cmd->key, cmd->value);
            } else {
                printf("%s is unknown\n", word);
            }
            cmd_i++;
        }

        total += i;
        free(word);
    }
break2:;

    return 0;
}
