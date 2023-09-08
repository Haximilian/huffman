This repository implements the [huffman compression](https://en.wikipedia.org/wiki/Huffman_coding) algorithm.

I wrote it in `c`. 

Except for `io` headers, It doesn't depend on any external libraries.

I used [American Fuzzy Lop](https://en.wikipedia.org/wiki/American_fuzzy_lop_(fuzzer)) to fuzz the implementation and find bugs.

The algorithm can compress a copy of Shakespeare's Macbeth by a ratio of about `~0.686` e.g. the original file is `105202` bytes while the compressed result is `72273` bytes.

**Build**
```
make
```

**Compress**
```
./target/bin/deflate ./examples/macbeth ./compressed-result
```

**Inflate**
```
./target/bin/inflate ./compressed-result > ./uncompressed-result
```

![](/examples/example.png "example")

<img width="2029" alt="Screen Shot 2023-09-07 at 11 50 35 PM" src="https://github.com/Haximilian/huffman/assets/47073524/f706fe42-3736-402a-847b-752b3fd8b597">
