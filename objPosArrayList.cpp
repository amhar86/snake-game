#include "objPosArrayList.h"


objPosArrayList::objPosArrayList()
{
    sizeArray = ARRAY_MAX_CAP;
    sizeList = 0;
    aList = new objPos[ARRAY_MAX_CAP];
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;   

}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if(sizeArray == sizeList) //check if the array is full 
    {
        return;
    }

    for(int i=sizeList ; i>0 ;i--)
    {
        aList[i].setObjPos(aList[i-1]);  //shuffling everything towards the tail 

    }

    aList[0].setObjPos(thisPos);  //inserting head
    sizeList++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(sizeArray == sizeList) //check if the array is full 
    {
        return;
    }

    aList[sizeList].setObjPos(thisPos); //inserting tail at the end

    sizeList++;
}

void objPosArrayList::removeHead()
{
    if(sizeList == 0) // if the list is empty don't remove anything
    {
        return;
    }   

    for(int i =0;i<sizeList-1;i++) //shuffling all the elements towards the head
    {
        aList[i].setObjPos(aList[i+1]);
    }
    sizeList--;

}

void objPosArrayList::removeTail()
{
    if(sizeList ==0) // if the list is empty don't do anything again 
    {
        return;
    }

    sizeList--;  //decrementing the list removes the tail 
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    if(sizeList ==0)
    {
        return;
    }

    returnPos.setObjPos(aList[0]); //getting the head element at index 0

}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    if(sizeList ==0) 
    {
        return;
    }

    returnPos.setObjPos(aList[sizeList-1]); //getting the tail element from the last index
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    if(sizeList ==0)
    {
        return;
    }

    returnPos.setObjPos(aList[index]); //getting the element from the inputed index

}