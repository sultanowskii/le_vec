#pragma once

#include <stdbool.h>
#include <stddef.h>

// Type of underlying elements
#define LE_VEC_TYPE int
// Default vector capacity
#define LE_VEC_DEFAULT_CAPACITY 32

// Vector itself
// You should use it using methods below, internals are not of your concern
// `Length` is a default concept
// `Capacity` is an addition for internal memory management
struct le_vec;

// Creates and initiates le_vec
struct le_vec *le_vec_init(void);
// Creates and initiates le_vec with requested length
struct le_vec *le_vec_init_with_length(size_t request);
// Destroys le_vec.
void le_vec_destroy(struct le_vec *v);

// Returns vector length
size_t le_vec_get_length(struct le_vec const *v);
// Returns vector capacity (available space)
size_t le_vec_get_capacity(struct le_vec const *v);
// Checks if vector empty (does not contain any elements)
bool le_vec_is_empty(struct le_vec const *v);

// Pushes element after the last element, increments length
void le_vec_push_back(struct le_vec *v, LE_VEC_TYPE value);
// Removes and returns element the last element, decrements length
LE_VEC_TYPE le_vec_pop_back(struct le_vec *v);
// Same as pop_back(), but checks if it is possible. If not - success = false
LE_VEC_TYPE le_vec_s_pop_back(struct le_vec *v, bool *success);

// Checks if index valid within vector
bool le_vec_is_index_valid(struct le_vec const *v, size_t index);
// Returns last index in vector
size_t le_vec_get_last_index(struct le_vec const *v);

// Gets element at index.
LE_VEC_TYPE le_vec_get_at(struct le_vec const *v, size_t index);
// Sets element at index to a new value.
bool le_vec_set_at(struct le_vec *v, size_t index, LE_VEC_TYPE value);

// Changes the length of vector. If vector is shrank, data might get lost
void le_vec_resize(struct le_vec *v, size_t new_length);

// Adds all elements of `other` after the end of v
void le_vec_extend(struct le_vec *v, struct le_vec const *other);

// Creates a new vector, where each element is a result of `f()` on corresponding `v` element
struct le_vec *le_vec_map(struct le_vec const *v, LE_VEC_TYPE (*f)(LE_VEC_TYPE));
// Same as `map()`, but does so in-place.
void le_vec_for_each(struct le_vec *v, LE_VEC_TYPE (*f)(LE_VEC_TYPE));

// Creates a copy of vector
struct le_vec *le_vec_copy(struct le_vec const *v);

// Creates a reversed copy of vector
struct le_vec *le_vec_reversed(struct le_vec const *v);
// Reverses vector in-place
void le_vec_reverse(struct le_vec *v);

// Creates a [start; end) slice
// Returns NULL if something is wrong with indexes
struct le_vec *le_vec_slice(struct le_vec const *v, size_t start, size_t end);

// Returns index of first elem entry
// Returns invalid index if not found
size_t le_vec_find(struct le_vec const *v, LE_VEC_TYPE elem);
// Returns index of `n`th elem entry
// Returns invalid index if not found
size_t le_vec_find_n(struct le_vec const *v, LE_VEC_TYPE elem, size_t n);

// Same as `find()`, but searches from end to start
size_t le_vec_rfind(struct le_vec const *v, LE_VEC_TYPE elem);
// Same as `find_n()`, but searches from end to start
size_t le_vec_rfind_n(struct le_vec const *v, LE_VEC_TYPE elem, size_t n);
