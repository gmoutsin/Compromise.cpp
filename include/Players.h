#pragma once

#include "ComGameTypes.h"

class AbstractPlayer
{
    public:
    virtual void play(Position*, GameState*, GameState*, int, int, int, int, int) = 0;

    virtual void place(PlacementArray*, GameState*, GameState*, int, int, int, int, int) = 0;
};


class RandomPlayer: public AbstractPlayer
{
    public:
    virtual void play(Position*, GameState*, GameState*, int, int, int, int, int);

    virtual void place(PlacementArray*, GameState*, GameState*, int, int, int, int, int);
};

class DeterminedPlayer: public RandomPlayer
{  
    private:
    int c1[2] = {-1,-1};
    int c2[2] = {-1,-1};
    int c3[2] = {-1,-1};

    public:
    virtual void play(Position*, GameState*, GameState*, int, int, int, int, int);
};

class GreedyPlayer: public RandomPlayer
{
    private:
    int c1[3];
    int c2[3];
    int c3[3];

    public:
    virtual void play(Position*, GameState*, GameState*, int, int, int, int, int);
};

class SmartGreedyPlayer: public AbstractPlayer {};