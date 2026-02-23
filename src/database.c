#include <stdio.h>
#include <string.h>
#include "database.h"

void init_database(Database *db)
{
    db->count = 0;
    db->active_index = -1;
}

int create_collection(Database *db, const char *name)
{
    if (db->count >= MAX_COLLECTIONS) {
        printf("Max collections reached\n");
        return 0;
    }

    strcpy(db->collections[db->count].name, name);
    init_collection(&db->collections[db->count].collection);

    db->count++;
    printf("Collection '%s' created\n", name);
    return 1;
}

int use_collection(Database *db, const char *name)
{
    for (int i = 0; i < db->count; i++) {
        if (strcmp(db->collections[i].name, name) == 0) {
            db->active_index = i;
            printf("Using collection '%s'\n", name);
            return 1;
        }
    }

    printf("Collection not found\n");
    return 0;
}

Collection* get_active_collection(Database *db)
{
    if (db->active_index < 0) {
        printf("No collection selected\n");
        return NULL;
    }

    return &db->collections[db->active_index].collection;
}

void list_collections(Database *db)
{
    printf("Collections:\n");

    for (int i = 0; i < db->count; i++) {
        printf("- %s\n", db->collections[i].name);
    }
}