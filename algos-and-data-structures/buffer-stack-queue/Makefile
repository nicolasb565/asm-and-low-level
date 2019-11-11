all: buffer.c buffer.h stack.c stack.h queue.c queue.h
	gcc -g -O0 -Wall -Wextra buffer.c -o buffer
	gcc -g -O0 -Wall -Wextra buffer.c stack.c -o stack
	gcc -g -O0 -Wall -Wextra buffer.c queue.c -o queue
	
.PHONY: clean
clean:
	rm buffer stack queue
