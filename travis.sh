
#!/usr/bin/env sh
set -evx
env | sort

# crete build folder
mkdir build || true
cd build

# compile googletest
mkdir gtest || true
cd gtest 
cmake ../../external/googletest/googletest
cmake --build .
sudo cmake --build . --target install
cd ..

# compile and run our system
cmake -DCMAKE_CXX_FLAGS=$CXX_FLAGS ../
make
make test
