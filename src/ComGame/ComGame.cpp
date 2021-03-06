#include "ComGame.h"

void CompromiseGame::printMoves()
{
    std::cout << "Player 1 move: " << (int) (*move1)[0]+1 << (int) (*move1)[2]+1 << (int) (*move1)[1]+1 << "\n";
    std::cout << "Player 2 move: " << (int) (*move2)[0]+1 << (int) (*move2)[2]+1 << (int) (*move2)[1]+1 << "\n\n";
}

void CompromiseGame::printState()
{
    std::cout << state1->uget(0,0,0) << ":" << state2->uget(0,0,0) << "\t";
    std::cout << state1->uget(0,1,0) << ":" << state2->uget(0,1,0) << "\t";
    std::cout << state1->uget(0,2,0) << ":" << state2->uget(0,2,0) << "\t";
    std::cout << "\t  ";
    std::cout << state1->uget(1,0,0) << ":" << state2->uget(1,0,0) << "\t";
    std::cout << state1->uget(1,1,0) << ":" << state2->uget(1,1,0) << "\t";
    std::cout << state1->uget(1,2,0) << ":" << state2->uget(1,2,0) << "\t";
    std::cout << "\t  ";
    std::cout << state1->uget(2,0,0) << ":" << state2->uget(2,0,0) << "\t";
    std::cout << state1->uget(2,1,0) << ":" << state2->uget(2,1,0) << "\t";
    std::cout << state1->uget(2,2,0) << ":" << state2->uget(2,2,0) << "\n";
    
    std::cout << state1->uget(0,0,1) << ":" << state2->uget(0,0,1) << "\t";
    std::cout << state1->uget(0,1,1) << ":" << state2->uget(0,1,1) << "\t";
    std::cout << state1->uget(0,2,1) << ":" << state2->uget(0,2,1) << "\t";
    std::cout << "\t  ";
    std::cout << state1->uget(1,0,1) << ":" << state2->uget(1,0,1) << "\t";
    std::cout << state1->uget(1,1,1) << ":" << state2->uget(1,1,1) << "\t";
    std::cout << state1->uget(1,2,1) << ":" << state2->uget(1,2,1) << "\t";
    std::cout << "\t  ";
    std::cout << state1->uget(2,0,1) << ":" << state2->uget(2,0,1) << "\t";
    std::cout << state1->uget(2,1,1) << ":" << state2->uget(2,1,1) << "\t";
    std::cout << state1->uget(2,2,1) << ":" << state2->uget(2,2,1) << "\n";
    
    std::cout << state1->uget(0,0,2) << ":" << state2->uget(0,0,2) << "\t";
    std::cout << state1->uget(0,1,2) << ":" << state2->uget(0,1,2) << "\t";
    std::cout << state1->uget(0,2,2) << ":" << state2->uget(0,2,2) << "\t";
    std::cout << "\t  ";
    std::cout << state1->uget(1,0,2) << ":" << state2->uget(1,0,2) << "\t";
    std::cout << state1->uget(1,1,2) << ":" << state2->uget(1,1,2) << "\t";
    std::cout << state1->uget(1,2,2) << ":" << state2->uget(1,2,2) << "\t";
    std::cout << "\t  ";
    std::cout << state1->uget(2,0,2) << ":" << state2->uget(2,0,2) << "\t";
    std::cout << state1->uget(2,1,2) << ":" << state2->uget(2,1,2) << "\t";
    std::cout << state1->uget(2,2,2) << ":" << state2->uget(2,2,2) << "\n\n";
}

void CompromiseGame::resetGame() 
{
    srand( (unsigned)time(0) );
    score1 = 0;
    score2 = 0;
    turn = 0;
    for (int i = 0; i < 27; i++)
    {
        state1->data[i] = 0;
        state2->data[i] = 0;
    }
};

void CompromiseGame::newPlayers(AbstractPlayer* player1, AbstractPlayer* player2) 
{
    p1 = player1;
    p2 = player2;
    resetGame();
};

void CompromiseGame::prepareDisposableStates() 
{
    for (int i = 0; i < 27; i++) {
        disp1->data[i] = state1->data[i];
        disp2->data[i] = state2->data[i];
    }
};

void CompromiseGame::placePips() 
{
    if (type == 1) // 1 is simple
    {
        for (int i = 0; i < newPips; i++)
        { // placement arrays are circumvented, the states are directly increased
            state1->inc(rand() % 3, rand() % 3, rand() % 3);
            state2->inc(rand() % 3, rand() % 3, rand() % 3);
        }
    }
    else 
    {
        prepareDisposableStates();
        p1->place(placement1, disp1, disp2, score1, score2, turn, newPips);
        prepareDisposableStates();
        p2->place(placement2, disp2, disp1, score2, score1, turn, newPips);
        for (int i = 0; i < newPips; i++)
        {
            if (invalidPosisionQ( (*placement1)[i] ))
            {
                /* throw error */
            }
            if (invalidPosisionQ( (*placement2)[i] ))
            {
                /* throw error */
            }
        }
        for (int i = 0; i < newPips; i++)
        {
            state1->inc((*placement1)[i]);
            state2->inc((*placement2)[i]);
        }
    }
    
};

void CompromiseGame::placePips_unsafe() 
{
    if (type == 1) // 1 is simple
    {
        for (int i = 0; i < newPips; i++)
        { // placement arrays are circumvented, the states are directly increased
            state1->inc(rand() % 3, rand() % 3, rand() % 3);
            state2->inc(rand() % 3, rand() % 3, rand() % 3);
        }
    }
    else 
    {
        prepareDisposableStates();
        p1->place(placement1, disp1, disp2, score1, score2, turn, newPips);
        prepareDisposableStates();
        p2->place(placement2, disp2, disp1, score2, score1, turn, newPips);
        
        for (int i = 0; i < newPips; i++)
        {
            state1->inc((*placement1)[i]);
            state2->inc((*placement2)[i]);
        }
    }
};

void CompromiseGame::getMoves() 
{
    if (type==0) // 0 is gamble
    {
        (*move1)[0] = rand() % 3;
        (*move1)[1] = rand() % 3;
        (*move1)[2] = rand() % 3;
        (*move2)[0] = rand() % 3;
        (*move2)[1] = rand() % 3;
        (*move2)[2] = rand() % 3;
    }
    else
    {
        prepareDisposableStates();
        p1->move(move1, disp1, disp2, score1, score2, turn, newPips);
        prepareDisposableStates();
        p2->move(move2, disp2, disp1, score2, score1, turn, newPips);
        if (invalidPosisionQ(*move1))
        {
            /* throw error */
        }
        if (invalidPosisionQ(*move2))
        {
            /* throw error */
        }
    }
};

void CompromiseGame::getMoves_unsafe() 
{
    if (type==0) // 0 is gamble
    {
        (*move1)[0] = rand() % 3;
        (*move1)[1] = rand() % 3;
        (*move1)[2] = rand() % 3;
        (*move2)[0] = rand() % 3;
        (*move2)[1] = rand() % 3;
        (*move2)[2] = rand() % 3;
    }
    else
    {
        prepareDisposableStates();
        p1->move(move1, disp1, disp2, score1, score2, turn, newPips);
        prepareDisposableStates();
        p2->move(move2, disp2, disp1, score2, score1, turn, newPips);
    }
};

void CompromiseGame::updateScore() 
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                if ( !(i==(*move1)[0] || i==(*move2)[0] || j==(*move1)[1] || j==(*move2)[1] || k==(*move1)[2] || k==(*move2)[2]) )
                {
                    score1 += state1->uget(i,j,k);
                    score2 += state2->uget(i,j,k);
                    state1->uset(i,j,k,0);
                    state2->uset(i,j,k,0);
                }
            }
        }
    }
};

void CompromiseGame::getScore(int* res) 
{
    res[0] = score1;
    res[1] = score2;
};

void CompromiseGame::playRound() 
{
    turn += 1;
    placePips();
    getMoves();
    updateScore();
};

void CompromiseGame::playRound_unsafe() 
{
    turn += 1;
    placePips_unsafe();
    getMoves_unsafe();
    updateScore();
};

void CompromiseGame::play() 
{
    p1->initialise(type, length, newPips, noTies);
    p2->initialise(type, length, newPips, noTies);
    while (turn<length || (noTies && score1==score2))
    {
        playRound();
    }
};

void CompromiseGame::play_unsafe() 
{
    p1->initialise(type, length, newPips, noTies);
    p2->initialise(type, length, newPips, noTies);
    while (turn < length || (noTies && score1==score2))
    {
        playRound_unsafe();
    }
};

CompromiseGame::CompromiseGame(AbstractPlayer* player1, AbstractPlayer* player2, int newpips, int len, int gametype, bool noties) 
{
    srand( (unsigned)time(0) );
    p1 = player1;
    p2 = player2;
    newPips = newpips;
    length = len;
    type = gametype;
    noTies = noties;
    state1 = new InnerGameState();
    state2 = new InnerGameState();
    disp1 = new GameState();
    disp2 = new GameState();
    move1 = new Position;
    move2 = new Position;
    placement1 = new PlacementArray(newpips);
    placement2 = new PlacementArray(newpips);
    score1 = 0;
    score2 = 0;
    turn = 0;
};

CompromiseGame::~CompromiseGame() 
{
    delete state1;
    delete state2;
    delete disp1;
    delete disp2;
    delete move1;
    delete move2;
    delete placement1;
    delete placement2;
}