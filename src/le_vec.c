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

bool le_vec_is_empty(struct le_vec const *v) {
    return le_vec_get_length(v) == 0;
}

bool __le_vec_expand_to_request(struct le_vec *v, size_t request) {
    size_t capacity = le_vec_get_capacity(v);
    if (capacity >= request) {
        return false;
    }

    while (capacity < request) {
        capacity *= 2;
    }

    v->data = realloc(v->data, capacity);
    v->capacity = capacity;

    return true;
}

bool _le_vec_expand(struct le_vec *v) {
    return __le_vec_expand_to_request(v, v->length + 1);
}

void le_vec_push_back(struct le_vec *v, TYPE value) {
    if (v->length >= v->capacity) {
        _le_vec_expand(v);
    }
    v->length++;

    size_t last_index = le_vec_get_last_index(v);
    v->data[last_index] = value;
}

TYPE le_vec_pop_back(struct le_vec *v) {
    size_t last_index = le_vec_get_last_index(v);
    TYPE value = v->data[last_index];

    v->length--;

    return value;
}

TYPE le_vec_s_pop_back(struct le_vec *v, bool *success) {
    if (le_vec_is_empty(v)) {
        *success = false;
        return (TYPE)0;
    }

    TYPE value = le_vec_pop_back(v);
    *success = true;

    return value;
}

bool le_vec_is_index_valid(struct le_vec const *v, size_t index) {
    return 0 <= index && index < le_vec_get_length(v);
}

size_t le_vec_get_last_index(struct le_vec const *v) {
    return le_vec_get_length(v) - 1;
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
