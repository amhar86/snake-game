#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "objPosArrayList.h"


class Food
{
    private:
        objPosArrayList* foodBin;

    public:
        Food();   //Constructor
        ~Food();  //Desstructor
        void generateFood(objPosArrayList* coord); 
        objPosArrayList* getFoodPos(); 
};

#endif