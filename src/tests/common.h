#pragma once

#include <stddef.h>

static int ERR_CNTR = 0;
static int ASSERT_CNTR = 0;

// If x evaluates to 0, prints message with details.
#define ASSERT(x, msg) {                                      \
    if (!(x)) {                                               \
        printf(                                               \
            "[!] Test #%d failed (%s, %s(), line %d): %s\n",  \
            __COUNTER__ + 1,                                  \
            __FILE__,                                         \
            __func__,                                         \
            __LINE__,                                         \
            (msg)                                             \
        );                                                    \
        ERR_CNTR++;                                           \
    }                                                         \
    ASSERT_CNTR++;                                            \
}

// ASSERT(s1 == s2)
#define ASSERT_STRINGS_EQUAL(a, b)                     \
    ASSERT(strcmp((a), (b)) == 0, ("strings differ"))

// ASSERT(a == b)
#define ASSERT_EQUAL(a, b)                 \
    ASSERT((a) == (b), ("values differ"))

// ASSERT(a >= b)
#define ASSERT_BGE(a, b)                                    \
    ASSERT((a) >= (b), ("first value is less than second"))

// ASSERT(a != b)
#define ASSERT_NOT_EQUAL(a, b)           \
    ASSERT((a) != (b), ("values match"))

void print_int(int n);
void print_size_t(size_t n);
void print_str(const char *s);
void print_newline(void);
