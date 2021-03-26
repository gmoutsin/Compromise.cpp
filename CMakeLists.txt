# cmake -G "MinGW Makefiles" .

cmake_minimum_required(VERSION 3.20.0)

project(CompromiseCPP
        VERSION 0.1
        DESCRIPTION "Description"
        LANGUAGES CXX
)

add_subdirectory(include)

set (CMAKE_CXX_STANDARD 14)

set(SOURCES src/main.cpps)

add_executable(bin src/main.cpp)

target_include_directories(bin PUBLIC include)

target_link_directories(bin PRIVATE include)

target_link_libraries(bin
                        PRIVATE ComGameTypes
                        PRIVATE ComGame
                        PRIVATE Players
)


