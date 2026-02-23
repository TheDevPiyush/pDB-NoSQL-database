#include "storage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DB_FILE "database.pdb"


/* =========================================================
   STRING SERIALIZATION
   ========================================================= */

void write_string(FILE *f, const char *str)
{
    int len = strlen(str);

    fwrite(&len, sizeof(int), 1, f);
    fwrite(str, sizeof(char), len, f);
}

void read_string(FILE *f, char *buffer)
{
    int len;

    if (fread(&len, sizeof(int), 1, f) != 1) {
        printf("Read error\n");
        exit(1);
    }

    if (len < 0 || len > 63) {
        printf("Invalid string length: %d\n", len);
        exit(1);
    }

    fread(buffer, sizeof(char), len, f);
    buffer[len] = '\0';
}


/* =========================================================
   LOAD DATABASE
   ========================================================= */

void load_database(Database *db)
{
    FILE *f = fopen(DB_FILE, "rb");

    if (!f) {
        printf("No database file found. Starting fresh.\n");
        return;
    }

    init_database(db);

    if (fread(&db->count, sizeof(int), 1, f) != 1) {
        printf("Corrupted database file\n");
        fclose(f);
        return;
    }

    for (int i = 0; i < db->count; i++)
    {
        NamedCollection *nc = &db->collections[i];
        Collection *c = &nc->collection;

        read_string(f, nc->name);

        init_collection(c);

        fread(&c->count, sizeof(int), 1, f);

        for (int d = 0; d < c->count; d++)
        {
            Document loaded_doc;

            fread(&loaded_doc.id, sizeof(int), 1, f);
            fread(&loaded_doc.created_at, sizeof(time_t), 1, f);
            fread(&loaded_doc.updated_at, sizeof(time_t), 1, f);

            fread(&loaded_doc.field_count, sizeof(int), 1, f);

            for (int k = 0; k < loaded_doc.field_count; k++)
            {
                read_string(f, loaded_doc.fields[k].key);
                read_string(f, loaded_doc.fields[k].value);
            }

            c->docs[d] = loaded_doc;
        }

        int max_id = 0;
        for (int j = 0; j < c->count; j++)
            if (c->docs[j].id > max_id)
                max_id = c->docs[j].id;

        c->next_id = max_id + 1;
    }

    db->active_index = -1;

    fclose(f);

    printf("Database loaded (%d collections)\n", db->count);
}


/* =========================================================
   SAVE DATABASE
   ========================================================= */

void save_database(Database *db)
{
    FILE *f = fopen(DB_FILE, "wb");
    if (!f) {
        printf("Failed to open database file\n");
        return;
    }

    fwrite(&db->count, sizeof(int), 1, f);

    for (int i = 0; i < db->count; i++)
    {
        NamedCollection *nc = &db->collections[i];
        Collection *c = &nc->collection;

        write_string(f, nc->name);

        fwrite(&c->count, sizeof(int), 1, f);

        for (int d = 0; d < c->count; d++)
        {
            Document *doc = &c->docs[d];

            fwrite(&doc->id, sizeof(int), 1, f);
            fwrite(&doc->created_at, sizeof(time_t), 1, f);
            fwrite(&doc->updated_at, sizeof(time_t), 1, f);

            fwrite(&doc->field_count, sizeof(int), 1, f);

            for (int k = 0; k < doc->field_count; k++)
            {
                write_string(f, doc->fields[k].key);
                write_string(f, doc->fields[k].value);
            }
        }
    }

    fclose(f);

    printf("Database saved.\n");
}