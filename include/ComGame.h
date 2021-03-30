#pragma once

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <ctime>
#include <random>
#include "ComGameTypes.h"
#include "Players.h"

class CompromiseGame 
{
    public:
    Player* p1;
    Player* p2;
    GameState* state1;
    GameState* state2;
    GameState* disp1;
    GameState* disp2;
    Position* move1;
    Position* move2;
    PlacementArray* placement1;
    PlacementArray* placement2;
    int score1;
    int score2;
    int length;
    int turn;
    int newPips;
    bool noTies;
    int type;

    CompromiseGame(Player* player1, Player* player2, int newpips, int len, int gametype = 1, bool noties = true);
    
    ~CompromiseGame();

    void printMoves();

    void printState();

    void resetGame();

    void newPlayers(Player*, Player*);

    void prepareDisposable();

    void placePips();
    
    void placePips_unsafe();

    void getMoves();

    void getMoves_unsafe();

    void updateScore();

    void playRound();

    void playRound_unsafe();

    void play();

    void play_unsafe();
};