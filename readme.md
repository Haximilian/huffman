**Run:**
```
make
./target/bin/deflate ./examples/macbeth ./compressed-result
./target/bin/inflate ./compressed-result > ./uncompressed-result
vim ./compressed-result ./uncompressed-result
```
![](/examples/example.png "example")
