#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"


using namespace std;

#define DELAY_CONST 100000
#define DELAY_CONST_2 999999


//global variables
GameMechs* myGM;
Player* myPlayer;
Food* myfood;


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void LoopDelay2(void);
void CleanUp(void);


int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    //initializing on the heap
    myGM = new GameMechs(30,15);
    myfood = new Food();
    myPlayer = new Player(myGM,myfood);

    //initialize food avoid player position
    objPosArrayList* tempPlayer = myPlayer->getPlayerPos();
    myfood->generateFood(tempPlayer);

    //update time
    srand(time(NULL));  
}

void GetInput(void)
{
    myGM->getInput();
}


void RunLogic(void)
{

    //moving the snake
    myPlayer->updatePlayerDir(); 
    myPlayer->movePlayer();  
    myGM->clearInput();

    //getting the player pos
    objPosArrayList* tempPlayer = myPlayer->getPlayerPos();
    objPos temphead;
    tempPlayer->getHeadElement(temphead);

    //if the usual food is eaten
    if(myPlayer->checkFoodConsumption()==1)
    {
        myPlayer->increasePlayerLength(); //increases snake length by 1
        myfood->generateFood(tempPlayer); //generates new food 
        myGM->incrementScore(); //increments the score by 1 point
    }
    else if(myPlayer->checkFoodConsumption()==2) //if special food is eaten
    {
        myfood->generateFood(tempPlayer); //generates new food
        for(int i=0;i<10;i++) 
            myGM->incrementScore(); //increments the score by 10 points since it's a special food
    }
    if(myPlayer->checkSelfCollision()) //checking for self collision
    {
        myGM->setLoseFlag();
    }
}


void DrawScreen(void)
{
    MacUILib_clearScreen();  

    //local variables
    objPos bodypart,tempfoodpos;
    objPosArrayList* tempPlayer = myPlayer->getPlayerPos();
    objPosArrayList* tempFoodBin = myfood->getFoodPos();

    //getting the information from the head element
    objPos currentHead;
    tempPlayer->getHeadElement(currentHead);
    
    for(int i = 0;i < myGM->getBoardSizeY();i++)
    {
        for(int j = 0;j< myGM->getBoardSizeX() ;j++) //iterating through all the xy coordinates
        {
            for(int k=0; k<tempPlayer->getSize();k++)
            {
                tempPlayer->getElement(bodypart,k);
                if(bodypart.x == j && bodypart.y==i) //it will skip if the snake is in the xy coordinate
                {
                    break;
                }
            }
            for(int k=0; k<tempFoodBin->getSize();k++)
            {
                tempFoodBin->getElement(tempfoodpos,k);
                
                if(tempfoodpos.x == j && tempfoodpos.y==i) //it will skip if the food is in the xy coordinate
                {
                    break;
                }
            }
            if(j == bodypart.x && i == bodypart.y)
            {
                MacUILib_printf("%c",bodypart.symbol); //drawing snake body
            }

            else if( j == tempfoodpos.x && i == tempfoodpos.y)
            {
                MacUILib_printf("%c",tempfoodpos.symbol); //drawing food
            }

            else if( i == 0 || i == myGM->getBoardSizeY() - 1 || j == 0 || j == myGM->getBoardSizeX() - 1)
            {
                MacUILib_printf("#"); //drawing the outline
            }
            else
            {
                MacUILib_printf(" "); //drawing empty spaces
            }
        }
        MacUILib_printf("\n");
    } 

    //displaying score and head coordinate
    MacUILib_printf("Current head pos: <%d,%d>\nCurrent Score: %d\n",currentHead.x,currentHead.y,myGM->getScore());
    
    if(myPlayer->checkSelfCollision())
    {
        MacUILib_printf("Oopsie! You self collided :( \n"); //if self collided, the message is displayed for 2 seconds before showing final score 
        LoopDelay2();
        LoopDelay2();
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void LoopDelay2(void)
{
    MacUILib_Delay(DELAY_CONST_2); // 1 second delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    if(myGM ->getLoseFlagStatus())
    {
        MacUILib_printf("Final score: %d",myGM->getScore()); //displaying final score after losing 
        MacUILib_uninit();
    }

    else{
        MacUILib_uninit();
    }

    delete myGM;
    delete myPlayer;
    delete myfood;
}
