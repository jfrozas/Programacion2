/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Guillermo Fernandez Sanchez LOGIN 1: guillermo.fernandezs
 * AUTHOR 2: Javier Fernandez Rozas      LOGIN 2: j.frozas
 * GROUP: 6.1
 * DATE: 04 / 05 / 21
 */

#ifndef P2_VIDEO_LIST_H
#define P2_VIDEO_LIST_H

#define NULL_VIDEO (-1)
#define MAX 25

#include <stdbool.h>
#include "types.h"


typedef int tVideoPos;

typedef tVideo tVideoItem;

typedef struct tVideoList{ //Item of the video
    tVideoItem  data[MAX];
    tVideoPos lastPos;
} tVideoList;


/* Functions */

void createEmptyListV (tVideoList*);
bool isEmptyListV(tVideoList);
tVideoPos firstV(tVideoList);
tVideoPos lastV(tVideoList);
tVideoPos nextV(tVideoPos, tVideoList);
tVideoPos previousV(tVideoPos, tVideoList);
bool insertItemV(tVideoItem, tVideoPos, tVideoList*);
void deleteAtPositionV(tVideoPos, tVideoList*);
tVideoItem getItemV(tVideoPos, tVideoList);
void updateItemV(tVideoItem, tVideoPos, tVideoList*);
tVideoPos findItemV(tNickname, tVideoList);


#endif //P2_VIDEO_LIST_H

