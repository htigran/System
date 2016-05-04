
#!/usr/bin/env sh
set -evx
env | sort

cd /usr/src/gtest && sudo cmake . && sudo cmake --build . && sudo mv libg* /usr/local/lib/ ; cd -

mkdir build || true
cd build
cmake -DCMAKE_CXX_FLAGS=$CXX_FLAGS \
      ../
make
make test
