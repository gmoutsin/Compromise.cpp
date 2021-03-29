add_library(ComGame STATIC ComGame.cpp)
target_link_libraries(ComGame PUBLIC ComGameTypes Players)

target_include_directories(ComGame
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)
install(TARGETS ComGame
    DESTINATION ${PROJECT_SOURCE_DIR}/lib
)
install(FILES ComGame.h
    DESTINATION ${PROJECT_SOURCE_DIR}/include
)