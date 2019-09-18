#!/bin/sh
 
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
ninja -j8
cd ..
