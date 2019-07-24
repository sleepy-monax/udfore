UDFORE_MACHINE_SOURCE=${wildcard Machine/*.c}

udfore: $(UDFORE_MACHINE_SOURCE)
	$(CC) -Wall -Wextra $^ -o $@

test: udfore
	./udfore Exemples/FizzBuzz.ud 

clean:
	rm udfore