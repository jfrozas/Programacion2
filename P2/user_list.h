/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Guillermo Fernandez Sanchez LOGIN 1: guillermo.fernandezs
 * AUTHOR 2: Javier Fernandez Rozas      LOGIN 2: j.frozas
 * GROUP: 6.1
 * DATE: 04 / 05 / 21
 */

#ifndef P2_USER_LIST_H
#define P2_USER_LIST_H
#define NULL_USER NULL

#include "types.h"
#include "video_list.h"
#include <stdbool.h>

typedef struct tNode * tUserPos;

typedef struct tUserItem{ //Item with the data of the user
    tNickname nickname;
    tPlayTime totalPlayTime;
    tUserCategory userCategory;
    tVideoList videoList;
} tUserItem;

struct tNode{ // Node of the list, containing the item and the pointer to the next position
    tUserItem data;
    tUserPos next;
};

typedef tUserPos tUserList; //Declaration of the list


/*Functions*/
void createEmptyList (tUserList *);
bool isEmptyList(tUserList);
tUserPos first(tUserList);
tUserPos last(tUserList);
tUserPos next(tUserPos, tUserList);
tUserPos previous(tUserPos, tUserList);
bool insertItem(tUserItem, tUserList*);
void deleteAtPosition(tUserPos, tUserList*);
tUserItem getItem(tUserPos, tUserList);
void updateItem(tUserItem, tUserPos, tUserList*);
tUserPos findItem(tNickname, tUserList);

#endif