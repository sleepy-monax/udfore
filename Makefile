UDFORE_RUNTIME_MAIN=runtime/main.c

udfore: $(UDFORE_RUNTIME_MAIN)
	$(CC) -std=gnu11 -Wall -Wextra -Werror $^ -o $@

.PHONY: udfore

test: udfore
	./udfore samples/HelloWorld.ud 

clean:
	rm udfore