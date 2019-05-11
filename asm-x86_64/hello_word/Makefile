hello_world: hello.asm
	nasm -felf64 hello.asm -o hello.o
	ld -o hello hello.o
	chmod u+x hello
	
.PHONY: clean
clean:
	rm hello.o hello
