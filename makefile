# CC=./AFL/afl-gcc
CC=cc
CCARGS=-g3
SOURCES=string.c list.c heap.c build.c decode.c main.c

SHELL := /bin/bash

make: $(SOURCES)
	pushd ./AFL >/dev/null && make && popd >/dev/null
	make deflate
	make inflate

fuzz-deflate:
	make
	export AFL_SKIP_CPUFREQ=""; ./AFL/afl-fuzz -i examples/afl -o findings_dir -- ./target/bin/deflate @@

deflate: $(SOURCES)
	mkdir -p ./target/bin
	$(CC) $(CCARGS) -o ./target/bin/deflate string.c list.c bit-buffer.c heap.c build.c decode.c main.c

inflate: $(SOURCES) 
	mkdir -p ./target/bin
	$(CC) $(CCARGS) -o ./target/bin/inflate string.c list.c decode.c inflate.c
