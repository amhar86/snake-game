#include "Player.h"


Player::Player(GameMechs* thisGMRef,Food* thisfood)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2,mainGameMechsRef->getBoardSizeY()/2,'@'); // Setting the start position to be in the middle 
                                                                                                    // if the board.
    //setting the initial player position
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);

    //getting the food information
    foodinfo = thisfood;
    

}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic  

    char input = mainGameMechsRef->getInput();  //getting the current input

    switch(input)
        {           
            //UP
            case 119:  
                if(myDir != DOWN || myDir == STOP)
                    myDir = UP;
                break;

            //LEFT
            case 97:    
                if(myDir != RIGHT || myDir == STOP)
                    myDir = LEFT;
                break;

            //DOWN    
            case 115: 
                if(myDir != UP || myDir == STOP)
                    myDir = DOWN;
                break;

            //RIGHT
            case 100:   
                if(myDir != LEFT || myDir == STOP)
                    myDir = RIGHT;
                break;

            case 27: //Press 'ESC' to stop the game
                mainGameMechsRef->setExitTrue();
                break;

            

            default:
                break;
        }


}


void Player::movePlayer()
{
    objPos currentHead;

    playerPosList->getHeadElement(currentHead);

    // PPA3 Finite State Machine logic
    switch (myDir) 
    {
        case UP:
            currentHead.y--;
            break;
        case DOWN:
            currentHead.y++;
            break;
        case LEFT:
            currentHead.x--;
            break;
        case RIGHT:
            currentHead.x++;
            break;
        default:
            break;
    }
    
    // Vertical Wraparound
    if (currentHead.y == 0) // Wrap to the bottom
    {
        currentHead.y = mainGameMechsRef->getBoardSizeY() - 2; 
    } 
    else if (currentHead.y == mainGameMechsRef->getBoardSizeY() - 1) // Wrap to the top
    {
        currentHead.y = 1; 
    }

    // Horizontal Wraparound
    if (currentHead.x == 0) // Wrap to the right
    {
        currentHead.x = mainGameMechsRef->getBoardSizeX() - 2; 
    } 
    else if (currentHead.x == mainGameMechsRef->getBoardSizeX() - 1)  // Wrap to the left
    {
        currentHead.x = 1;
    }

    //moving the snake by inserting head and removing tail on every iteration
    playerPosList->insertHead(currentHead);
    playerPosList->removeTail();

}

int Player::checkFoodConsumption()
{
    int cond;

    objPosArrayList* food = foodinfo->getFoodPos(); //getting the food information 

    objPos currentHead,foodpos;

    playerPosList->getHeadElement(currentHead); //getting the information about the head


    for(int i=0; i<food->getSize(); i++)
    {
        food->getElement(foodpos,i);
        if(foodpos.isPosEqual(&currentHead) &&foodpos.symbol=='*') //checking if the usual food is eaten
        {
            cond = 1;
            break;
        }

        else if(foodpos.isPosEqual(&currentHead) && foodpos.symbol=='0') //checking if the special food is eaten
        {
            cond = 2;
            break;
        }

        else //no food is eaten
        {
            cond = 0;
        }
    }
    


    return cond;
}


bool Player::checkSelfCollision()
{
    int s;

    objPos currentHead,bodypart;
    playerPosList->getHeadElement(currentHead);


    if(playerPosList->getSize()>1) //it only checks if the snake is longer than 1 symbol since otherwise collision is impossible
    {
        for(s=2; s<playerPosList->getSize();s++) //checking if the head is in the same coordinate as any of the other members of the current list
        {
            playerPosList->getElement(bodypart,s);

            if(bodypart.x == currentHead.x && bodypart.y == currentHead.y)
            {
                break;  
            }
        }

        if(s != playerPosList->getSize())
        {
            return true;
        }
        
    }

    return false;
}

void Player::increasePlayerLength()
{
    objPos currentHead;

    playerPosList->getHeadElement(currentHead);
    playerPosList->insertHead(currentHead); //increasing the length by inserting head
}