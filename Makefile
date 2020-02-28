PROJECT=udfore

TESTS := $(wildcard $(PROJECT)/tests/*.test.c)
SOURCES := $(filter-out $(wildcard $(PROJECT)/tests/*.test.c), $(wildcard $(PROJECT)/*/*.c))
OBJECTS := $(SOURCES:.c=.o)

CC = gcc
LDFLAGS = -lm
CFLAGS = -g \
		 -std=c11 \
		 -MD \
		 -I. \
		 -Wall \
		 -Wextra \
		 -Werror \
		 -fsanitize=address \
		 -fsanitize=undefined

.PHONY: all clean test

all: $(PROJECT).out

clean:
	rm -f $(OBJECTS) $(SOURCES:.c=.d) $(PROJECT).out

run: $(PROJECT).out
	./$(PROJECT).out

$(PROJECT).out: $(PROJECT)/tests/main.c $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(PROJECT)/tests/Lexer.test.out: $(PROJECT)/tests/Lexer.test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)


-include $(SOURCES:.c=.d)
