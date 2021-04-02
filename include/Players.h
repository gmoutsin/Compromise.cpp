#pragma once

#include "ComGameTypes.h"

class AbstractPlayer
{
    public:
    virtual void play(Position*, GameState*, GameState*, int, int, int, int) = 0;
    virtual void place(PlacementArray*, GameState*, GameState*, int, int, int, int) = 0;
    virtual void initialise(int, int, int, bool){};
};

class OscillatingPlayer: public AbstractPlayer
{
    private:
    Position* pos1;
    Position* pos2;
    Position* move;
    int flip;

    public:
    virtual void play(Position*, GameState*, GameState*, int, int, int, int);
    virtual void place(PlacementArray*, GameState*, GameState*, int, int, int, int);
    virtual void initialise(int, int, int, bool);
    OscillatingPlayer();
    ~OscillatingPlayer();
};

class RandomPlayer: public AbstractPlayer
{
    public:
    virtual void play(Position*, GameState*, GameState*, int, int, int, int);
    virtual void place(PlacementArray*, GameState*, GameState*, int, int, int, int);
};

class MyopicPlayer: public AbstractPlayer
{
    private:
    Position* pos;
    int* t1;
    int* t2;
    int* t3;

    public:
    virtual void play(Position*, GameState*, GameState*, int, int, int, int);
    virtual void place(PlacementArray*, GameState*, GameState*, int, int, int, int);
    MyopicPlayer();
    ~MyopicPlayer();
};

class GreedyPlayer: public MyopicPlayer
{
    public:
    virtual void play(Position*, GameState*, GameState*, int, int, int, int);
};

class SmartGreedyPlayer: public MyopicPlayer
{
    public:
    virtual void play(Position*, GameState*, GameState*, int, int, int, int);
};