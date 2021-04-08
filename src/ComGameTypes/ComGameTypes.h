#pragma once

#include <iostream>
#include <array>
#include <vector>

/**
 * Position is a different name for std::array<std::int8_t, 3>. 
 * It is used to define a position on the game board.
 */
using Position = std::array<std::int8_t, 3>;

/**
 * PlacementArray is a different name for std::vector<Position>.
 */
using PlacementArray = std::vector<Position>;

/**
 * This function returns true if the position is valid, i.e. all coordinates
 * are between 0 and 2, and returns false otherwise.
 * 
 * @param p the Position to be checked.
 * 
 * @see invalidPosisionQ
 */
bool validPosisionQ(Position p);

/**
 * This function returns false if the position is valid, i.e. all coordinates
 * are between 0 and 2, and returns true otherwise.
 * 
 * @param p the Position to be checked.
 * 
 * @see validPosisionQ
 */
bool invalidPosisionQ(Position p);

/**
 * This function changes the coordinates of a Position to random ones.
 * 
 * @param p a pointer to the Position that needs to be changed to random.
 */
void random(Position* p);

/**
 * This is a wrapper class for std::array<int, 27> data which is used
 * to store the game state for a player.
 * 
 * All the accessor functions that take 3 coordinates, i,j,k, access the element
 * 9*i+3*j+k of the array.
 */
class GameState 
{
    public:

    /**
     * The array which holds the data.
     */
    std::array<int, 27> data;
    
    /**
     * Unsafe get, it does not check bounds.
     * 
     * @param i the first coordinate
     * @param j the second coordinate
     * @param k the third coordinates
     * 
     * @note There is not unsafe get that accepts only integer as index
     * because the container array is public and can be accessed directly.
     * 
     * @see get(int,int,int) get(Position)
     */
    int uget(int i, int j, int k);

    /**
     * Unsafe set, it does not check bounds.
     * 
     * @param i the first coordinate
     * @param j the second coordinate
     * @param k the third coordinates
     * @param v the value to be set
     * 
     * @note There is not unsafe set that accepts only integer as index
     * because the container array is public and can be accessed directly.
     * 
     * @see set(int,int,int,int) set(Position,int)
     */
    void uset(int i, int j, int k, int v);

    /**
     * This set function accepts a position as an argument.
     * 
     * @param p the Position to be set to the value
     * @param v the value to be set
     * 
     * @note The function assumes that the Position is valid and does not check bounds.
     * 
     * @see set(int,int,int,int) uset(int,int,int,int)
     */
    void set(Position p, int v);

    /**
     * This get function accepts a position as an argument.
     * 
     * @param p the Position to be returned
     * 
     * @note The function assumes that the Position is valid and does not check bounds.
     * 
     * @see get(int,int,int) uget(int,int,int)
     */
    int get(Position p);

    /**
     * Increases the value at Position by one.
     * 
     * @param p the Position to be increased
     * 
     * @note The function assumes that the Position is valid and does not check bounds.
     * 
     * @see inc(int,int,int)
     */
    void inc(Position p);

    /**
     * Increases the value at position by one.
     * 
     * @param i the first coordinate
     * @param j the second coordinate
     * @param k the third coordinates
     * 
     * @note The function assumes that the Position is valid and does not check bounds.
     *
     * @see inc(Position)
     */
    void inc(int i, int j, int k);

    /**
     * Safe set, checks bounds before trying to access the array.
     * 
     * @param i the first coordinate
     * @param j the second coordinate
     * @param k the third coordinates
     * 
     * @see uset(int,int,int,int) set(int,int) set(Position,int)
     */
    void set(int i, int j, int k, int v);

    /**
     * Safe set, checks bounds before trying to access the array.
     * 
     * @param i the index
     * 
     * @see uset(int,int,int,int) set(int,int,int,int) set(Position,int)
     */
    void set(int i, int v);

    /**
     * Safe get, checks bounds before trying to access the array.
     * 
     * @param i the first coordinate
     * @param j the second coordinate
     * @param k the third coordinates
     * 
     * @see uget(int,int,int) get(Position) get(int)
     */
    int get(int i, int j, int k);

    /**
     * Safe get, checks bounds before trying to access the array.
     * 
     * @param i the index
     * 
     * @see uget(int,int,int) get(Position) get(int,int,int)
     */
    int get(int i);

    /**
     * Subtracts the GameState given as an argument from the current object position-wise.
     * 
     * @param s a pointer to the GameState to be subracted
     */
    void minus(GameState* s);

    /**
     * Compares the argument GameState to the current object position-wise.
     * 
     * @param s the GameState to be compared
     */
    bool operator==(GameState s);

    /**
     * Copies the values of the argument GameState to the current object.
     * 
     * @param s a pointer to the GameState to be subracted
     */
    void copy(GameState* s);
    GameState();
};

/**
 * This class is identical to the GameState class, but all members are protected
 * has CompromiseGame as a friend class.
 */
class InnerGameState: protected GameState
{
    friend class CompromiseGame;
};