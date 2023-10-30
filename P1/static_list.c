/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Guillermo Fernandez Sanchez LOGIN 1: guillermo.fernandezs
 * AUTHOR 2: Javier Fernandez Rozas      LOGIN 2: j.frozas
 * GROUP: 6.1
 * DATE: 31 / 03 / 21
 */

#include "static_list.h"
#include "string.h"


void createEmptyList(tList *l){
    /*Creates an empty list*/

    l->lastPos = LNULL;

}

bool isEmptyList(tList l){
    /*Checks if the list inserted is an empty list*/

    return (l.lastPos == LNULL);

}

tPosL first(tList l){

    /*The static list is an array, therefore the position of the first item is the position 0 in the array*/
    return 0;

}

tPosL last(tList l){
    //returns the last position on the list

    return l.lastPos;

}

tPosL next(tPosL p,tList l){
    //returns the position after the position inserted

    if ( p == l.lastPos ){

        return LNULL;

    } else return ++p;

}

tPosL previous(tPosL p,tList l){
    //Returns the previous position to the one inserted

    return --p;
    //if p is 0 it would return LNULL but as LNULL is equal to -1 we dont need to implement an If statement

}

bool insertItem(tItemL d, tPosL p, tList *l)
{
    int i;//Creates the variable i to be used on the loops

    if( l->lastPos == MAX-1 ){//if the last position of the array is the last possible position(MAX-1) the item cannot be inserted. The function returns false

        return false;

    }

    else{

        l->lastPos++;

        if( p == LNULL ){  //The item is inserted at the end

            l->data[l->lastPos] = d;

        }
        else
        {
            for(i = l->lastPos; i>=p+1; i--)
                /*Moves all the elements from the position to be inserted 1 spot to the right*/
                l->data[i] = l->data[i-1];

            l->data[p]=d;//inserts the element in the position specified
        }

        return true;
    }

}

void deleteAtPosition(tPosL p, tList *l){

    tPosL i;

    l->lastPos--;

    /*Moves every element 1 spot to the left until overwriting the element we want to delete*/
    for ( i = p; i <= l->lastPos ; i++ ) {

        l->data[i] = l->data[i+1];

    }
}

tItemL getItem(tPosL p, tList l){
    //Returns the item in the p position

    return l.data[p];

}

void updateItem(tItemL i, tPosL p, tList *l){
    //changes the item of the position p by the item d

    l -> data[p]=i;

}

tPosL findItem(tNickname nick, tList l){
    //Searches for a nickname in the list and returns it position. If the item is not in the list, returns LNULL

    tPosL p;//Creates the variable p to be used on the for loop

    if (l.lastPos == LNULL){

        return LNULL; //If the list is empty, it returns LNULL

    } else{

        /*The loop goes over each element of the list, comparing the
          nickname to be searched and the nick of the item in each element*/
        for ( p = 0;  (p <= l.lastPos); p++ ) {

            if ( strcmp(l.data[p].nickname,nick) == 0 ){

                return p;//If the nickname is found, it returns it position

            }
        } return LNULL;//If the nickname is not found, it returns LNULL

    }
}
