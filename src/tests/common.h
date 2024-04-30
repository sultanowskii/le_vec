#pragma once

#include <stddef.h>

static int ERR_CNTR = 0;
static int ASSERT_CNTR = 0;

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

#define ASSERT_STRINGS_EQUAL(a, b)                     \
    ASSERT(strcmp((a), (b)) == 0, ("strings differ"))

#define ASSERT_EQUAL(a, b)                 \
    ASSERT((a) == (b), ("values differ"))

#define ASSERT_NOT_EQUAL(a, b)           \
    ASSERT((a) != (b), ("values match"))

void print_int(int n);
void print_size_t(size_t n);
void print_str(const char *s);
void print_newline(void);