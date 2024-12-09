# Citation Generator
A fast C++ CLI utility to generate citations given a search string

## Build From Source
```bash
git submodule update --init --recursive
mkdir -p build && cd build
cmake ../
make -j$(nproc)
sudo make install
```

## Notes

Output if verbose

Format data as specified (Plaintext || bib)
