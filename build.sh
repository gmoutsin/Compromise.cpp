#!/bin/sh
cmake -S . -B ./build/
cd ./build
make
cmake --install .
cd ..
rm -rf ./build