**Run:**
```
make
./target/bin/deflate examples/example ./compressed-result
./target/bin/inflate ./results > ./uncompressed-result
vim compressed-result uncompressed-result
```
![](/examples/example.png "example")