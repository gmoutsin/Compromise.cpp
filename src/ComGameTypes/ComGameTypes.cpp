#include "ComGameTypes.h"

bool validPosisionQ(Position p)
{
    return (0 <= p[0] <= 2) && (0 <= p[1] <= 2) && (0 <= p[2] <= 2);
}

bool invalidPosisionQ(Position p)
{
    return p[0] < 0 || p[0] > 2 || p[1] < 0 || p[1] > 2 || p[2] < 0 || p[2] > 2;
}

void random(Position* pos)
{
    (*pos)[0] = rand() % 3;
    (*pos)[1] = rand() % 3;
    (*pos)[2] = rand() % 3;
}

int GameState::uget(int i, int j, int k) 
{ // unsafe get, no bound checking
    return data[9*i+3*j+k];
};

void GameState::uset(int i, int j, int k, int val) 
{ // unsafe set, no bound checking
    data[9*i+3*j+k] = val;
};

void GameState::set(Position p, int v)
{
    data[9*p[0]+3*p[1]+p[2]] = v;
}

int GameState::get(Position p)
{
    return data[9*p[0]+3*p[1]+p[2]];
}

void GameState::inc(Position p)
{
    data[9*p[0]+3*p[1]+p[2]] += 1;
}

void GameState::inc(int i, int j, int k) 
{ // unsafe set, no bound checking
    data[9*i+3*j+k] += 1;
};

void GameState::set(int i, int j, int k, int val) 
{
    if (i<0 || i>2 || j<0 || j>2 || k<0 || k>2)
    {
        /* throw error */
    }
    data[9*i+3*j+k] = val;
};

void GameState::set(int i, int val) 
{
    if (i<0 || i>27)
    {
        /* throw error */
    }
    data[i] = val;
};

int GameState::get(int i, int j, int k) 
{
    if (i<0 || i>2 || j<0 || j>2 || k<0 || k>2)
    {
        /* throw error */
    }
    return data[9*i+3*j+k];
};

int GameState::get(int i) 
{
    if (i<0 || i>27)
    {
        /* throw error */
    }
    return data[i];
};

void GameState::minus(GameState* s)
{
    for (int i = 0; i < 27; i++)
    {
        data[i] -= s->data[i];
    }
}

bool GameState::operator==(GameState s)
{
    for (int i = 0; i < 27; i++)
    {
        if (data[i] != s.data[i])
        {
            return false;
        }
    }
        return true;
}

void GameState::copy(GameState* s)
{
    for (int i = 0; i < 27; i++)
    {
        data[i] = s->data[i];
    }
}

GameState::GameState() 
{
    for (int i = 0; i < 27; i++)
    {
        data[i] = 0;
    }
};