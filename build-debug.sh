#!/bin/sh
 
mkdir build
cd build
cmake -GNinja -DCMAKE_BUILD_TYPE=Debug ..
ninja -j8
cd ..
