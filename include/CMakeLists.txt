cmake_minimum_required(VERSION 3.20.0)

add_library(ComGameTypes CompromiseTypeDef.cpp)

add_library(Players Players.cpp)

target_link_libraries(Players PUBLIC ComGameTypes)

add_library(ComGame CompromiseGame.cpp)

target_link_libraries(ComGame PUBLIC ComGameTypes PUBLIC Players)