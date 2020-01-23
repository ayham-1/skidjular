#!/bin/sh
 
mkdir build
cd build
conan install ..
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j9
cd ..
