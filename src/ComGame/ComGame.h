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
     * Provides the game score.
     * 
     * @param res the array on which the score will be stored.
     * The array is assumed to be of length 2.
     * 
     * @note This function returns nothing. It stores the score
     * in the array that is provided as an argument.
     */
    void getScore(int* res);

    /**
     * Resets the game.
     * 
     * It gives a new random seed using the system time,
     * resets the score, resets the turn counter and resets
     * the game state.
     */
    void resetGame();

    /**
     * Resets the game and changes the players to the ones provided.
     * 
     * @param player1 A pointer to the first player.
     * @param player2 A pointer to the second player.
     */
    void newPlayers(AbstractPlayer* player1, AbstractPlayer* player2);

    /**
     * Plays the game.
     * 
     * Initially calls the AbstractPlayer::initialise() function of both player
     * and then plays the game until it terminates.
     * 
     * @note This function does not return the score. The score can be obtained
     * by calling the getScore() function.
     * 
     * @see play_unsafe
     */
    void play();

    /**
     * Plays the game without checking the players' inputs.
     * 
     * Initially calls the `initialise` function of both player
     * and then plays the game until it terminates.
     * 
     * The function trusts that players give valid inputs.
     * It is faster than play() and it should be used during training. 
     *
     * @note This function does not return the score. The score can be obtained
     * by calling the getScore() function.
     * 
     * @see play
     */
    void play_unsafe();

    /**
     * The constructor of CompromiseGame.
     * 
     * @param player1   A pointer to the first player.
     * @param player2   A pointer to the second player.
     * @param newPips   The number of pips each player has to place each round.
     * @param len       The length of the game in rounds.
     * @param gameType  The type of the game, 0 = gamble, 1 = simple and 2 = complex. Its default value is 1.
     * @param noTies    If this is set to true, then the game does not stop when after `len` number of rounds
     *                  if the players tie. It continues until one of the players scores more than the others.
     *                  Its default value is false.
     * 
     * @note If `noTies` is set to true, then there is a chance that the game will enter an infinite loop. Use this option with caution.
     * 
     * 
     */
    CompromiseGame(AbstractPlayer* player1, AbstractPlayer* player2, int newPips, int len, int gameType = 1, bool noTies = false);

    /**
     * The destructor of CompromiseGame.
     */
    ~CompromiseGame();
};