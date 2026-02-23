#include "parser.h"

#include <string.h>

CommandType get_command_type(char* input) {
    if (strncmp(input, "insert", 6) == 0) return CMD_INSERT;

    if (strncmp(input, "select", 6) == 0) return CMD_SELECT;

    if (strncmp(input, "create", 6) == 0) return CMD_CREATE;

    if (strncmp(input, "delete", 6) == 0) return CMD_DELETE;

    if (strncmp(input, "update", 6) == 0) return CMD_UPDATE;

    if (strncmp(input, "use", 3) == 0) return CMD_USE;

    if (strcmp(input, "list") == 0) return CMD_SHOW;

    if (strcmp(input, "exit") == 0) return CMD_EXIT;

    return CMD_UNKNOWN;
}