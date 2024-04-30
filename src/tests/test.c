#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#include "le_vec.h"
#include "util.h"
#include "tests/common.h"

void test_init(void) {
    struct le_vec *v = le_vec_init();

    ASSERT_NOT_EQUAL(v, NULL)
    ASSERT_EQUAL(le_vec_get_capacity(v), LE_VEC_DEFAULT_CAPACITY)
    ASSERT_EQUAL(le_vec_get_length(v), 0)

    le_vec_destroy(v);
}

void test_init_with_length(void) {
    struct le_vec *v = le_vec_init_with_length(10);

    ASSERT_NOT_EQUAL(v, NULL)
    ASSERT_EQUAL(le_vec_get_capacity(v), 10)
    ASSERT_EQUAL(le_vec_get_length(v), 10)

    le_vec_destroy(v);
}

void test_init_with_invalid_length(void) {
    struct le_vec *v = le_vec_init_with_length(0);

    ASSERT_EQUAL(v, NULL)
}

void test_destroy_null(void) {
    struct le_vec *v = NULL;

    le_vec_destroy(v);
}

void test_length_and_capacity_after_push(void) {
    struct le_vec *v = le_vec_init();

    le_vec_push_back(v, 100);
    ASSERT_EQUAL(le_vec_get_length(v), 1)
    ASSERT_EQUAL(le_vec_get_capacity(v), LE_VEC_DEFAULT_CAPACITY)

    le_vec_push_back(v, 123);
    ASSERT_EQUAL(le_vec_get_length(v), 2)
    ASSERT_EQUAL(le_vec_get_capacity(v), LE_VEC_DEFAULT_CAPACITY)

    le_vec_push_back(v, 900);
    ASSERT_EQUAL(le_vec_get_length(v), 3)
    ASSERT_EQUAL(le_vec_get_capacity(v), LE_VEC_DEFAULT_CAPACITY)

    le_vec_destroy(v);
}

void test_push_pop(void) {
    struct le_vec *v = le_vec_init();

    le_vec_push_back(v, 11);
    ASSERT_EQUAL(le_vec_get_length(v), 1)
    ASSERT_EQUAL(le_vec_get_capacity(v), LE_VEC_DEFAULT_CAPACITY)

    le_vec_push_back(v, 22);
    ASSERT_EQUAL(le_vec_get_length(v), 2)
    ASSERT_EQUAL(le_vec_get_capacity(v), LE_VEC_DEFAULT_CAPACITY)

    int val = le_vec_pop_back(v);
    ASSERT_EQUAL(val, 22);
    ASSERT_EQUAL(le_vec_get_length(v), 1)
    ASSERT_EQUAL(le_vec_get_capacity(v), LE_VEC_DEFAULT_CAPACITY)

    le_vec_push_back(v, 33);
    ASSERT_EQUAL(le_vec_get_length(v), 2)
    ASSERT_EQUAL(le_vec_get_capacity(v), LE_VEC_DEFAULT_CAPACITY)

    le_vec_destroy(v);
}

void test_pop(void) {
    struct le_vec *v = le_vec_init();
    le_vec_push_back(v, 11);
    le_vec_push_back(v, 22);

    int val = le_vec_pop_back(v);
    ASSERT_EQUAL(val, 22);
    ASSERT_EQUAL(le_vec_get_length(v), 1)
    ASSERT_EQUAL(le_vec_get_capacity(v), LE_VEC_DEFAULT_CAPACITY)

    bool success = false;
    int val1 = le_vec_s_pop_back(v, &success);
    ASSERT_EQUAL(success, true);
    ASSERT_EQUAL(val, 11);
    ASSERT_EQUAL(le_vec_get_length(v), 0)
    ASSERT_EQUAL(le_vec_get_capacity(v), LE_VEC_DEFAULT_CAPACITY)

    success = false;
    int val2 = le_vec_s_pop_back(v, &success);
    ASSERT_EQUAL(success, false);
    ASSERT_EQUAL(le_vec_get_length(v), 0)
    ASSERT_EQUAL(le_vec_get_capacity(v), LE_VEC_DEFAULT_CAPACITY)

    le_vec_destroy(v);
}

void test_is_index_valid(void) {
    struct le_vec *v = le_vec_init();

    ASSERT_EQUAL(le_vec_is_index_valid(v, 0), false)
    ASSERT_EQUAL(le_vec_is_index_valid(v, 1), false)

    le_vec_push_back(v, 100);
    le_vec_push_back(v, 250);
    le_vec_push_back(v, 600);

    ASSERT_EQUAL(le_vec_is_index_valid(v, 0), true)
    ASSERT_EQUAL(le_vec_is_index_valid(v, 1), true)
    ASSERT_EQUAL(le_vec_is_index_valid(v, 2), true)
    ASSERT_EQUAL(le_vec_is_index_valid(v, 3), false)

    le_vec_destroy(v);
}

void test_last_index(void) {
    struct le_vec *v = le_vec_init();

    le_vec_push_back(v, 12);
    ASSERT_EQUAL(le_vec_get_last_index(v), 0)
    le_vec_push_back(v, 23);
    ASSERT_EQUAL(le_vec_get_last_index(v), 1)
    le_vec_push_back(v, 34);
    ASSERT_EQUAL(le_vec_get_last_index(v), 2)

    le_vec_pop_back(v);
    ASSERT_EQUAL(le_vec_get_last_index(v), 1)
    le_vec_pop_back(v);
    ASSERT_EQUAL(le_vec_get_last_index(v), 0)

    le_vec_destroy(v);
}

void test_get_at(void) {
    struct le_vec *v = le_vec_init();

    le_vec_push_back(v, 123);
    le_vec_push_back(v, 456);
    le_vec_push_back(v, 789);

    ASSERT_EQUAL(le_vec_get_at(v, 0), 123)
    ASSERT_EQUAL(le_vec_get_at(v, 1), 456)
    ASSERT_EQUAL(le_vec_get_at(v, 2), 789)

    le_vec_destroy(v);
}

void test_resize(void) {
    struct le_vec *v = le_vec_init();

    le_vec_resize(v, 25);
    ASSERT_EQUAL(le_vec_get_length(v), 25)
    ASSERT_EQUAL(le_vec_get_capacity(v), LE_VEC_DEFAULT_CAPACITY)

    le_vec_resize(v, 10);
    ASSERT_EQUAL(le_vec_get_length(v), 10)
    ASSERT_EQUAL(le_vec_get_capacity(v), 10)

    le_vec_resize(v, 60);
    ASSERT_EQUAL(le_vec_get_length(v), 60)
    ASSERT_BGE(le_vec_get_capacity(v), 60)

    le_vec_resize(v, 0);
    ASSERT_EQUAL(le_vec_get_length(v), 0)
    ASSERT_EQUAL(le_vec_get_capacity(v), 0)

    le_vec_destroy(v);
}

void test_extend(void) {
    struct le_vec *v1 = le_vec_init();
    le_vec_push_back(v1, 1);
    le_vec_push_back(v1, 1);
    le_vec_push_back(v1, 1);

    struct le_vec *v2 = le_vec_init();
    le_vec_push_back(v2, 2);
    le_vec_push_back(v2, 2);

    struct le_vec *v3 = le_vec_init();

    le_vec_extend(v2, v3);
    ASSERT_EQUAL(le_vec_get_length(v2), 2)
    ASSERT_EQUAL(le_vec_get_length(v3), 0)
    ASSERT_EQUAL(le_vec_get_at(v2, 0), 2)
    ASSERT_EQUAL(le_vec_get_at(v2, 1), 2)

    le_vec_extend(v1, v2);
    ASSERT_EQUAL(le_vec_get_length(v1), 5)
    ASSERT_EQUAL(le_vec_get_length(v2), 2)
    ASSERT_EQUAL(le_vec_get_at(v1, 0), 1)
    ASSERT_EQUAL(le_vec_get_at(v1, 1), 1)
    ASSERT_EQUAL(le_vec_get_at(v1, 2), 1)
    ASSERT_EQUAL(le_vec_get_at(v1, 3), 2)
    ASSERT_EQUAL(le_vec_get_at(v1, 4), 2)

    le_vec_destroy(v3);
    le_vec_destroy(v2);
    le_vec_destroy(v1);
}

int multiply_by_2(int n) {
    return n * 2;
}

void test_map(void) {
    struct le_vec *v = le_vec_init();
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 2);
    le_vec_push_back(v, 3);

    struct le_vec *new_v = le_vec_map(v, multiply_by_2);

    ASSERT_NOT_EQUAL(new_v, NULL)
    ASSERT_EQUAL(le_vec_get_length(new_v), 3)
    ASSERT_EQUAL(le_vec_get_at(new_v, 0), 2)
    ASSERT_EQUAL(le_vec_get_at(new_v, 1), 4)
    ASSERT_EQUAL(le_vec_get_at(new_v, 2), 6)

    le_vec_destroy(v);
    le_vec_destroy(new_v);
}

void test_for_each(void) {
    struct le_vec *v = le_vec_init();
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 2);
    le_vec_push_back(v, 3);

    le_vec_for_each(v, multiply_by_2);

    ASSERT_EQUAL(le_vec_get_length(v), 3)
    ASSERT_EQUAL(le_vec_get_at(v, 0), 2)
    ASSERT_EQUAL(le_vec_get_at(v, 1), 4)
    ASSERT_EQUAL(le_vec_get_at(v, 2), 6)

    le_vec_destroy(v);
}

void test_copy(void) {
    struct le_vec *v = le_vec_init();
    le_vec_push_back(v, 228);
    le_vec_push_back(v, 1337);
    le_vec_push_back(v, 420);
    le_vec_push_back(v, 431);

    struct le_vec *v_copy = le_vec_copy(v);
    ASSERT_NOT_EQUAL(v_copy, NULL)
    ASSERT_NOT_EQUAL(v_copy, v)
    ASSERT_EQUAL(le_vec_get_length(v), 4)
    ASSERT_EQUAL(le_vec_get_at(v_copy, 0), 228)
    ASSERT_EQUAL(le_vec_get_at(v_copy, 1), 1337)
    ASSERT_EQUAL(le_vec_get_at(v_copy, 2), 420)
    ASSERT_EQUAL(le_vec_get_at(v_copy, 3), 431)

    le_vec_destroy(v);
    le_vec_destroy(v_copy);
}

void test_reversed_odd(void) {
    struct le_vec *v = le_vec_init();
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 4);
    le_vec_push_back(v, 9);
    le_vec_push_back(v, 16);
    le_vec_push_back(v, 25);

    le_vec_reverse(v);
    ASSERT_EQUAL(le_vec_get_length(v), 5)
    ASSERT_EQUAL(le_vec_get_at(v, 0), 25)
    ASSERT_EQUAL(le_vec_get_at(v, 1), 16)
    ASSERT_EQUAL(le_vec_get_at(v, 2), 9)
    ASSERT_EQUAL(le_vec_get_at(v, 3), 4)
    ASSERT_EQUAL(le_vec_get_at(v, 4), 1)

    le_vec_destroy(v);
}

void test_reversed_even(void) {
    struct le_vec *v = le_vec_init();
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 4);
    le_vec_push_back(v, 9);
    le_vec_push_back(v, 16);

    le_vec_reverse(v);
    ASSERT_EQUAL(le_vec_get_length(v), 4)
    ASSERT_EQUAL(le_vec_get_at(v, 0), 16)
    ASSERT_EQUAL(le_vec_get_at(v, 1), 9)
    ASSERT_EQUAL(le_vec_get_at(v, 2), 4)
    ASSERT_EQUAL(le_vec_get_at(v, 3), 1)

    le_vec_destroy(v);
}

void test_reversed_two(void) {
    struct le_vec *v = le_vec_init();
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 4);

    le_vec_reverse(v);
    ASSERT_EQUAL(le_vec_get_length(v), 2)
    ASSERT_EQUAL(le_vec_get_at(v, 0), 4)
    ASSERT_EQUAL(le_vec_get_at(v, 1), 1)

    le_vec_destroy(v);
}

void test_reversed_one(void) {
    struct le_vec *v = le_vec_init();
    le_vec_push_back(v, 9999);

    le_vec_reverse(v);
    ASSERT_EQUAL(le_vec_get_length(v), 1)
    ASSERT_EQUAL(le_vec_get_at(v, 0), 9999)

    le_vec_destroy(v);
}

void test_reverse(void) {
    struct le_vec *v = le_vec_init();
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 4);
    le_vec_push_back(v, 9);
    le_vec_push_back(v, 16);
    le_vec_push_back(v, 25);

    struct le_vec *reversed_v = le_vec_reversed(v);
    ASSERT_NOT_EQUAL(reversed_v, NULL)
    ASSERT_NOT_EQUAL(reversed_v, v)

    ASSERT_EQUAL(le_vec_get_length(v), 5)
    ASSERT_EQUAL(le_vec_get_at(v, 0), 1)
    ASSERT_EQUAL(le_vec_get_at(v, 1), 4)
    ASSERT_EQUAL(le_vec_get_at(v, 2), 9)
    ASSERT_EQUAL(le_vec_get_at(v, 3), 16)
    ASSERT_EQUAL(le_vec_get_at(v, 4), 25)

    ASSERT_EQUAL(le_vec_get_length(reversed_v), 5)
    ASSERT_EQUAL(le_vec_get_at(reversed_v, 0), 25)
    ASSERT_EQUAL(le_vec_get_at(reversed_v, 1), 16)
    ASSERT_EQUAL(le_vec_get_at(reversed_v, 2), 9)
    ASSERT_EQUAL(le_vec_get_at(reversed_v, 3), 4)
    ASSERT_EQUAL(le_vec_get_at(reversed_v, 4), 1)

    le_vec_destroy(v);
    le_vec_destroy(reversed_v);
}

void test_slice(void) {
    struct le_vec *v = le_vec_init();
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 2);
    le_vec_push_back(v, 4);
    le_vec_push_back(v, 8);
    le_vec_push_back(v, 16);
    le_vec_push_back(v, 32);

    struct le_vec *slice = le_vec_slice(v, 2, 4);
    ASSERT_NOT_EQUAL(slice, NULL)
    ASSERT_NOT_EQUAL(slice, v)
    ASSERT_EQUAL(le_vec_get_length(slice), 2)
    ASSERT_EQUAL(le_vec_get_at(slice, 0), 4)
    ASSERT_EQUAL(le_vec_get_at(slice, 1), 8)

    le_vec_destroy(v);
    le_vec_destroy(slice);
}

void test_slice_one(void) {
    struct le_vec *v = le_vec_init();
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 2);
    le_vec_push_back(v, 4);
    le_vec_push_back(v, 8);
    le_vec_push_back(v, 16);
    le_vec_push_back(v, 32);

    struct le_vec *sl = le_vec_slice(v, 1, 2);
    ASSERT_NOT_EQUAL(sl, NULL)
    ASSERT_NOT_EQUAL(sl, v)
    ASSERT_EQUAL(le_vec_get_length(sl), 1)
    ASSERT_EQUAL(le_vec_get_at(sl, 0), 2)

    le_vec_destroy(v);
    le_vec_destroy(sl);
}

void test_slice_all(void) {
    struct le_vec *v = le_vec_init();
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 2);
    le_vec_push_back(v, 4);
    le_vec_push_back(v, 8);
    le_vec_push_back(v, 16);
    le_vec_push_back(v, 32);

    struct le_vec *slice = le_vec_slice(v, 0, 6);
    ASSERT_NOT_EQUAL(slice, NULL)
    ASSERT_NOT_EQUAL(slice, v)
    ASSERT_EQUAL(le_vec_get_length(slice), 6)
    ASSERT_EQUAL(le_vec_get_at(v, 0), 1)
    ASSERT_EQUAL(le_vec_get_at(v, 1), 2)
    ASSERT_EQUAL(le_vec_get_at(v, 2), 4)
    ASSERT_EQUAL(le_vec_get_at(v, 3), 8)
    ASSERT_EQUAL(le_vec_get_at(v, 4), 16)
    ASSERT_EQUAL(le_vec_get_at(v, 5), 32)

    le_vec_destroy(v);
    le_vec_destroy(slice);
}

void test_slice_invalid(void) {
    struct le_vec *v = le_vec_init();
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 2);
    le_vec_push_back(v, 4);
    le_vec_push_back(v, 8);
    le_vec_push_back(v, 16);
    le_vec_push_back(v, 32);

    struct le_vec *slice1 = le_vec_slice(v, 0, 0);
    ASSERT_EQUAL(slice1, NULL)

    struct le_vec *slice2 = le_vec_slice(v, 0, 7);
    ASSERT_EQUAL(slice2, NULL)

    struct le_vec *slice3 = le_vec_slice(v, 3, 1);
    ASSERT_EQUAL(slice3, NULL)

    struct le_vec *slice4 = le_vec_slice(v, 1, 1);
    ASSERT_EQUAL(slice4, NULL)

    struct le_vec *slice5 = le_vec_slice(v, 9, 12);
    ASSERT_EQUAL(slice5, NULL)

    le_vec_destroy(v);
}

void test_count(void) {
    struct le_vec *v = le_vec_init();
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 2);
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 2);
    le_vec_push_back(v, 2);
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 1);

    size_t count1 = le_vec_count(v, 1);
    ASSERT_EQUAL(count1, 7)

    size_t count2 = le_vec_count(v, 2);
    ASSERT_EQUAL(count2, 3)

    le_vec_destroy(v);
}

void test_count_non_present(void) {
    struct le_vec *v = le_vec_init();
    le_vec_push_back(v, 2);
    le_vec_push_back(v, 7);
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 8);
    le_vec_push_back(v, 2);
    le_vec_push_back(v, 8);
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 8);

    size_t count = le_vec_count(v, 9999);
    ASSERT_EQUAL(count, 0)

    le_vec_destroy(v);
}

void test_find(void) {
    struct le_vec *v = le_vec_init();
    le_vec_push_back(v, 3);
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 4);
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 5);
    le_vec_push_back(v, 9);
    le_vec_push_back(v, 2);

    size_t idx1 = le_vec_find(v, 3);
    ASSERT_EQUAL(idx1, 0)

    size_t idx2 = le_vec_find(v, 1);
    ASSERT_EQUAL(idx2, 1)

    size_t idx3 = le_vec_find(v, 4);
    ASSERT_EQUAL(idx3, 2)

    size_t idx4 = le_vec_find(v, 5);
    ASSERT_EQUAL(idx4, 4)

    size_t idx5 = le_vec_find(v, 9);
    ASSERT_EQUAL(idx5, 5)

    size_t idx6 = le_vec_find(v, 2);
    ASSERT_EQUAL(idx6, 6)

    le_vec_destroy(v);
}

void test_find_invalid(void) {
    struct le_vec *v = le_vec_init();
    le_vec_push_back(v, 3);
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 4);

    size_t idx = le_vec_find(v, 999999);
    ASSERT_NOT_EQUAL(idx, 0)
    ASSERT_NOT_EQUAL(idx, 1)
    ASSERT_NOT_EQUAL(idx, 2)

    le_vec_destroy(v);
}

void test_find_n(void) {
    struct le_vec *v = le_vec_init();
    le_vec_push_back(v, 0);
    le_vec_push_back(v, 1111);
    le_vec_push_back(v, 0);
    le_vec_push_back(v, 1111);
    le_vec_push_back(v, 0);
    le_vec_push_back(v, 0);
    le_vec_push_back(v, 1111);

    size_t idx1 = le_vec_find_n(v, 1111, 1);
    ASSERT_EQUAL(idx1, 1)

    size_t idx2 = le_vec_find_n(v, 1111, 2);
    ASSERT_EQUAL(idx2, 3)

    size_t idx3 = le_vec_find_n(v, 1111, 3);
    ASSERT_EQUAL(idx3, 6)

    le_vec_destroy(v);
}

void test_rfind(void) {
    struct le_vec *v = le_vec_init();
    le_vec_push_back(v, 999);
    le_vec_push_back(v, 0);
    le_vec_push_back(v, 999);
    le_vec_push_back(v, 0);
    le_vec_push_back(v, 999);
    le_vec_push_back(v, 999);

    size_t idx = le_vec_rfind(v, 999);
    ASSERT_EQUAL(idx, 5)

    le_vec_destroy(v);
}

void test_rfind_invalid(void) {
    struct le_vec *v = le_vec_init();
    le_vec_push_back(v, 3);
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 4);

    size_t idx = le_vec_rfind(v, 999999);
    ASSERT_NOT_EQUAL(idx, 0)
    ASSERT_NOT_EQUAL(idx, 1)
    ASSERT_NOT_EQUAL(idx, 2)

    le_vec_destroy(v);
}

void test_rfind_n(void) {
    struct le_vec *v = le_vec_init();
    le_vec_push_back(v, 0);
    le_vec_push_back(v, 1111);
    le_vec_push_back(v, 0);
    le_vec_push_back(v, 1111);
    le_vec_push_back(v, 0);
    le_vec_push_back(v, 0);
    le_vec_push_back(v, 1111);

    size_t idx1 = le_vec_rfind_n(v, 1111, 1);
    ASSERT_EQUAL(idx1, 6)

    size_t idx2 = le_vec_rfind_n(v, 1111, 2);
    ASSERT_EQUAL(idx2, 3)

    size_t idx3 = le_vec_rfind_n(v, 1111, 3);
    ASSERT_EQUAL(idx3, 1)

    le_vec_destroy(v);
}

void test_replace_all(void) {
    struct le_vec *v = le_vec_init();
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 300);
    le_vec_push_back(v, 20);
    le_vec_push_back(v, 300);
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 20);
    le_vec_push_back(v, 1);

    size_t replaced_cntr = le_vec_replace_all(v, 1, 9000);
    
    ASSERT_EQUAL(replaced_cntr, 3)
    ASSERT_EQUAL(le_vec_get_at(v, 0), 9000)
    ASSERT_EQUAL(le_vec_get_at(v, 1), 300)
    ASSERT_EQUAL(le_vec_get_at(v, 2), 20)
    ASSERT_EQUAL(le_vec_get_at(v, 3), 300)
    ASSERT_EQUAL(le_vec_get_at(v, 4), 9000)
    ASSERT_EQUAL(le_vec_get_at(v, 5), 20)
    ASSERT_EQUAL(le_vec_get_at(v, 6), 9000)

    le_vec_destroy(v);
}

void test_replace_all_non_present(void) {
    struct le_vec *v = le_vec_init();
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 2);
    le_vec_push_back(v, 3);
    le_vec_push_back(v, 4);
    le_vec_push_back(v, 5);
    le_vec_push_back(v, 6);
    le_vec_push_back(v, 7);

    size_t replaced_cntr = le_vec_replace_all(v, 8080, 8000);
    
    ASSERT_EQUAL(replaced_cntr, 0)
    ASSERT_EQUAL(le_vec_get_at(v, 0), 1)
    ASSERT_EQUAL(le_vec_get_at(v, 1), 2)
    ASSERT_EQUAL(le_vec_get_at(v, 2), 3)
    ASSERT_EQUAL(le_vec_get_at(v, 3), 4)
    ASSERT_EQUAL(le_vec_get_at(v, 4), 5)
    ASSERT_EQUAL(le_vec_get_at(v, 5), 6)
    ASSERT_EQUAL(le_vec_get_at(v, 6), 7)

    le_vec_destroy(v);
}

void test_replace_n(void) {
    struct le_vec *v = le_vec_init();
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 1);

    size_t replaced_cntr = le_vec_replace_n(v, 1, 4000, 3);
    
    ASSERT_EQUAL(replaced_cntr, 3)
    ASSERT_EQUAL(le_vec_get_at(v, 0), 4000)
    ASSERT_EQUAL(le_vec_get_at(v, 1), 4000)
    ASSERT_EQUAL(le_vec_get_at(v, 2), 4000)
    ASSERT_EQUAL(le_vec_get_at(v, 3), 1)
    ASSERT_EQUAL(le_vec_get_at(v, 4), 1)
    ASSERT_EQUAL(le_vec_get_at(v, 5), 1)
    ASSERT_EQUAL(le_vec_get_at(v, 6), 1)

    le_vec_destroy(v);
}

void test_rreplace_n(void) {
    struct le_vec *v = le_vec_init();
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 1);
    le_vec_push_back(v, 1);

    size_t replaced_cntr = le_vec_rreplace_n(v, 1, 4000, 3);
    
    ASSERT_EQUAL(replaced_cntr, 3)
    ASSERT_EQUAL(le_vec_get_at(v, 0), 1)
    ASSERT_EQUAL(le_vec_get_at(v, 1), 1)
    ASSERT_EQUAL(le_vec_get_at(v, 2), 1)
    ASSERT_EQUAL(le_vec_get_at(v, 3), 1)
    ASSERT_EQUAL(le_vec_get_at(v, 4), 4000)
    ASSERT_EQUAL(le_vec_get_at(v, 5), 4000)
    ASSERT_EQUAL(le_vec_get_at(v, 6), 4000)

    le_vec_destroy(v);
}

void (*TESTS[])(void) = {
    test_init,
    test_init_with_length,
    test_init_with_invalid_length,
    test_destroy_null,
    test_length_and_capacity_after_push,
    test_push_pop,
    test_is_index_valid,
    test_last_index,
    test_get_at,
    test_resize,
    test_extend,
    test_map,
    test_for_each,
    test_copy,
    test_reversed_even,
    test_reversed_odd,
    test_reversed_two,
    test_reversed_one,
    test_reverse,
    test_slice,
    test_slice_one,
    test_slice_all,
    test_slice_invalid,
    test_count,
    test_count_non_present,
    test_find,
    test_find_invalid,
    test_find_n,
    test_rfind,
    test_rfind_invalid,
    test_rfind_n,
    test_replace_all,
    test_replace_all_non_present,
    test_replace_n,
    test_rreplace_n,
};

int main() {
    puts("Running tests...");
    print_newline();

    for (size_t i = 0; i < array_length(TESTS); i++) {
        void (*test)(void) = TESTS[i];
        test();
    }

    print_newline();
    printf("Finished. %d/%d tests passed.", ASSERT_CNTR - ERR_CNTR, ASSERT_CNTR);
    print_newline();
    return 0;
}
