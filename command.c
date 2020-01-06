#include "command.h"

command* new_command() {
    command* ret = malloc(sizeof(*ret));
    return ret;
}

void del_command(command* command) {
    free(command->type);
    free(command->arg1);
    free(command);
}
