#include "executor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "collection.h"

/* =========================================================
   Read User Inputs as tokens and parse pair inputs
   ========================================================= */

void read_token(char** cursor, char* out) {
    int i = 0;
    char* p = *cursor;

    while (*p == ' ') p++;

    if (*p == '"') {
        p++;

        while (*p && *p != '"') out[i++] = *p++;

        if (*p == '"') p++;
    } else {
        while (*p && *p != '=' && *p != ' ') out[i++] = *p++;
    }

    out[i] = '\0';
    *cursor = p;
}

int parse_pair(char** cursor, Field* field) {
    read_token(cursor, field->key);

    if (**cursor != '=') {
        printf("Syntax error: expected '=' after key\n");
        return 0;
    }

    (*cursor)++;

    read_token(cursor, field->value);

    return 1;
}

/* =========================================================
   Execute user commands if correct syntax
   ========================================================= */

void execute_command(CommandType cmd, char* input, Database* db) {
    // ------- CREATE Command -----------

    if (cmd == CMD_CREATE) {
        strtok(input, " ");
        char* name = strtok(NULL, " ");

        if (name) create_collection(db, name);
    }

    // ------- USE Command -----------

    else if (cmd == CMD_USE) {
        strtok(input, " ");
        char* name = strtok(NULL, " ");

        if (name) use_collection(db, name);
    }

    // ------- Show Collection Command -----------

    else if (cmd == CMD_SHOW) {
        list_collections(db);
    }

    // ------- DELETE A DOC BY ID Command -----------

    else if (cmd == CMD_DELETE) {
        Collection* c = get_active_collection(db);
        if (!c) return;

        int id = atoi(strchr(input, ' ') + 1);

        delete_by_id(c, id);

        printf("Document deleted\n");
    }

    // ------- UPDATE A DOC BY ID Command -----------

    else if (cmd == CMD_UPDATE) {
        Collection* c = get_active_collection(db);
        if (!c) return;

        char* cursor = strchr(input, ' ');
        cursor++;

        int id = atoi(cursor);

        char* set_pos = strstr(cursor, "set");
        if (!set_pos) {
            printf("Missing SET clause\n");
            return;
        }

        cursor = set_pos + 4;

        char key[64];
        char value[64];

        read_token(&cursor, key);

        if (*cursor != '=') {
            printf("Expected '='\n");
            return;
        }

        cursor++;

        read_token(&cursor, value);

        update_by_id(c, id, key, value);

        printf("Document updated\n");
    }

    // ------- INSERT A DOC BY ID Command -----------

    else if (cmd == CMD_INSERT) {
        Collection* c = get_active_collection(db);
        if (!c) return;

        Document doc;
        doc.field_count = 0;

        char* cursor = strchr(input, ' ');
        if (!cursor) {
            printf("Insert requires fields\n");
            return;
        }

        cursor++;

        while (*cursor) {
            while (*cursor == ' ') cursor++;

            if (*cursor == '\0') break;

            if (doc.field_count >= MAX_FIELDS) {
                printf("Too many fields\n");
                return;
            }

            if (!parse_pair(&cursor, &doc.fields[doc.field_count])) return;

            doc.field_count++;
        }

        insert_document(c, doc);
        printf("Document inserted\n");
    }

    // ------- SELECT A DOC BY ID or all docs Command -----------

    else if (cmd == CMD_SELECT) {
        Collection* c = get_active_collection(db);
        if (!c) return;

        char* token = strtok(input, " ");
        token = strtok(NULL, " ");

        if (token == NULL) {
            print_documents(c);
        } else {
            int id = atoi(token);
            print_document_by_id(c, id);
        }
    }
}