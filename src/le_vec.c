#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "le_vec.h"

struct le_vec {
    size_t capacity;
    size_t length;
    LE_VEC_TYPE *data;
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
void _le_vec_map(struct le_vec *dest, struct le_vec const *src, LE_VEC_TYPE (*f)(LE_VEC_TYPE));

struct le_vec *le_vec_init(void) {
    struct le_vec *v = malloc(sizeof(struct le_vec));
    LE_VEC_TYPE *data = malloc(LE_VEC_DEFAULT_CAPACITY);

    v->capacity = LE_VEC_DEFAULT_CAPACITY;
    v->length = 0;
    v->data = data;

    return v;
}

struct le_vec *le_vec_init_with_length(size_t request) {
    if (request == 0) {
        return NULL;
    }

    struct le_vec *v = malloc(sizeof(struct le_vec));
    LE_VEC_TYPE *data = malloc(request);

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

void le_vec_push_back(struct le_vec *v, LE_VEC_TYPE value) {
    if (v->length >= v->capacity) {
        _le_vec_expand(v);
    }
    v->length++;

    size_t last_index = le_vec_get_last_index(v);
    v->data[last_index] = value;
}

LE_VEC_TYPE le_vec_pop_back(struct le_vec *v) {
    size_t last_index = le_vec_get_last_index(v);
    LE_VEC_TYPE value = v->data[last_index];

    v->length--;

    return value;
}

LE_VEC_TYPE le_vec_s_pop_back(struct le_vec *v, bool *success) {
    if (le_vec_is_empty(v)) {
        *success = false;
        return (LE_VEC_TYPE)0;
    }

    LE_VEC_TYPE value = le_vec_pop_back(v);
    *success = true;

    return value;
}

bool le_vec_is_index_valid(struct le_vec const *v, size_t index) {
    return 0 <= index && index < le_vec_get_length(v);
}

size_t le_vec_get_last_index(struct le_vec const *v) {
    return le_vec_get_length(v) - 1;
}

LE_VEC_TYPE le_vec_get_at(struct le_vec const *v, size_t index) {
    return v->data[index];
}

bool le_vec_set_at(struct le_vec *v, size_t index, LE_VEC_TYPE value) {
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
        size_t v_index = i + v_length;
        size_t other_index = i;

        le_vec_set_at(v, v_index, le_vec_get_at(other, other_index));
    }
}

void _le_vec_map(struct le_vec *dest, struct le_vec const *src, LE_VEC_TYPE (*f)(LE_VEC_TYPE)) {
    for (size_t i = 0; i < le_vec_get_length(src); i++) {
        dest->data[i] = f(src->data[i]);
    }
}

struct le_vec *le_vec_map(struct le_vec const *v, LE_VEC_TYPE (*f)(LE_VEC_TYPE)) {
    struct le_vec *new_v = le_vec_init_with_length(le_vec_get_length(v));

    _le_vec_map(new_v, v, f);

    return new_v;
}

void le_vec_for_each(struct le_vec *v, LE_VEC_TYPE (*f)(LE_VEC_TYPE)) {
    _le_vec_map(v, v, f);
}

LE_VEC_TYPE return_itself(LE_VEC_TYPE value) {
    return value;
}

struct le_vec *le_vec_copy(struct le_vec const *v) {
    return le_vec_map(v, return_itself);
}

struct le_vec *le_vec_reversed(struct le_vec const *v) {
    size_t v_length = le_vec_get_length(v);
    size_t v_last_index = le_vec_get_last_index(v);
    struct le_vec *new_v = le_vec_init_with_length(v_length);

    for (size_t i = 0; i < v_length; i++) {
        size_t new_index = i;
        size_t v_index = v_last_index - i;

        le_vec_set_at(new_v, new_index, le_vec_get_at(v, v_index));
    }

    return new_v;
}

void le_vec_reverse(struct le_vec *v) {
    size_t v_length = le_vec_get_length(v);
    size_t v_last_index = le_vec_get_last_index(v);

    for (size_t i = 0; i < v_length / 2; i++) {
        size_t l = i;
        size_t r = v_last_index - i;

        LE_VEC_TYPE l_value = le_vec_get_at(v, l);
        le_vec_set_at(v, l, le_vec_get_at(v, r));
        le_vec_set_at(v, r, l_value);
    }
}

struct le_vec *le_vec_slice(struct le_vec const *v, size_t start, size_t end) {
    if (!le_vec_is_index_valid(v, start) || !le_vec_is_index_valid(v, end - 1)) {
        return NULL;
    }

    if (start > end) {
        return NULL;
    }

    size_t slice_length = end - start;

    struct le_vec *slice = le_vec_init_with_length(slice_length);

    for (size_t i = 0; i < slice_length; i++) {
        size_t slice_index = i;
        size_t v_index = i + start;

        le_vec_set_at(slice, slice_index, le_vec_get_at(v, v_index));
    }

    return slice;
}

size_t le_vec_find(struct le_vec const *v, LE_VEC_TYPE elem) {
    return le_vec_find_n(v, elem, 1);
}

size_t le_vec_find_n(struct le_vec const *v, LE_VEC_TYPE elem, size_t n) {
    size_t cntr = 0;
    for (size_t i = 0; i < le_vec_get_length(v); i++) {
        if (le_vec_get_at(v, i) == elem) {
            cntr++;
            if (cntr == n) {
                return i;
            }
        }
    }

    return (size_t)-1;
}

size_t le_vec_rfind(struct le_vec const *v, LE_VEC_TYPE elem) {
    return le_vec_rfind_n(v, elem, 1);
}

size_t le_vec_rfind_n(struct le_vec const *v, LE_VEC_TYPE elem, size_t n) {
    size_t cntr = 0;
    size_t v_last_index = le_vec_get_last_index(v);

    for (size_t i = 0; i < le_vec_get_length(v); i++) {
        size_t v_index = v_last_index - i;
        if (le_vec_get_at(v, v_index) == elem) {
            cntr++;
            if (cntr == n) {
                return v_index;
            }
        }
    }

    return (size_t)-1;
}
