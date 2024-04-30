CFLAGS        = -fPIC
CFLAGS_DEBUG  = -g -Wall -Wextra -fPIC
LDFLAGS       = -shared
INCLUDES      = -Isrc -L.

NAME          = le-vec
SRCS          = $(wildcard src/*.c)
0BJS          = $(SRCS:.c=.o)
TARGET        = lib$(NAME).so

HEADER_NAME   = le_vec
HEADER_NAME_H = $(HEADER_NAME).h

TEST_NAME     = test
TEST_SRCS     = $(wildcard src/tests/*.c)
TEST_0BJS     = $(TEST_SRCS:.c=.o)
TEST_EXE      = $(TEST_NAME).elf

EXAMPLE_NAME  = example
EXAMPLE_SRCS  = $(EXAMPLE_NAME).c
EXAMPLE_OBJS  = $(EXAMPLE_NAME).o
EXAMPLE_EXE   = $(EXAMPLE_NAME).elf

.PHONY: default
.PHONY: clean
.PHONY: test
.PHONY: test-shared
.PHONY: install

default: $(TARGET)

clean:
	rm -f $(TARGET) *.o src/*.o src/tests/*.o $(TEST_EXE) $(EXAMPLE_EXE)

$(TARGET): $(0BJS)
	$(CC) $(INCLUDES) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $^

test: $(TEST_0BJS) $(0BJS)
	$(CC) $(INCLUDES) $(CFLAGS_DEBUG) -o $(TEST_EXE) $^
	./$(TEST_EXE)

test-shared: src/tests/test.o src/tests/common.o $(TARGET)
	$(CC) $(INCLUDES) $(CFLAGS_DEBUG) -l$(NAME) -o $(TEST_EXE) $^
	LD_LIBRARY_PATH=. ./$(TEST_EXE)

example: $(EXAMPLE_OBJS)
	$(CC) $(INCLUDES) $(CFLAGS_DEBUG) -l$(NAME) -o $(EXAMPLE_EXE) $^
	./$(EXAMPLE_EXE)

# using some automatic variables, which is pretty convenient
%.o: %.c
	$(CC) $(INCLUDES) $(CFLAGS) -c -o $@ $<

install:
	install -m 755 $(TARGET) /usr/local/lib/
	ldconfig /usr/local/lib/
	cp src/$(HEADER_NAME_H) /usr/local/include/$(HEADER_NAME)
