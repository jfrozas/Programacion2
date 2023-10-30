#ifndef PRO2_2021_P1_TYPES_H
#define PRO2_2021_P1_TYPES_H

#define NAME_LENGTH_LIMIT 20


typedef char tNickname[NAME_LENGTH_LIMIT];
typedef enum {standard, premium} tUserCategory;
typedef int tNumPlay;
typedef struct tItemL {
    tNickname nickname ;
    tNumPlay numPlay;
    tUserCategory userCategory;
} tItemL;
typedef char tTitleVideo[NAME_LENGTH_LIMIT];
typedef struct tVideo {
    tTitleVideo titleVideo;
} tVideo;


#endif //PRO2_2021_P1_TYPES_H
