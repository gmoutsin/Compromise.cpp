cmake -G "MinGW Makefiles" -S . -B ./build/
cd ./build/
make
cmake --install .
cd ..
del /Q/S build > NUL