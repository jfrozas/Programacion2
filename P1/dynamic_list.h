/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Guillermo Fernandez Sanchez LOGIN 1: guillermo.fernandezs
 * AUTHOR 2: Javier Fernandez Rozas      LOGIN 2: j.frozas
 * GROUP: 6.1
 * DATE: 31 / 03 / 21
 */

#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H
#define LNULL NULL

#include "types.h"
#include <stdbool.h>

typedef struct tNode * tPosL;
struct tNode
{
    tItemL data;
    tPosL next;
};
typedef tPosL tList;

/* function prototypes*/
void createEmptyList (tList *);
bool isEmptyList(tList);
tPosL first(tList);
tPosL last(tList);
tPosL next(tPosL, tList);
tPosL previous(tPosL, tList);
bool insertItem(tItemL, tPosL, tList*);
void deleteAtPosition(tPosL, tList*);
tItemL getItem(tPosL, tList);
void updateItem(tItemL, tPosL, tList*);
tPosL findItem(tNickname, tList);

#endif
