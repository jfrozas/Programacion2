/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Guillermo Fernandez Sanchez LOGIN 1: guillermo.fernandezs
 * AUTHOR 2: Javier Fernandez Rozas      LOGIN 2: j.frozas
 * GROUP: 6.1
 * DATE: 31 / 03 / 21
 */
#define LNULL NULL


#include "dynamic_list.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


void createEmptyList(tList *l){
    /* Creating a list*/

    /*Empty list => no nodes, so l points to a NULL node*/
    *l = LNULL;
}


bool createNode(tPosL * p){
    /*Auxiliary operation to Insert Item*/

    *p = malloc(sizeof(struct tNode));
    /*Takes a position by reference*/

    return *p != LNULL;
    /*returns wether the malloc returns LNULL or not*/
    /*Just for operations that need to create nodes, such insertItem,
      so that we just call createNode to see if its true or false*/
}


bool isEmptyList(tList l){

    //checks if the list is empty (if the list points to NULL)
    return (l == LNULL);
}


tPosL first(tList l){

    //returns the first position of a list
    return l;
}


tPosL last(tList l){

    tPosL p;
    //variable created to find the last element of the list
    for ( p=l; p->next != LNULL ; p = p->next );
    // makes a loop til the next node is Null, and returns the node before (the last one)

    return p;
}


tPosL next(tPosL p, tList l){

    //Gives the next position of p
    return p->next;
}


tPosL previous(tPosL p, tList l){
    //returns the previous position to the one inserted

    tPosL q;
    //variable created to return a previous position from a given one
    if ( p == l)
        return LNULL;
        //we check if its the first one (because if it is, the previous is Null)
    else
    {
        for (q=l ; q->next != p ; q = q->next) ;
        //goes through the list until he finds the previous node to p, and returns it
        return q;
    }
}


bool insertItem(tItemL d, tPosL p, tList *l){
    /*Inserting an item*/


    tPosL n, r;//Creates variables of type tPosL to be used on the loops

    /*Exceptional case: no memory*/
    if ( !createNode(&n) )
        return false;
    else
    {
        /* There is enough memory. n = new node*/
        n->data = d;
        n->next = NULL;


        if ( *l == LNULL ){ /* l is an empty list*/

            *l = n;

        }

        else if ( p == LNULL ) /* Position given is NULL -> Insert at the end */
        {
            for ( r = *l ; r->next != LNULL ; r = r->next ) ;
            /*We set r to pint the first node, we see if its NULL or not
              ,if there is a next node, we point r to there, and repeat*/
            r->next = n;
            /*When we get to the last node, we link n*/

        }

        else if ( p == *l ) /*Insert at the beginning*/
        {
            n->next = p;
            // we make the newt of n p
            *l = n;
            //we make that n is at the beggining of the list
        }

        else /*Insert at an intermediate position*/
        {
            n->data = p->data;
            p->data = d;
            n->next = p->next;
            p->next = n;
            //we insert it by inserting a new node, that will be in the middle of two positions,
            //making the first one to point to the new node, and the second one to point to the next node
        }

        return true;

    }

}


void deleteAtPosition(tPosL p, tList *l){
    //Deletes a position of the list

    tPosL q; /*auxiliary variable created to perform the operations of deleting the last element,
               and for the operationsthat deletes an intermediate positions*/

    if ( p == *l )
        *l = p->next;
        //makes the pointer to point the next element

    else if ( p->next == LNULL ){
        //delete last element

        for (q = *l ; q->next != p ; q = q->next);
        //q is the previous node to p

        //we make  the next node to q (p) Null
        q->next = LNULL;

    }

    else{  //delete intermediate position



        q = p->next; //q is the next node to p

        p->data = q->data; // we pass the q data to p

        p->next = q->next; //the pointer p will face the same as the pointer of q (the same position)

        p = q; //As p = q, the position p is deleted


    }

    free(p);

}


tItemL getItem(tPosL p, tList l){

    //get the data of an especific position
    return p ->data;
}


void updateItem(tItemL d, tPosL p, tList *l){
    /*store the item at a position p of a list*/

    //makes the item d the new data of the position p
    p -> data = d;

}


tPosL findItem(tNickname d, tList l){
    //finding an specific item on the list

    tPosL p;//variable created to perform a loop to find items

    //compares the item searched with the nodes of the list, this being NULL or with and strcmp
    for ( p=l ; (p != LNULL) && (strcmp(p -> data.nickname, d)!=0) ; p=p->next);


    //returns if it finds the item
    return p;
}











