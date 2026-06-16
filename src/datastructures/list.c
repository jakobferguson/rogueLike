#include "list.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void list_init(struct list *l, size_t elem_size){
    l->data = NULL;
    l->size = 0;
    l->capacity = 0;
    l->elem_size = elem_size;
}

void list_free(struct list *l){
    free(l->data);
    l->data = NULL;
    l->capacity = 0;
    l->size = 0;
}

void *list_get(struct list *l, size_t index){
    assert(index <= l->size);
    return l->data + l->elem_size * index;
}

int list_append(struct list *l, const void *item){
    if (l->size == l->capacity){
        size_t new_cap = (l->capacity) ? l->capacity * 2 : 8;
        void *new_data = realloc(l->data, l->elem_size * new_cap);
        if (!new_data) return -1;
        l->capacity = new_cap;
        l->data = new_data;
    }
    memcpy(l->data + l->size * l->elem_size, item, l->elem_size);
    l->size++;

    return 0;
}

int list_insert(struct list *l, const void *item, size_t index){
    if (l->size == l->capacity){
       size_t new_cap = (l->capacity) ? l->capacity * 2 : 8;
        void *new_data = realloc(l->data, l->elem_size * new_cap);
        if (!new_data) return -1;
        l->capacity = new_cap;
        l->data = new_data;
    }
    memmove(l->data + l->elem_size * (index + 1), l->data + l->elem_size * index, l->elem_size * (l->size - index));
    memcpy(l->data + l->elem_size * index, item, l->elem_size);
    l->size++;

    return 0;
}
