#include "Players.h"

void OscillatingPlayer::play(Position* res, GameState* mystate, GameState* oppstate, int myscore, int oppscore, int turn, int length, int newPips)
{
    (*res)[0] = (*move)[0];
    (*res)[1] = (*move)[1];
    (*res)[2] = (*move)[2];
};

void OscillatingPlayer::place(PlacementArray* res, GameState* mystate, GameState* oppstate, int myscore, int oppscore, int turn, int length, int newPips)
{
    for (int i = 0; i < newPips; i++)
    {
        if (flip)
        {
            (*res)[i][0] = (*pos1)[0];
            (*res)[i][1] = (*pos1)[1];
            (*res)[i][2] = (*pos1)[2];
        }
        else
        {
            (*res)[i][0] = (*pos2)[0];
            (*res)[i][1] = (*pos2)[1];
            (*res)[i][2] = (*pos2)[2];
        }
    };
    flip = (flip+1) & 1;
};

OscillatingPlayer::OscillatingPlayer()
{
    pos1 = new Position;
    pos2 = new Position;
    move = new Position;
    flip = 0;
    int j1 = 0;
    int j2 = 0;
    int j3 = 0;
    int t1[2];
    int t2[2];
    int t3[2];
    (*pos1)[0] = rand() % 3;
    (*pos1)[1] = rand() % 3;
    (*pos1)[2] = rand() % 3;
    for (int i = 0; i < 3; i++)
    {
        if (i != (*pos1)[0])
        {
            t1[j1] = i;
            j1 += 1;
        }
        if (i != (*pos1)[1])
        {
            t2[j2] = i;
            j2 += 1;
        }
        if (i != (*pos1)[2])
        {
            t3[j3] = i;
            j3 += 1;
        }
    }
    (*pos2)[0] = t1[rand() & 1];
    (*pos2)[1] = t2[rand() & 1];
    (*pos2)[2] = t3[rand() & 1];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if ( (*pos1)[j] != i && (*pos2)[j] != i )
            {
                (*move)[j] = i;
            }
        }
    }
};

OscillatingPlayer::~OscillatingPlayer()
{
    delete pos1;
    delete pos2;
    delete move;
};

void RandomPlayer::play(Position* res, GameState* mystate, GameState* oppstate, int myscore, int oppscore, int turn, int length, int newPips)
{
    (*res)[0] = rand() % 3;
    (*res)[1] = rand() % 3;
    (*res)[2] = rand() % 3;
};

void RandomPlayer::place(PlacementArray* res, GameState* mystate, GameState* oppstate, int myscore, int oppscore, int turn, int length, int newPips)
{
    for (int i = 0; i < newPips; i++)
    {
        (*res)[i][0] = rand() % 3;
        (*res)[i][1] = rand() % 3;
        (*res)[i][2] = rand() % 3;
    };
};

void MyopicPlayer::play(Position* res, GameState* mystate, GameState* oppstate, int myscore, int oppscore, int turn, int length, int newPips)
{
    mystate->minus(oppstate);
    int p1, p2, p3, v = INT_MIN;
    int c1[2] = {-1,-1};
    int c2[2] = {-1,-1};
    int c3[2] = {-1,-1};
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

void MyopicPlayer::place(PlacementArray* res, GameState* mystate, GameState* oppstate, int myscore, int oppscore, int turn, int length, int newPips)
{
    int j1 = 0;
    int j2 = 0;
    int j3 = 0;
    play(pos, mystate, oppstate, myscore, oppscore, turn, length, newPips);
    for (int i = 0; i < 3; i++)
    {
        if (i != (*pos)[0])
        {
            t1[j1] = i;
            j1 += 1;
        }
        if (i != (*pos)[1])
        {
            t2[j2] = i;
            j2 += 1;
        }
        if (i != (*pos)[2])
        {
            t3[j3] = i;
            j3 += 1;
        }
    }
    for (int i = 0; i < newPips; i++)
    {
        (*res)[i][0] = t1[rand() & 1];
        (*res)[i][1] = t2[rand() & 1];
        (*res)[i][2] = t3[rand() & 1];
    }
}

MyopicPlayer::MyopicPlayer()
{
    pos = new Position;
    t1 = new int[2];
    t2 = new int[2];
    t3 = new int[2];
};

MyopicPlayer::~MyopicPlayer()
{
    delete pos;
    delete t1;
    delete t2;
    delete t3;
};

void GreedyPlayer::play(Position* res, GameState* mystate, GameState* oppstate, int myscore, int oppscore, int turn, int length, int newPips)
{
    int s1, s2, s3, m1, m2, m3, c1[3], c2[3], c3[3];
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
                s1 += mystate->uget(i,j,k);
                s2 += mystate->uget(j,i,k);
                s3 += mystate->uget(k,j,i);
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
};

void SmartGreedyPlayer::play(Position* res, GameState* mystate, GameState* oppstate, int myscore, int oppscore, int turn, int length, int newPips)
{
    int tmpres[3] = {-1,-1,-1};
    int mins[3] = {INT_MAX,INT_MAX,INT_MAX};
    bool locked[3] = {false,false,false};
    int sums[3][3] = {0,0,0,0,0,0,0,0,0};
    int min = INT_MAX;
    int pos;
    int indx;
    mystate->minus(oppstate);
    while (not (locked[0] && locked[1] && locked[2]) )
    {
        mins[0] = mins[1] = mins[2] = INT_MAX;
        min = INT_MAX;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    sums[0][i] += mystate->uget(i,j,k);
                    sums[1][i] += mystate->uget(k,i,j);
                    sums[2][i] += mystate->uget(j,k,i);
                }
            }
        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (mins[i] > sums[i][j])
                {
                    mins[i] = sums[i][j];
                    tmpres[i] = j;
                }
            }
        }
        for (int i = 0; i < 3; i++)
        {
            if ((not locked[i]) && (min > mins[i]))
            {
                min = mins[i];
                pos = i;
            }
        }
        locked[pos] = true;
        (*res)[pos] = tmpres[pos];
        if (pos == 0)
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    mystate->uset((*res)[0],i,j,0);
                }
            }
        }
        else if (pos == 1)
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    mystate->uset(i,(*res)[1],j,0);
                }
            }
        }
        else if (pos == 2)
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    mystate->uset(i,j,(*res)[2],0);
                }
            }
        }
    }
};