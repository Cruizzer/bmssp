# bmssp

To build the main exe:
cmake -S . -B build
cmake --build build --target bmssp
./build/bmssp 5000 20

To run the unit tests:
cmake --build build --target unit_tests
ctest --output-on-failure -C Debug -j1