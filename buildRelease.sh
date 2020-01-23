#!/bin/sh

mkdir build
cd build
conan install ..
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j9
cd ..
