#include <iostream>
#include <string>
#include <chrono>
#include "ComGameTypes.h"
#include "Players.h"
#include "ComGame.h"

void playerStats(CompromiseGame* g, AbstractPlayer* p1, AbstractPlayer* p2, std::string mes, int times, int* res, int* score)
{
    res[0] = res[1] = res[2] = 0;
    g->newPlayers(p1,p2);
    for (int i = 0; i < times; i++)
    {
        g->resetGame();
        g->play_unsafe();
        g->getScore(score);
        if (score[0] > score[1])
        {
            res[0] += 1;
        }
        else if(score[0] == score[1])
        {
            res[1] += 1;
        }
        else
        {
            res[2] += 1;
        }
    }
    std::cout << mes << res[0] << " " << res[1] << " " << res[2] << std::endl;
};

int main() 
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    int res[3] = {0,0,0};
    int score[2];
    int times = 10000;
    int type = 2;
    bool noties = false;
    int rounds = 10;
    int pips = 20;
    std::string typelabel;
    std::string tieslabel = "";
    RandomPlayer pr;
    MyopicPlayer pm;
    GreedyPlayer pg;
    SmartGreedyPlayer ps;
    OscillatingPlayer po;
    CompromiseGame g(NULL, NULL, pips, rounds, type, noties);
    if (noties)
    {
        tieslabel = "not ";
    }
    if (type == 0)
    {
        typelabel = " gamble";
    }
    else if (type == 1)
    {
        typelabel = " simple";
    }
    else
    {
        typelabel = " complex";
    }
    std::cout << "\n" << "Players play " << times << typelabel << " games of " << rounds << " rounds with " << pips << " pips placed per round in which ties are " << tieslabel << "allowed.\n";
    auto t1 = high_resolution_clock::now();
    // playerStats(&g, &pr, &pr, " RandomPlayer       vs       RandomPlayer: ", times, res, score);
    playerStats(&g, &pm, &pr, "  MyopicPlayer       vs       RandomPlayer: ", times, res, score);
    playerStats(&g, &pg, &pr, "  GreedyPlayer       vs       RandomPlayer: ", times, res, score);
    playerStats(&g, &ps, &pr, "  SmartGreedyPlayer  vs       RandomPlayer: ", times, res, score);
    playerStats(&g, &po, &pr, "  OscillatingPlayer  vs       RandomPlayer: ", times, res, score);
    playerStats(&g, &po, &pm, "  OscillatingPlayer  vs       MyopicPlayer: ", times, res, score);
    playerStats(&g, &po, &pg, "  OscillatingPlayer  vs       GreedyPlayer: ", times, res, score);
    playerStats(&g, &po, &ps, "  OscillatingPlayer  vs  SmartGreedyPlayer: ", times, res, score);
    playerStats(&g, &pm, &pg, "  MyopicPlayer       vs       GreedyPlayer: ", times, res, score);
    playerStats(&g, &pm, &ps, "  MyopicPlayer       vs  SmartGreedyPlayer: ", times, res, score);
    playerStats(&g, &pg, &ps, "  GreedyPlayer       vs  SmartGreedyPlayer: ", times, res, score);
    auto t2 = high_resolution_clock::now();
    auto ms_int = duration_cast<milliseconds>(t2 - t1);
    duration<double, std::milli> ms_double = t2 - t1;
    std::cout << "Time elapsed: " << ms_double.count() << " ms \n";
    return 0;
};