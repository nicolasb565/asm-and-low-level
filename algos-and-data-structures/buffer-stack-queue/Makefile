all: buffer.c buffer.h stack.c stack.h
	gcc -g -O0 -Wall -Wextra buffer.c -o buffer
	gcc -g -O0 -Wall -Wextra buffer.c stack.c -o stack
	
.PHONY: clean
clean:
	rm buffer stack
