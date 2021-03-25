#include <iostream>
#include "..\\include\\CompromiseTypeDef.h"

inline bool validPosisionQ(Position p)
{
    return (0 <= p[0] <= 2) && (0 <= p[1] <= 2) && (0 <= p[2] <= 2);
}

inline bool invalidPosisionQ(Position p)
{
    return p[0] < 0 || p[0] > 2 || p[1] < 0 || p[1] > 2 || p[2] < 0 || p[2] > 2;
}

inline int GameState::uget(int i, int j, int k) 
{ // unsafe get, no bound checking
    return data[9*i+3*j+k];
};

inline void GameState::uset(int i, int j, int k, int val) 
{ // unsafe set, no bound checking
    data[9*i+3*j+k] = val;
};

inline void GameState::set(Position p, int v)
{
    data[9*p[0]+3*p[1]+p[2]] = v;
}

inline void GameState::inc(Position p)
{
    data[9*p[0]+3*p[1]+p[2]] += 1;
}

inline void GameState::inc(int i, int j, int k) 
{ // unsafe set, no bound checking
    data[9*i+3*j+k] += 1;
};

inline void GameState::set(int i, int j, int k, int val) 
{
    if (i<0 || i>2 || j<0 || j>2 || k<0 || k>2)
    {
        /* throw error */
    }
    data[9*i+3*j+k] = val;
};

inline void GameState::set(int i, int val) 
{
    if (i<0 || i>27)
    {
        /* throw error */
    }
    data[i] = val;
};

GameState::GameState() 
{
    for (int8_t i = 0; i < 27; i++)
    {
        data[i] = 0;
    }
};

inline int GameState::get(int i, int j, int k) 
{
    if (i<0 || i>2 || j<0 || j>2 || k<0 || k>2)
    {
        // throw error
    }
    return data[9*i+3*j+k];
};

inline int GameState::get(int i) 
{
    if (i<0 || i>27)
    {
        /* throw error */
    }
    return data[i];
};
