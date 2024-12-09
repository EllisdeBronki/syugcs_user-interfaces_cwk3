rm -r build
cd ..
cmake -S src -B src/build
echo "CMake Successful"
cd src/build
make
echo "Make Successful"
./watertool