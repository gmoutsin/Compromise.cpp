#include "Players.h"

void AbstractOscillatingPlacer::initialise(int, int, int, bool)
{
    int j1 = 0;
    int j2 = 0;
    int j3 = 0;
    int t1[2];
    int t2[2];
    int t3[2];
    random(pos1);
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
                (*block)[j] = i;
            }
        }
    }
};

void AbstractOscillatingPlacer::place(PlacementArray* res, GameState*, GameState*, int, int, int, int newPips)
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
        flip = (flip+1) & 1;
    };
};

AbstractOscillatingPlacer::AbstractOscillatingPlacer()
{
    pos1 = new Position;
    pos2 = new Position;
    block = new Position;
    flip = 0;
    initialise(0, 0, 0, false);
};

AbstractOscillatingPlacer::~AbstractOscillatingPlacer()
{
    delete pos1;
    delete pos2;
    delete block;
};

void AbstractConstantMover::move(Position* res, GameState*, GameState*, int, int, int, int)
{
    (*res)[0] = (*block)[0];
    (*res)[1] = (*block)[1];
    (*res)[2] = (*block)[2];
};

AbstractConstantMover::AbstractConstantMover()
{
    block = new Position;
    random(block);
};

AbstractConstantMover::~AbstractConstantMover()
{
    delete block;
};

void AbstractRandomMover::move(Position* res, GameState*, GameState*, int, int, int, int)
{
    random(res);
};

void AbstractRandomPlacer::place(PlacementArray* res, GameState*, GameState*, int, int, int, int newPips)
{
    for (int i = 0; i < newPips; i++)
    {
        (*res)[i][0] = rand() % 3;
        (*res)[i][1] = rand() % 3;
        (*res)[i][2] = rand() % 3;
    };
};

void AbstractMyopicMover::move(Position* res, GameState* myState, GameState* oppState, int, int, int, int newPips)
{
    myState->minus(oppState);
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
                    if (myState->uget(i,j,k) > v)
                    {
                        v = myState->uget(i,j,k);
                        p1 = i;
                        p2 = j;
                        p3 = k;
                    }
                }
            }
        }
        myState->uset(p1,p2,p3,INT_MIN);
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

void AbstractGreedyPlacer::place(PlacementArray* res, GameState* myState, GameState* oppState, int myScore, int oppScore, int turn, int newPips)
{
    int j1 = 0;
    int j2 = 0;
    int j3 = 0;
    int t1[2];
    int t2[2];
    int t3[2];
    Position pos;
    move(&pos, myState, oppState, myScore, oppScore, turn, newPips);
    for (int i = 0; i < 3; i++)
    {
        if (i != pos[0])
        {
            t1[j1] = i;
            j1 += 1;
        }
        if (i != pos[1])
        {
            t2[j2] = i;
            j2 += 1;
        }
        if (i != pos[2])
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

void AbstractGreedyMover::move(Position* res, GameState* myState, GameState* oppState, int, int, int, int newPips)
{
    int s1, s2, s3, m1, m2, m3, c1[3], c2[3], c3[3];
    s1 = s2 = s3 = 0;
    m1 = m2 = m3 = INT_MAX;
    c1[0] = c1[1] = c1[2] = c2[0] = c2[1] = c2[2] = c3[0] = c3[1] = c3[2] = -1;
    (*res)[0] = (*res)[1] = (*res)[2] = -1;
    myState->minus(oppState);
    for (int i = 0; i < 3; i++)
    {
        s1 = s2 = s3 = 0;
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                s1 += myState->uget(i,j,k);
                s2 += myState->uget(j,i,k);
                s3 += myState->uget(k,j,i);
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

void AbstractSmartGreedyMover::move(Position* res, GameState* myState, GameState* oppState, int, int, int, int newPips)
{
    int tmpres[3] = {-1,-1,-1};
    int mins[3] = {INT_MAX,INT_MAX,INT_MAX};
    bool locked[3] = {false,false,false};
    int sums[3][3] = {0,0,0,0,0,0,0,0,0};
    int min = INT_MAX;
    int pos;
    int indx;
    myState->minus(oppState);
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
                    sums[0][i] += myState->uget(i,j,k);
                    sums[1][i] += myState->uget(k,i,j);
                    sums[2][i] += myState->uget(j,k,i);
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
                    myState->uset((*res)[0],i,j,0);
                }
            }
        }
        else if (pos == 1)
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    myState->uset(i,(*res)[1],j,0);
                }
            }
        }
        else if (pos == 2)
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    myState->uset(i,j,(*res)[2],0);
                }
            }
        }
    }
};