# problem_hwe

## Build
```bash
cmake -DCMAKE_BUILD_TYPE=Release -S . -B build && cmake --build build 
```

## Test
```bash
ctest --test-dir build/
```

## Run
```bash
./build/sieve_app
```