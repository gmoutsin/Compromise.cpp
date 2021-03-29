#!/bin/sh
cmake -G "MinGW Makefiles" -S . -B ./build/
cd ./build
make
cmake --install .
cd ..
rm -rf ./build