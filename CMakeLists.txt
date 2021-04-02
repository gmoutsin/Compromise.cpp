cmake_minimum_required(VERSION 3.20.0)

project(CompromiseCPP
    VERSION 0.1
    DESCRIPTION "Description"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

# message(${CMAKE_CXX_FLAGS_RELEASE})

add_subdirectory("${PROJECT_SOURCE_DIR}/src/ComGameTypes")
list(APPEND LIBS_NEEDED ComGameTypes)

add_subdirectory("${PROJECT_SOURCE_DIR}/src/Players")
list(APPEND LIBS_NEEDED Players)

add_subdirectory("${PROJECT_SOURCE_DIR}/src/ComGame")
list(APPEND LIBS_NEEDED ComGame)

add_executable(cg "${PROJECT_SOURCE_DIR}/src/main.cpp")

target_link_libraries(cg PUBLIC ${LIBS_NEEDED})

install(TARGETS cg DESTINATION ${PROJECT_SOURCE_DIR}/bin)