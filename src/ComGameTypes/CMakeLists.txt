add_library(ComGameTypes STATIC ComGameTypes.cpp)

target_include_directories(ComGameTypes
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)
install(TARGETS ComGameTypes
    DESTINATION ${PROJECT_SOURCE_DIR}/lib
)
install(FILES ComGameTypes.h
    DESTINATION ${PROJECT_SOURCE_DIR}/include
)