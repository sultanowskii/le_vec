#include <stdio.h>
#include <stddef.h>

#include "tests/common.h"

void print_int(int n) {
    printf("%d", n);
}

void print_size_t(size_t n) {
    printf("%zu", n);
}

void print_str(const char *s) {
    printf("%s", s);
}

void print_newline(void) {
    printf("\n");
}