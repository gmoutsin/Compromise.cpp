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
    public:
    std::array<int, 27> data;
    int uget(int i, int j, int k);
    void uset(int i, int j, int k, int v) ;
    void set(Position, int);
    void inc(Position);
    void inc(int i, int j, int k) ;
    void set(int i, int j, int k, int v) ;
    void set(int i, int v);
    int get(int i, int j, int k);
    int get(int i);
    void minus(GameState* s);
    bool operator==(GameState s);
    void copy(GameState* s);
    GameState();
};

class InnerGameState: protected GameState
{
    friend class CompromiseGame;
};