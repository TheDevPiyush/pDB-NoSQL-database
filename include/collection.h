#ifndef COLLECTION_H
#define COLLECTION_H

#include "document.h"

#define MAX_DOCS 100

typedef struct {
    Document docs[MAX_DOCS];
    int count;
    int next_id;
} Collection;

void insert_document(Collection* c, Document doc);
void print_documents(Collection* c);
void init_collection(Collection* c);
void delete_by_id(Collection* c, int id);
void update_by_id(Collection* c, int id, char* key, char* value);
void print_document_by_id(Collection *c, int id);
#endif