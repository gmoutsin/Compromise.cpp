add_library(Players STATIC Players.cpp)
target_link_libraries(Players PUBLIC ComGameTypes)

target_include_directories(Players
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)
install(TARGETS Players
    DESTINATION ${PROJECT_SOURCE_DIR}/lib
)
install(FILES Players.h
    DESTINATION ${PROJECT_SOURCE_DIR}/include
)