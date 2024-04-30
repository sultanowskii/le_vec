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
