# cmake -G "MinGW Makefiles" -S . -B .\build\

cmake_minimum_required(VERSION 3.20.0)

project(CompromiseCPP
    VERSION 0.1
    DESCRIPTION "Description"
    LANGUAGES CXX
)

add_subdirectory(include)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES src/main.cpps)

add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_directories(${PROJECT_NAME} PUBLIC build/include)

target_link_libraries(${PROJECT_NAME}
    PUBLIC ComGameTypes
    PUBLIC ComGame
    PUBLIC Players
)


