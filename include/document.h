#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <time.h>

#define MAX_FIELDS 10

typedef struct {
    char key[32];
    char value[64];
} Field;

typedef struct {
    int id;
    time_t created_at;
    time_t updated_at;

    Field fields[MAX_FIELDS];
    int field_count;
} Document;
#endif