#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <ctime>
#include <random>

#include "../include/CompromiseTypeDef.h"
#include "../include/Players.h"
#include "../include/CompromiseGame.h"

// #include "CompromiseTypeDef.cpp"
// #include "Players.cpp"
// #include "CompromiseGame.cpp"

int main() 
{
    RandomPlayer p;
    CompromiseGame g(&p,&p,120,1);
    srand(rand() + (unsigned)time(0));
    g.play_unsafe();
    std::cout << g.score1 << ":" << g.score2 << '\n';
    return 0;
};