#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "le_vec.h"

struct le_vec {
    size_t capacity;
    size_t length;
    TYPE *data;
};

// Expands data so that capacity is >= request.
bool __le_vec_expand_to_request(struct le_vec *v, size_t request);
// Expands data. Call this.
bool _le_vec_expand(struct le_vec *v);
// Explicitly and stupidly sets a length to a new value.
void _le_vec_set_length(struct le_vec *v, size_t new_length);
// Reallocates data and so that capacity == length.
void _le_vec_shrink_down_to_length(struct le_vec *v);
// Applies f for each element in src and stores result in dest.
// dest.length must be >= src.lentgth to fit all elements.
void _le_vec_map(struct le_vec *dest, struct le_vec const *src, TYPE (*f)(TYPE));

struct le_vec *le_vec_init(void) {
    struct le_vec *v = malloc(sizeof(struct le_vec));
    TYPE *data = malloc(DEFAULT_CAPACITY);

    v->capacity = DEFAULT_CAPACITY;
    v->length = 0;
    v->data = data;

    return v;
}

struct le_vec *le_vec_init_with_length(size_t request) {
    if (request == 0) {
        return NULL;
    }

    struct le_vec *v = malloc(sizeof(struct le_vec));
    TYPE *data = malloc(request);
   
    v->capacity = request;
    v->length = request;
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

void _le_vec_set_length(struct le_vec *v, size_t new_length) {
    v->length = new_length;
}

void _le_vec_shrink_down_to_length(struct le_vec *v) {
    size_t length = le_vec_get_length(v);

    v->data = realloc(v->data, length);
    v->capacity = length;
}

void le_vec_resize(struct le_vec *v, size_t new_length) {
    size_t capacity = le_vec_get_capacity(v);
    size_t length = le_vec_get_length(v);

    if (new_length == length) {
        return;
    }

    if (new_length > capacity) {
        __le_vec_expand_to_request(v, new_length);
        _le_vec_set_length(v, new_length);
        return;
    }

    _le_vec_set_length(v, new_length);

    if (le_vec_get_length(v) < le_vec_get_capacity(v) / 2) {
        _le_vec_shrink_down_to_length(v);
    }
}

void le_vec_extend(struct le_vec *v, struct le_vec const *other) {
    if (le_vec_is_empty(other)) {
        return;
    }

    size_t v_length = le_vec_get_length(v);
    size_t other_length = le_vec_get_length(other);

    size_t total_length = v_length + other_length;

    le_vec_resize(v, total_length);

    for (size_t i = 0; i < other_length; i++) {
        size_t first_index = i + v_length;
        size_t other_index = i;

        v->data[first_index] = other->data[other_index];
    }
}

void _le_vec_map(struct le_vec *dest, struct le_vec const *src, TYPE (*f)(TYPE)) {
    for (size_t i = 0; i < le_vec_get_length(src); i++) {
        dest->data[i] = f(src->data[i]);
    }
}

struct le_vec *le_vec_map(struct le_vec *v, TYPE (*f)(TYPE)) {
    struct le_vec *new_v = le_vec_init_with_length(le_vec_get_length(v));

    _le_vec_map(new_v, v, f);

    return new_v;
}

void le_vec_for_each(struct le_vec *v, TYPE (*f)(TYPE)) {
    _le_vec_map(v, v, f);
}
