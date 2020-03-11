#!/bin/sh

mkdir build
cd build
conan install .. --build missing
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j9
cd ..
