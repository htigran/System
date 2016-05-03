
#!/usr/bin/env sh
set -evx
env | sort

mkdir build || true
mkdir build/$TARGET || true
cd build/$TARGET
cmake -DCMAKE_CXX_FLAGS=$CXX_FLAGS \
      ../../$TARGET
make
make test
