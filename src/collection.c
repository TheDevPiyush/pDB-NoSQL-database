#include "collection.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

void init_collection(Collection* c) {
    c->count = 0;
    c->next_id = 1;
}

void insert_document(Collection* c, Document doc) {
    if (c->count >= MAX_DOCS) {
        printf("Collection full\n");
        return;
    }

    doc.id = c->next_id++;
    doc.created_at = time(NULL);
    doc.updated_at = doc.created_at;

    c->docs[c->count++] = doc;
}

void print_documents(Collection* c) {
    for (int i = 0; i < c->count; i++) {
        Document* doc = &c->docs[i];

        printf("{ \"_id\": %d, ", doc->id);

        for (int j = 0; j < doc->field_count; j++) {
            printf("\"%s\": \"%s\"", doc->fields[j].key, doc->fields[j].value);

            if (j < doc->field_count - 1) printf(", ");
        }

        printf(" }\n");
    }
}

void delete_by_id(Collection* c, int id) {
    int write = 0;

    for (int i = 0; i < c->count; i++) {
        if (c->docs[i].id != id) {
            c->docs[write++] = c->docs[i];
        }
    }

    c->count = write;
}

void update_by_id(Collection* c, int id, char* key, char* value) {
    for (int i = 0; i < c->count; i++) {
        if (c->docs[i].id == id) {
            Document* doc = &c->docs[i];

            for (int j = 0; j < doc->field_count; j++) {
                if (strcmp(doc->fields[j].key, key) == 0) {
                    strcpy(doc->fields[j].value, value);
                    doc->updated_at = time(NULL);
                    return;
                }
            }

            strcpy(doc->fields[doc->field_count].key, key);
            strcpy(doc->fields[doc->field_count].value, value);
            doc->field_count++;
            doc->updated_at = time(NULL);
            return;
        }
    }

    printf("Document not found\n");
}

void print_document_by_id(Collection* c, int id) {
    for (int i = 0; i < c->count; i++) {
        if (c->docs[i].id == id) {
            Document* doc = &c->docs[i];

            printf("{ \"_id\": %d", doc->id);

            for (int j = 0; j < doc->field_count; j++) {
                printf(", \"%s\": \"%s\"", doc->fields[j].key,
                       doc->fields[j].value);
            }

            printf(" }\n");
            return;
        }
    }

    printf("Document with id %d not found\n", id);
}