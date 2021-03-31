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
    private:
    AbstractPlayer* p1;
    AbstractPlayer* p2;
    InnerGameState* state1;
    InnerGameState* state2;
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

    void printMoves();
    void printState();
    void prepareDisposable();
    void placePips();
    void placePips_unsafe();
    void getMoves();
    void getMoves_unsafe();
    void updateScore();
    void playRound();
    void playRound_unsafe();

    public:
    void getScore(int*);
    void resetGame();
    void newPlayers(AbstractPlayer*, AbstractPlayer*);
    void play();
    void play_unsafe();
    CompromiseGame(AbstractPlayer* player1, AbstractPlayer* player2, int newpips, int len, int gametype = 1, bool noties = true);
    ~CompromiseGame();
};