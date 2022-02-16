CC=cc
CCARGS=-g0
SOURCES=string.c list.c heap.c build.c decode.c main.c

make: $(SOURCES)
	make deflate
	make inflate

deflate: $(SOURCES)
	mkdir -p ./target/bin
	$(CC) $(CCARGS) -o ./target/bin/deflate string.c list.c bit-buffer.c heap.c build.c decode.c main.c

inflate: $(SOURCES) 
	mkdir -p ./target/bin
	$(CC) $(CCARGS) -o ./target/bin/inflate string.c list.c decode.c inflate.c