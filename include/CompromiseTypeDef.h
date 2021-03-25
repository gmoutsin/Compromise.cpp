#pragma once

#include <iostream>
#include <array>
#include <vector>

using Position = std::array<std::int8_t, 3>;
using PlacementArray = std::vector<Position>;

inline bool validPosisionQ(Position p);

inline bool invalidPosisionQ(Position p);


class GameState 
{
    friend class CompromiseGame;

    protected:
    std::array<int, 27> data;

    inline int uget(int, int, int);

    inline void uset(int, int, int, int) ;

    inline void set(Position, int);

    inline void inc(Position);

    inline void inc(int, int, int) ;

    inline void set(int, int, int, int) ;

    inline void set(int, int);

    public:
    GameState();

    inline int get(int, int, int);

    inline int get(int);
};