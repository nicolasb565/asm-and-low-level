all: io.asm
	nasm -felf64 io.asm -o io.o
	ld -o io io.o
	chmod u+x io
	
.PHONY: clean
clean:
	rm io.o io
