#include <stdio.h>
#include <stddef.h>
#include <le_vec.h>

int main() {
    // Create the le_vec
    struct le_vec *v = le_vec_init();

    // Push some values
    le_vec_push_back(v, 123);
    le_vec_push_back(v, 456);
    le_vec_push_back(v, 789);

    // Change value at index 1
    le_vec_set_at(v, 1, 1337);

    // Print the vector values
    for (size_t i = 0; i < le_vec_get_length(v); i++) {
        printf("%d ", le_vec_get_at(v, i));
    }
    printf("\n");

    // Don't forget to clean up!
    le_vec_destroy(v);

    return 0;
}

