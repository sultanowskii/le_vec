# le_vec

Your basic C vector.

## Install

```bash
# Get le_vec on your machine
git clone github.com/sultanowskii/le_vec
cd le_vec
# Build
make
# Install globally
# (you might want to run this one with sudo)
make install

# (Optional) Verify the library is installed properly on your system and accessible globally
make example
```

Or just copy+paste [src/](src/) right into your code.

## Usage

```c
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
```
