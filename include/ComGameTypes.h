#pragma once

#include <iostream>
#include <array>
#include <vector>

using Position = std::array<std::int8_t, 3>;
using PlacementArray = std::vector<Position>;

bool validPosisionQ(Position p);

bool invalidPosisionQ(Position p);


class GameState 
{
    friend class CompromiseGame;

    protected:
    std::array<int, 27> data;

    int uget(int, int, int);

    void uset(int, int, int, int) ;

    void set(Position, int);

    void inc(Position);

    void inc(int, int, int) ;

    void set(int, int, int, int) ;

    void set(int, int);

    public:
    GameState();

    int get(int, int, int);

    int get(int);
};