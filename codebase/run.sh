rm -r build
cd ..
cmake -S codebase -B codebase/build
echo "CMake Successful"
cd codebase/build
make
echo "Make Successful"
./watertool
