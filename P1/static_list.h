/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Guillermo Fernandez Sanchez LOGIN 1: guillermo.fernandezs
 * AUTHOR 2: Javier Fernandez Rozas      LOGIN 2: j.frozas
 * GROUP: 6.1
 * DATE: 31 / 03 / 21
 */

#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include <stdbool.h>
#include "types.h"

#define LNULL -1
#define MAX 25

/* Write your code here... */
typedef int tPosL;

typedef struct {
    tItemL data[MAX];
    tPosL lastPos;
} tList;

/* funtion prototypes */

void createEmptyList (tList*);
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

#endif //STATIC_LIST_H