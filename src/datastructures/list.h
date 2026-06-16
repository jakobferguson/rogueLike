#pragma once
#include <stddef.h>

struct list{
    void *data;
    size_t size;
    size_t capacity;
    size_t elem_size;
};


void list_init(struct list *l, size_t elem_size);
void list_free(struct list *l);
int list_append(struct list *l, const void *item);
void *list_get(struct list *l, size_t index);
int list_insert(struct list *l, const void *item, size_t index);
