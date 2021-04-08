#pragma once

#include "ComGameTypes.h"

/**
 * Abstract player class, every player class has to extend this one.
 *
 * Each player class has to implement the move() and place() functions.
 * The class also defines a default initialise() function.
 * 
 * @note This class declares a protected member `block` which is a
 * Position pointer but it is never initialised.
 */
class AbstractPlayer
{
    protected:
    Position* block;

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
    virtual void move(Position* res, GameState* myState, GameState* oppState, int myScore, int oppScore, int turn, int newPips) = 0;

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

/**
 * A player class which divides the pips equally between two positions.
 * 
 * This abstract class implements only the place() function.
 * Half of the pips are placed on one of the two placement positions, `pos1` and `pos2,
 * and the other half on the other.
 * 
 * The initialise() function sets the two placement positions and `block`
 * is such way that they all three do not have common coordinates.
 */
class AbstractOscillatingPlacer: public virtual AbstractPlayer
{
    protected:
    Position* pos1;
    Position* pos2;
    int flip;

    public:
    virtual void initialise(int type, int length, int newPips, bool noTies);
    virtual void place(PlacementArray* res, GameState* myState, GameState* oppState, int myScore, int oppScore, int turn, int newPips);
    AbstractOscillatingPlacer();
    ~AbstractOscillatingPlacer();
};

/**
 * A player class which chooses the same move every time.
 * 
 * This abstract class implements only the move() function.
 * The constructor sets the move by choosing one uniformely at random
 * and move() chooses it each time it is called.
 * 
 * The move is stored at the `block` member declared in the AbstractPlayer class.
 * 
 * @note This class does not provide an initialise() function and the move does not change
 * after the player has been created.
 */
class AbstractConstantMover: public virtual AbstractPlayer
{
    public:
    virtual void move(Position* res, GameState* myState, GameState* oppState, int myScore, int oppScore, int turn, int newPips);
    AbstractConstantMover();
    ~AbstractConstantMover();
};

/**
 * This player class inherits from AbstractOscillatingPlacer and AbstractConstantMover.
 */
class OscillatingPlayer: public AbstractConstantMover, public AbstractOscillatingPlacer {};

/**
 * A player class which places pips randomly.
 * 
 * This abstract class implements only the place() function.
 * For each pip it chooses a location uniformly at random and places it there.
 */
class AbstractRandomPlacer: public virtual AbstractPlayer
{
    public:
    
    /**
     * A function that provides random pip placement. 
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
 * A player class which choses a random move.
 * 
 * This abstract class implements only the move() function.
 * It chooses a move uniformly at random.
 */
class AbstractRandomMover: public virtual AbstractPlayer
{
    public:

    /**
     * A function that provides a random move. 
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
    virtual void move(Position* res, GameState* myState, GameState* oppState, int myScore, int oppScore, int turn, int newPips);
};

/**
 * This player class inherits from AbstractRandomPlacer and AbstractRandomMover.
 */
class RandomPlayer: public AbstractRandomMover, public AbstractRandomPlacer {};

/**
 * A class which before placing the pips, calls the move() functions and makes
 * sure that the pips are not placed on positions that would be blocked by move().
 */
class AbstractGreedyPlacer: public virtual AbstractPlayer
{
    public:

    /**
     * A function that provides pip placement. 
     * 
     * This function first calls the move() function and then it places the pips
     * randomly making sure that they wouldn't be excluded by the move.
     * 
     * For example if move() returns {0,0,0} then for each pip a position that does not contain 0,
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
};

/**
 * A class which chooses a move that will not block its best positions. 
 */
class AbstractMyopicMover: public virtual AbstractPlayer
{
    public:

    /**
     * A function that provides a move which does not block its best positions. 
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
    virtual void move(Position* res, GameState* myState, GameState* oppState, int myScore, int oppScore, int turn, int newPips);
};

/**
 * This player class inherits from AbstractGreedyPlacer and AbstractMyopicMover.
 */
class MyopicPlayer: public AbstractMyopicMover, public AbstractGreedyPlacer {};

/**
 * A class which chooses a move that will block its opponent best positions. 
 */
class AbstractGreedyMover: public virtual AbstractPlayer
{
    public:

    /**
     * A function that provides a move which blocks its opponent best positions. 
     * 
     * This function initially subracts the opponents pips from the player's pips for each position.
     * Then it calculates three sets of three sums.
     * 
     * - **Grid sums** Sums all numbers that are on the same grid.
     *    
     * - **Row sums** Sums all numbers that are on the same row on all grids.
     *    
     * - **Column sums** Sums all numbers that are on the same colunm on all grids.
     *    
     * After that chooses to block the grid, row and column that are most advantageous to its opponent.
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
    virtual void move(Position* res, GameState* myState, GameState* oppState, int myScore, int oppScore, int turn, int newPips);
};

/**
 * An improvement over AbstractGreedyMover.
 */
class AbstractSmartGreedyMover: public virtual AbstractPlayer
{
    public:

    /**
     * A function that provides a move which blocks its opponent best positions. 
     * 
     * This function initially subracts the opponents pips from the player's pips for each position.
     * Then it calculates three sets of three sums.
     * 
     * - **Grid sums** Sums all numbers that are on the same grid.
     *    
     * - **Row sums** Sums all numbers that are on the same row on all grids.
     *    
     * - **Column sums** Sums all numbers that are on the same colunm on all grids.
     *    
     * Then it choses the smallest sum and fixes that in the move, e.g. if the grid, row and column sums
     * are {-5,-1,6}, {10,0,-10} and {-3,-1,4} respectively, then it will choose the third row
     * and fix that in the move.
     * 
     * After that it zeros all the position that will be blocked with the chosen sum, e.g in the example
     * above it will set to 0 every position on any third row.
     * 
     * After that it recalculates the sums and repeats the process until a unique move is found.
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
    virtual void move(Position* res, GameState* myState, GameState* oppState, int myScore, int oppScore, int turn, int newPips);
};

/**
 * This player class inherits from AbstractGreedyPlacer and AbstractGreedyMover.
 */
class GreedyPlayer: public AbstractGreedyMover, public AbstractGreedyPlacer {};

/**
 * This player class inherits from AbstractGreedyPlacer and AbstractSmartGreedyMover.
 */
class SmartGreedyPlayer: public AbstractSmartGreedyMover, public AbstractGreedyPlacer {};