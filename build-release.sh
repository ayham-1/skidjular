#!/bin/sh

mkdir build
cd build
cmake -GNinja -DCMAKE_BUILD_TYPE=Release ..
ninja -j8
cd ..
