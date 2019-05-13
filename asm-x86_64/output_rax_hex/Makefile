hello_world: output_rax_hex.asm
	nasm -felf64 output_rax_hex.asm -o output_rax_hex.o
	ld -o output_rax_hex output_rax_hex.o
	chmod u+x output_rax_hex
	
.PHONY: clean
clean:
	rm output_rax_hex.o output_rax_hex
