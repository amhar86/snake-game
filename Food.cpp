#include "Food.h"


Food::Food()
{
    foodBin = new objPosArrayList();
}

Food::~Food()
{
    delete foodBin;
}

void Food::generateFood(objPosArrayList* coord)
{
    int x,y,size,s;
    int counter = 0;
    objPos tempplayer, tempfood;
    int board[30][15] = {0};  //used to check if coordinates for food generation overlap with snake
    bool not_overlap = false; //declaring a boolean that is true when food generation coordinate doesn't overlap with snake
    size = foodBin->getSize(); //getting the size of the bin

    while(size>0)
    {
        foodBin->removeHead(); //removing all the food from the bin first
        size--;
    }
    while(counter < 3) //generating 3 regular foods
    {
        x = 1 + rand() % 28;
        y = 1 + rand() % 13;
        tempfood.setObjPos(x,y,'*');
        bool Flag = true;

        for(int s=0; s < coord->getSize(); s++) //check if the food coordinates overlap with the snake's body
        {
            coord->getElement(tempplayer,s);
            if(tempplayer.isPosEqual(&tempfood))
            {
                Flag = false; //flag stays false since food coord and snake body overlap
                break;
            }
        }   
        if(Flag)
        {
            if(board[tempfood.x][tempfood.y] == 0 ) //if the food coord and snake body do not overlap
            {
                foodBin->insertTail(tempfood); //adding the food and marking the vector
                board[tempfood.x][tempfood.y]++; 
                counter++; //incrementing food counter
            }
        }

    }

    while(counter < 5) //generates two special food if the total number of food is 4 or less
    {
        bool Flag = 1;
        x = 1 + rand() % 28;
        y = 1 + rand() % 13;
        tempfood.setObjPos(x,y,'0');

        for(int s=0; s<coord->getSize(); s++) //if the food coordinate doesn't overlap snake body
        {
            coord->getElement(tempplayer,s); 
            if(tempplayer.isPosEqual(&tempfood))
            {
                Flag = 0;
                break;
            }
        }   
        if(Flag)
        {
            if(board[tempfood.x][tempfood.y] == 0 )
            {
                foodBin->insertTail(tempfood); //add the food and mark the vector again 
                board[tempfood.x][tempfood.y]++;
                counter++;
            }
        }
    }
}

objPosArrayList* Food::getFoodPos()
{
    return foodBin;
}