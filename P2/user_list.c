/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Guillermo Fernandez Sanchez LOGIN 1: guillermo.fernandezs
 * AUTHOR 2: Javier Fernandez Rozas      LOGIN 2: j.frozas
 * GROUP: 6.1
 * DATE: 04 / 05 / 21
 */


#include "user_list.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


void createEmptyList(tUserList *l){

    /* Creating a list*/

    /*Empty list => no nodes, so l points to a NULL node*/
    *l = NULL_USER;
}


bool createNode(tUserPos * p){
    /*
    Goal: Asigning memory space and creates a node
    Input: The position where the node is going to be created. Type tUserPos
    Output: Boolean value and the node created if boolean value is true
    */


    *p = malloc(sizeof(struct tNode));
    /*Takes a position by reference*/

    return *p != NULL_USER;
    /*returns wether the malloc returns NULL_USER or not*/
    /*Just for operations that need to create nodes, such insertItem,
      so that we just call createNode to see if its true or false*/
}


bool isEmptyList(tUserList l){

    //checks if the list is empty (if the list points to NULL)
    return (l == NULL_USER);
}


tUserPos first(tUserList l){

    //returns the first position of a list
    return l;
}


tUserPos last(tUserList l){

    tUserPos p;
    //variable created to find the last element of the list
    for ( p=l; p->next != NULL_USER ; p = p->next );
    // makes a loop til the next node is NULL_USER, and returns the node before (the last one)

    return p;
}


tUserPos next(tUserPos p, tUserList l){
    //Gives the next position of p

    return p->next;
}


tUserPos previous(tUserPos p, tUserList l){
    //returns the previous position to the one inserted

    tUserPos q;
    //variable created to return a previous position from a given one
    if ( p == l)
        return NULL_USER;
        //we check if its the first one (because if it is, the previous is NULL)
    else
    {
        for (q=l ; q->next != p ; q = q->next) ;
        //goes through the list until he finds the previous node to p, and returns it
        return q;
    }
}

tUserPos findUserPosition (tUserItem d, tUserList l){
    /*
    Goal: Finding the position where the user should be positioned alphabetically
    Input: d: The user item whose ideal position is wanted to find. Type tUserItem
           l: The list where the user will be inserted. Type tUserList
    Output: The position p where the user should be located alphabetically
    Precondition: the list is initialized and the list is not empty
    */




    tUserPos p; //creates a variable tUserPos to be used in a loop
    p=l;

    while (( p->next != NULL_USER ) && (strcmp(p->next->data.nickname,d.nickname)<0) ){
        p = p->next; //loops until it gets to the right position alphabetically or the to the end of the list
    }
    return p;

}

bool insertItem(tUserItem d, tUserList *l){
    /*Inserting an item*/


    tUserPos n, p;

    /*Exceptional case: no memory*/
    if ( !createNode(&n) )
        return false;
    else
    {
        /* There is enough memory. n = new node*/
        n->data = d;
        n->next = NULL;

        if ( *l == NULL_USER ){ /* l is an empty list*/
            *l = n;

        } else if ( strcmp(d.nickname,(*l)->data.nickname)<0 ){ //Insert the item at the beginning
            n->next= *l;
            *l = n;

        } else { //Insert the item at the middle or at the end

            p=findUserPosition(d,*l);
            n->next= p->next;
            p->next=n;
        }

        return true;

    }

}


void deleteAtPosition(tUserPos p, tUserList *l){
    //Deletes a position of the list

    tUserPos q; /*auxiliary variable created to perform the operations of deleting the last element,
               and for the operations that deletes an intermediate positions*/

    if ( p == *l )
        *l = p->next;
        //makes the pointer to point the next element

    else if ( p->next == NULL_USER ){
        //delete last element

        for (q = *l ; q->next != p ; q = q->next);
        //q is the previous node to p

        //we make  the next node to q (p) Null
        q->next = NULL_USER;

    }

    else{  //delete intermediate position



        q = p->next; //q is the next node to p

        p->data = q->data; // we pass the q data to p

        p->next = q->next; //the pointer p will face the same as the pointer of q (the same position)

        p = q; //As p = q, the position p is deleted


    }

    free(p); //Frees the memory reserved no that node

}


tUserItem getItem(tUserPos p, tUserList l){

    //get the data of an especific position
    return p ->data;
}


void updateItem(tUserItem d, tUserPos p, tUserList *l){
    /*store the item at a position p of a list*/

    //makes the item d the new data of the position p
    p -> data = d;

}


tUserPos findItem(tNickname d, tUserList l){
    //finding an specific item on the list

    tUserPos p; //variable created to perform a loop to find items

    //compares the item searched with the nodes of the list, this being NULL or with and strcmp
    for ( p=l ; (p != NULL_USER) && (strcmp(p -> data.nickname, d)<0) ; p=p->next);

    if ((p!=NULL_USER) && (strcmp(p -> data.nickname, d)==0)) {

        return p; //returns the position of the item if it is found
    }
    else{
        return NULL_USER; //If the user is not found, it returns NULL
    }
}
