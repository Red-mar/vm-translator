#ifndef __COMMAND_H_
#define __COMMAND_H_

#include <stdlib.h>

typedef struct {
    // TODO: Hash table should support int for enum
    char* type;
    char* arg1;
    char* arg2;
} command;

command* new_command();

void del_command(command* command);

#endif // __COMMAND_H_
