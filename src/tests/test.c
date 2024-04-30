#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#include "le_vec.h"
#include "util.h"
#include "tests/common.h"

void test_init(void) {
    struct le_vec *v = le_vec_init();

    ASSERT_NOT_EQUAL(v, NULL)
    ASSERT_EQUAL(le_vec_get_capacity(v), DEFAULT_CAPACITY)
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
    ASSERT_EQUAL(le_vec_get_length(v), 0)
    ASSERT_EQUAL(le_vec_get_capacity(v), DEFAULT_CAPACITY)

    le_vec_push_back(v, 100);
    ASSERT_EQUAL(le_vec_get_length(v), 1)
    ASSERT_EQUAL(le_vec_get_capacity(v), DEFAULT_CAPACITY)

    le_vec_push_back(v, 123);
    ASSERT_EQUAL(le_vec_get_length(v), 2)
    ASSERT_EQUAL(le_vec_get_capacity(v), DEFAULT_CAPACITY)

    le_vec_push_back(v, 900);
    ASSERT_EQUAL(le_vec_get_length(v), 3)
    ASSERT_EQUAL(le_vec_get_capacity(v), DEFAULT_CAPACITY)

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

void (*TESTS[])(void) = {
    test_init,
    test_init_with_length,
    test_init_with_invalid_length,
    test_destroy_null,
    test_length_and_capacity_after_push,
    test_is_index_valid,
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
