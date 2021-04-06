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
    void prepareDisposableStates();
    void placePips();
    void placePips_unsafe();
    void getMoves();
    void getMoves_unsafe();
    void updateScore();
    void playRound();
    void playRound_unsafe();

    public:

    /**
     * Provides the game score
     * 
     * @param res the array on which the score will be stored.
     * The array is assumed to be of length 2.
     * 
     * @note This function does not return anything. It store the score
     * in the array that is provided as an argument.
     */
    void getScore(int* res);

    /**
     * Resets the game
     * 
     * It gives a new random seed using the system time,
     * resets the score, resets the turn counter and resets
     * the game state.
     */
    void resetGame();
    void newPlayers(AbstractPlayer* player1, AbstractPlayer* player2);
    void play();
    void play_unsafe();
    CompromiseGame(AbstractPlayer* player1, AbstractPlayer* player2, int newpips, int len, int gametype = 1, bool noties = true);
    ~CompromiseGame();
};