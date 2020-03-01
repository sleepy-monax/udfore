PROJECT=udfore

TESTS := $(wildcard $(PROJECT)/tests/*.test.c)
SOURCES := $(filter-out $(wildcard $(PROJECT)/tests/*.test.c), $(wildcard $(PROJECT)/*/*.c) $(wildcard $(PROJECT)/*/*/*.c))
OBJECTS := $(SOURCES:.c=.o)

CC := gcc
LDFLAGS := -lm
CFLAGS := -g \
		 -std=c11 \
		 -MD \
		 -I. \
		 -Wall \
		 -Wextra \
		 -Werror \
		 -fsanitize=address \
		 -fsanitize=undefined \
		 -D_XOPEN_SOURCE=500

.PHONY: all clean test

all: $(PROJECT).out

clean:
	rm -f $(OBJECTS) $(SOURCES:.c=.d) $(PROJECT).out

run: $(PROJECT).out
	./$(PROJECT).out

test: $(TESTS:.c=.run)

$(PROJECT).out: $(PROJECT)/main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(PROJECT)/tests/%.test.run: $(PROJECT)/tests/%.test.out
	$^

$(PROJECT)/tests/%.test.out: $(PROJECT)/tests/%.test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)


-include $(SOURCES:.c=.d)
