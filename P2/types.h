/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Guillermo Fernandez Sanchez LOGIN 1: guillermo.fernandezs
 * AUTHOR 2: Javier Fernandez Rozas      LOGIN 2: j.frozas
 * GROUP: 6.1
 * DATE: 04 / 05 / 21
 */

#ifndef P2_TYPES_H
#define P2_TYPES_H

#define NAME_LENGTH_LIMIT 20


typedef char tNickname[NAME_LENGTH_LIMIT];
typedef enum {standard, premium} tUserCategory;
typedef int tPlayTime;

typedef char tTitleVideo[NAME_LENGTH_LIMIT];
typedef struct tVideo {
    tTitleVideo titleVideo;
    tPlayTime playTime;
} tVideo;

#endif //P2_TYPES_H
