

project (CompromiseCPP)

include_directories(include)

set(SOURCES src/main.cpp
    src/Players.cpp
    src/CompromiseGame.cpp
    src/CompromiseTypeDef.cpp
)

add_executable(/bin/main.exe ${SOURCES})


