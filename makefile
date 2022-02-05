CCARGS=-g3

huffman: list.c heap.c build.c main.c
	mkdir -p ./target/bin
	cc ${CCARGS} -o ./target/bin/huffman list.c bit-buffer.c heap.c build.c main.c
