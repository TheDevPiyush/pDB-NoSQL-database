#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "parser.h"
#include "collection.h"

#include "database.h"

void execute_command(CommandType cmd, char *input, Database *db);

#endif