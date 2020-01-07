#ifndef __PARSER_H_
#define __PARSER_H_

#include "command.h"

int parse_vm(char** buffer);
int parse_line(char** line, command* command);

#endif // __PARSER_H_
