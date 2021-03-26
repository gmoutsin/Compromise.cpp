#include "Players.h"

void Player::play(Position* res) 
{
    (*res)[0] = rand() % 3;
    (*res)[1] = rand() % 3;
    (*res)[2] = rand() % 3;
};

void Player::place(PlacementArray* res) 
{
    for (int i = 0; i < (*res).size(); i++)
    {
        (*res)[i][0] = rand() % 3;
        (*res)[i][1] = rand() % 3;
        (*res)[i][2] = rand() % 3;
    };
};