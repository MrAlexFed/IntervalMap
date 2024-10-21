# Interval map implementation project


### Requirements 

- g++
- cmake
- ninja

### Building

Execute commands from source dir to build library and tests:

````
cmake cmake -G Ninja -B build -DCMAKE_BUILD_TYPE=Release
cd build
ninja -f build.ninja
````

### Testing

To run tests execute command from build dir
````
ctest --test-dir test
````
