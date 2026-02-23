#include <stdio.h>
#include <string.h>

#include "collection.h"
#include "database.h"
#include "executor.h"
#include "parser.h"
#include "storage.h"

int main() {
    char input[256];
    Database db;

    init_database(&db);
    load_database(&db);

    while (1) {
        printf("pdb >> ");

        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        CommandType cmd = get_command_type(input);

        if (cmd == CMD_EXIT) {
            printf("Bye!\n");
            save_database(&db);
            break;
        }

        execute_command(cmd, input, &db);
    }
}