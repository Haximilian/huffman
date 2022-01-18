huffman: list.c heap.c build.c main.c
	mkdir -p ./target/bin
	cc -o ./target/bin/huffman list.c heap.c build.c main.c
