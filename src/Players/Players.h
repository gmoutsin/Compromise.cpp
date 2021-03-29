#pragma once

#include "ComGameTypes.h"

class Player {
    public:
    void play(Position* res);

    void place(PlacementArray* res);
};

class RandomPlayer: public Player {};

class DeterminedPlayer: public Player {};

class GreedyPlayer: public Player {};

class SmartGreedyPlayer: public Player {};