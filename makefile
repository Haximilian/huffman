CCARGS=-g3

huffman: list.c heap.c build.c decode.c main.c
	mkdir -p ./target/bin
	cc ${CCARGS} -o ./target/bin/huffman string.c list.c bit-buffer.c heap.c build.c decode.c main.c

inflate-huffman: list.c heap.c build.c decode.c main.c
	mkdir -p ./target/bin
	cc ${CCARGS} -o ./target/bin/inflate string.c list.c decode.c inflate.c