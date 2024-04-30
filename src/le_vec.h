#pragma once

#include <stdbool.h>
#include <stddef.h>

#define TYPE int
#define DEFAULT_CAPACITY 32

struct le_vec;

struct le_vec *le_vec_init(void);
struct le_vec *le_vec_init_with_length(size_t length_request);
void le_vec_destroy(struct le_vec *v);

size_t le_vec_get_length(struct le_vec const *v);
size_t le_vec_get_capacity(struct le_vec const *v);

void le_vec_push_back(struct le_vec *v, TYPE value);

TYPE le_vec_get_at(struct le_vec const *v, size_t index);
bool le_vec_set_at(struct le_vec *v, size_t index, TYPE value);

bool le_vec_is_index_valid(struct le_vec const *v, size_t index);
