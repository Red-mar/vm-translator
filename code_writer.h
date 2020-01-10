#ifndef __CODE_WRITER_H_
#define __CODE_WRITER_H_

#include <stdio.h>
#include <string.h>

#include "command.h"

int init_writer(const char* filename);

int write_command(command* command);
int write_arithmetic(command* command);

#endif // __CODE_WRITER_H_
