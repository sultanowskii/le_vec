#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "le_vec.h"

struct le_vec {
    size_t capacity;
    size_t length;
    TYPE *data;
};

struct le_vec *le_vec_init(void) {
    struct le_vec *v = malloc(sizeof(struct le_vec));
    TYPE *data = malloc(DEFAULT_CAPACITY);

    v->capacity = DEFAULT_CAPACITY;
    v->length = 0;
    v->data = data;

    return v;
}

struct le_vec *le_vec_init_with_length(size_t length_request) {
    if (length_request == 0) {
        return NULL;
    }

    struct le_vec *v = malloc(sizeof(struct le_vec));
    TYPE *data = malloc(length_request);
    
    v->capacity = length_request;
    v->length = length_request;
    v->data = data;

    return v;
}

void le_vec_destroy(struct le_vec *v) {
    if (v == NULL) {
        return;
    }

    free(v->data);
    v->data = NULL;
    free(v);
}

size_t le_vec_get_capacity(struct le_vec const *v) {
    return v->capacity;
}

size_t le_vec_get_length(struct le_vec const *v) {
    return v->length;
}

bool _le_vec_expand_to_request(struct le_vec *v, size_t request) {
    if (v->capacity >= request) {
        return false;
    }

    while (v->capacity < request) {
        v->capacity *= 2;
    }

    v->data = realloc(v->data, v->capacity);
    
    return true;
}

bool _le_vec_expand(struct le_vec *v) {
    return _le_vec_expand_to_request(v, v->length + 1);
}

void le_vec_push_back(struct le_vec *v, TYPE value) {
    if (v->length >= v->capacity) {
        _le_vec_expand(v);
    }
    v->length++;

    size_t last_index = v->length - 1;
    v->data[last_index] = value;
}

bool le_vec_is_index_valid(struct le_vec const *v, size_t index) {
    return 0 <= index && index < v->length;
}

TYPE le_vec_get_at(struct le_vec const *v, size_t index) {
    return v->data[index];
}

bool le_vec_set_at(struct le_vec *v, size_t index, TYPE value) {
    if (!le_vec_is_index_valid(v, index)) {
        return false;
    }

    v->data[index] = value;
    return true;
}
