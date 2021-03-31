#include <iostream>
#include <string>
#include "ComGameTypes.h"
#include "Players.h"
#include "ComGame.h"

int main() 
{
    int res[2] = {0,0};
    int score[2];
    RandomPlayer pr;
    DeterminedPlayer pd;
    GreedyPlayer pg;
    CompromiseGame g(&pd,&pr,20,10);
    for (int i = 0; i < 1000; i++)
    {
        g.resetGame();
        g.play_unsafe();
        g.getScore(score);
        if (score[0] > score[1])
        {
            res[0] += 1;
        }
        else
        {
            res[1] += 1;
        }  
    }
    std::cout << "DeterminedPlayer vs RandomPlayer: " << res[0] << " " << res[1] << '\n';
    res[0] = res[1] = 0;
    g.newPlayers(&pg,&pd);
    for (int i = 0; i < 1000; i++)
    {
        g.resetGame();
        g.play_unsafe();
        g.getScore(score);
        if (score[0] > score[1])
        {
            res[0] += 1;
        }
        else
        {
            res[1] += 1;
        }  
    }
    std::cout << "GreedyPlayer vs DeterminedPlayer: " << res[0] << " " << res[1] << '\n';
    return 0;
};