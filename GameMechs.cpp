#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    score = 0;
    loseFlag = false;
    boardSizeX = 30;
    boardSizeY = 15;
}


GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    score = 0;
    loseFlag = false;
    boardSizeX = boardX;
    boardSizeY = boardY;

}

// do you need a destructor?

GameMechs::~GameMechs()
{
    //Destructor is not needed
}




bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}


bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}


void GameMechs::setLoseFlag()
{
    loseFlag = true;
    exitFlag = true;
}


char GameMechs::getInput()
{
    if(MacUILib_hasChar()) //get input when there is a key pressed
    {
        input = MacUILib_getChar();
    }
    return input;
}


void GameMechs::setInput(char this_input)
{
    input = this_input;
}


void GameMechs::clearInput()
{
    input = 0;
}



int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}


int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}


int GameMechs::getScore()
{
    return score;
}


void GameMechs::incrementScore()
{
    score++;
}