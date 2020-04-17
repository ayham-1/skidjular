#!/bin/sh

mkdir build
cd build
conan install .. --build=missing
cmake --config=Debug .. 
make -j9
cd ..
