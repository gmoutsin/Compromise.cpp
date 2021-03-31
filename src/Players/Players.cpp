#include "Players.h"

void RandomPlayer::play(Position* res, GameState* mystate, GameState* oppstate, int myscore, int oppscore, int turn, int length, int newPips)
{
    (*res)[0] = rand() % 3;
    (*res)[1] = rand() % 3;
    (*res)[2] = rand() % 3;
};

void RandomPlayer::place(PlacementArray* res, GameState* mystate, GameState* oppstate, int myscore, int oppscore, int turn, int length, int newPips)
{
    for (int i = 0; i < (*res).size(); i++)
    {
        (*res)[i][0] = rand() % 3;
        (*res)[i][1] = rand() % 3;
        (*res)[i][2] = rand() % 3;
    };
};

void DeterminedPlayer::play(Position* res, GameState* mystate, GameState* oppstate, int myscore, int oppscore, int turn, int length, int newPips)
{
    mystate->minus(oppstate);
    int p1, p2, p3, v = INT_MIN;
    c1[0] = c1[1] = c2[0] = c2[1] = c3[0] = c3[1] = -1;
    p1 = p2 = p3 = -1;
    while (c1[0] == -1 || c1[1] == -1 || c2[0] == -1 || c2[1] == -1 || c3[0] == -1 || c3[1] == -1 )
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    if (mystate->uget(i,j,k) > v)
                    {
                        v = mystate->uget(i,j,k);
                        p1 = i;
                        p2 = j;
                        p3 = k;
                    }
                    
                }
                
            }
            
        }
        mystate->uset(p1,p2,p3,INT_MIN);
        v = INT_MIN;
        if (c1[0] == -1)
        {
            c1[0] = p1;
        }
        else
        {
            if (c1[1] == -1)
            {
                c1[1] = p1;
            } 
        }
        if (c2[0] == -1)
        {
            c2[0] = p2;
        }
        else
        {
            if (c2[1] == -1)
            {
                c2[1] = p2;
            } 
        }
        if (c3[0] == -1)
        {
            c3[0] = p3;
        }
        else
        {
            if (c3[1] == -1)
            {
                c3[1] = p3;
            } 
        }
    }
    for (int i = 0; i < 3; i++)
    {
        if (c1[0] != i && c1[1] != i)
        {
            (*res)[0] = i;
        }
        if (c2[0] != i && c2[1] != i)
        {
            (*res)[1] = i;
        }
        if (c3[0] != i && c3[1] != i)
        {
            (*res)[2] = i;
        }
    }
};

void GreedyPlayer::play(Position* res, GameState* mystate, GameState* oppstate, int myscore, int oppscore, int turn, int length, int newPips)
{
    int s1, s2, s3, m1, m2, m3;
    s1 = s2 = s3 = 0;
    m1 = m2 = m3 = INT_MAX;
    c1[0] = c1[1] = c1[2] = c2[0] = c2[1] = c2[2] = c3[0] = c3[1] = c3[2] = -1;
    (*res)[0] = (*res)[1] = (*res)[2] = -1;
    mystate->minus(oppstate);
    for (int i = 0; i < 3; i++)
    {
        s1 = s2 = s3 = 0;
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                s1 += mystate->get(i,j,k);
                s2 += mystate->get(j,i,k);
                s3 += mystate->get(k,j,i);
            }
        }
        c1[i] = s1;
        c2[i] = s2;
        c3[i] = s3;
    }
    for (int i = 0; i < 3; i++)
    {
        if (c1[i] < m1)
        {
            m1 = c1[i];
            (*res)[0] = i;
        }
        if (c2[i] < m2)
        {
            m2 = c2[i];
            (*res)[1] = i;
        }
        if (c3[i] < m3)
        {
            m3 = c3[i];
            (*res)[2] = i;
        }
    }
}