#ifndef __COMMAND_H_
#define __COMMAND_H_

#include <stdlib.h>

typedef struct {
    char* type;
    char* arg1;
    int arg2;
} command;

command* new_command();

void del_command(command* command);

#endif // __COMMAND_H_
