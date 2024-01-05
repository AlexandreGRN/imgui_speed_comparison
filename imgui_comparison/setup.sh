mkdir build
cd build
conan install ../conanfile.txt --build=missing
cmake ..
cmake --build .
