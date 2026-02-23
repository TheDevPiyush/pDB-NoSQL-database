#ifndef DATABASE_H
#define DATABASE_H

#include "collection.h"

#define MAX_COLLECTIONS 10

typedef struct {
    char name[32];
    Collection collection;
} NamedCollection;

typedef struct {
    NamedCollection collections[MAX_COLLECTIONS];
    int count;
    int active_index;
} Database;

void init_database(Database* db);

int create_collection(Database* db, const char* name);

int use_collection(Database* db, const char* name);

Collection* get_active_collection(Database* db);

void list_collections(Database* db);

#endif