#ifndef PARSER_H
#define PARSER_H

typedef enum {
    CMD_INSERT,
    CMD_SELECT,
    CMD_CREATE,
    CMD_USE,
    CMD_SHOW,
    CMD_EXIT,
    CMD_DELETE,
    CMD_UPDATE,
    CMD_UNKNOWN
} CommandType;

CommandType get_command_type(char* input);

#endif