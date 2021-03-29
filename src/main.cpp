#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <ctime>
#include <random>

#include "ComGameTypes.h"
#include "Players.h"
#include "ComGame.h"

// #include "../include/CompromiseTypeDef.cpp"
// #include "../include/Players.cpp"
// #include "../include/CompromiseGame.cpp"

int main() 
{
    RandomPlayer p;
    CompromiseGame g(&p,&p,120,1);
    srand(rand() + (unsigned)time(0));
    g.play_unsafe();
    std::cout << g.score1 << ":" << g.score2 << '\n';
    return 0;
};