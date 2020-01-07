#ifndef __CODE_WRITER_H_
#define __CODE_WRITER_H_

#include <stdio.h>

#include "command.h"

int init_writer(const char* filename);

int write_command(command* command, char* buffer);
int write_arithmetic(command* command, char* buffer);

#endif // __CODE_WRITER_H_
