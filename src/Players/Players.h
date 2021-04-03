#pragma once

#include "ComGameTypes.h"

/**
 * Abstract player class, every player class has to extend this one.
 *
 * Each player class has to implement the play() and place() functions.
 * The class also defines a default initialise() function.
 */
class AbstractPlayer
{
    public:

    /**
     * This is a pure virtual function of AbstractPlayer.
     * 
     * This functions accepts the game's state and provides the player's move. 
     * 
     * @note This function does not return anything. The player's move is stored in the first argument.
     * 
     * @param res The player's move should me stored here.
     * @param myState The position of the player's pips.
     * @param oppState The position of the opponent's pips.
     * @param myScore The player's score.
     * @param oppScore The opponents score.
     * @param turn The turn number.
     * @param newPips The number of pips to be placed each turn.
     */
    virtual void play(Position* res, GameState* myState, GameState* oppState, int myScore, int oppScore, int turn, int newPips) = 0;

    /**
     * This is a pure virtual function of AbstractPlayer.
     * 
     * This function accepts the game's state and provides the player's pip placement. 
     * 
     * @note This function does not return anything. The player's pip placement is stored in the first argument.
     * 
     * @param res The player's move should me stored here. This is a Position array of length `newPips`.
     * @param myState The position of the player's pips.
     * @param oppState The position of the opponent's pips.
     * @param myScore The player's score.
     * @param oppScore The opponents score.
     * @param turn The turn number.
     * @param newPips The number of pips to be placed each turn.
     */
    virtual void place(PlacementArray* res, GameState* myState, GameState* oppState, int myScore, int oppScore, int turn, int newPips) = 0;

    /**
     * This function can be used to initialise the player.
     * 
     * This function is called everytime a game starts. By default it does nothing.
     * 
     * @param type The game's type, see CompromiseGame::CompromiseGame().
     * @param length The number of turns the game will last.
     * @param newPips The number of pips to be placed each turn.
     * @param noTies If this is set to true, the game does not end if there is a tie.
     */
    virtual void initialise(int type, int length, int newPips, bool noTies){};
};

class OscillatingPlayer: public AbstractPlayer
{
    private:
    Position* pos1;
    Position* pos2;
    Position* move;
    int flip;

    public:
    virtual void play(Position* res, GameState* myState, GameState* oppState, int myScore, int oppScore, int turn, int newPips);
    virtual void place(PlacementArray* res, GameState* myState, GameState* oppState, int myScore, int oppScore, int turn, int newPips);
    virtual void initialise(int type, int length, int newPips, bool noTies);
    OscillatingPlayer();
    ~OscillatingPlayer();
};

/**
 * This player plays randomly.
 *
 * Both play() and place() functions of the class give random results.
 */
class RandomPlayer: public AbstractPlayer
{
    public:

    /**
     * This function provides a random move. 
     * 
     * @note This function does not return anything. The player's move is stored in the first argument.
     * 
     * @note This function ignores its arguments.
     * 
     * @param res The player's move should me stored here.
     * @param myState The position of the player's pips.
     * @param oppState The position of the opponent's pips.
     * @param myScore The player's score.
     * @param oppScore The opponents score.
     * @param turn The turn number.
     * @param newPips The number of pips to be placed each turn.
     */
    virtual void play(Position* res, GameState* myState, GameState* oppState, int myScore, int oppScore, int turn, int newPips);

    /**
     * This function provides random pip placement. 
     * 
     * @note This function does not return anything. The player's pip placement is stored in the first argument.
     * 
     * @note This function ignores its arguments.
     * 
     * @param res The player's move should me stored here. This is a Position array of length `newPips`.
     * @param myState The position of the player's pips.
     * @param oppState The position of the opponent's pips.
     * @param myScore The player's score.
     * @param oppScore The opponents score.
     * @param turn The turn number.
     * @param newPips The number of pips to be placed each turn.
     */
    virtual void place(PlacementArray* res, GameState* myState, GameState* oppState, int myScore, int oppScore, int turn, int newPips);
};

/**
 * This player makes sure that it doesn't exclude its best positions.
 */
class MyopicPlayer: public AbstractPlayer
{
    private:
    Position* pos;
    int* t1;
    int* t2;
    int* t3;

    public:

    /**
     * This function provides a move. 
     * 
     * This function initially subracts the opponents pips from the player's pips for each position.
     * Then it finds the best position for the player and excludes
     * its coordinates from the move. For example if the best position is {0,0,0} then the move cannot contain 0.
     * 
     * After that it finds the second best position and excludes its coordinates from the move.
     * For example if the second best position is {1,1,0} then the first two coordinates of the
     * move cannot contain 0 or 1, hence they have to be 2. The second can be 1 or 2.
     * 
     * It continues in that manner until all coordinates have been determined. 
     * 
     * @note This function does not return anything. The player's move is stored in the first argument.
     * 
     * @note This function ignores its `myScore` `oppScore` `turn` `newPips` arguments.
     * 
     * @param res The player's move should me stored here.
     * @param myState The position of the player's pips.
     * @param oppState The position of the opponent's pips.
     * @param myScore The player's score.
     * @param oppScore The opponents score.
     * @param turn The turn number.
     * @param newPips The number of pips to be placed each turn.
     */
    virtual void play(Position* res, GameState* myState, GameState* oppState, int myScore, int oppScore, int turn, int newPips);

    /**
     * This function provides pip placement. 
     * 
     * This function first calls the play() function and then it places the pips
     * randomly making sure that they wouldn't be excluded by the move.
     * 
     * For example if play() returns {0,0,0} then for each pip a position that does not contain 0,
     * i.e {1,1,1}, {2,1,1}, {1,2,1}, {1,1,2}, {2,2,1}, {2,1,2}, {1,2,2}, {2,2,2},
     * is chosen uniformely at random.
     * 
     * @note This function does not return anything. The player's pip placement is stored in the first argument.
     * 
     * @note This function ignores its `myScore` `oppScore` `turn` `newPips` arguments.
     * 
     * @param res The player's move should me stored here. This is a Position array of length newPips.
     * @param myState The position of the player's pips.
     * @param oppState The position of the opponent's pips.
     * @param myScore The player's score.
     * @param oppScore The opponents score.
     * @param turn The turn number.
     * @param newPips The number of pips to be placed each turn.
     */
    virtual void place(PlacementArray* res, GameState* myState, GameState* oppState, int myScore, int oppScore, int turn, int newPips);
    MyopicPlayer();
    ~MyopicPlayer();
};

class GreedyPlayer: public MyopicPlayer
{
    public:
    virtual void play(Position* res, GameState* myState, GameState* oppState, int myScore, int oppScore, int turn, int newPips);
};

class SmartGreedyPlayer: public MyopicPlayer
{
    public:
    virtual void play(Position* res, GameState* myState, GameState* oppState, int myScore, int oppScore, int turn, int newPips);
};