mkdir -p build && cd build

cmake .. -DBUILD_TESTING=ON
cmake --build .

ctest --output-on-failure -V
