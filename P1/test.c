#include <stdio.h>
#include <string.h>

#ifdef STATIC_LIST
#include "static_list.h"
#endif
#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef TEST_LIST
#include "list/list.h"
#endif

void print_list(tList list) {
    tPosL pos;
    tItemL item;

    printf("(");
    if (!isEmptyList(list)) {
        pos = first(list);
        while (pos != LNULL) {
            item = getItem(pos, list);
            printf(" %s numPlay %d", item.nickname, item.numPlay);
            pos = next(pos, list);
        }
    }
    printf(")\n");
}

int main() {
    tList list;
    tPosL pos;
    tItemL item1, item2;

    /* init */
    item1.numPlay = 0;


    /* create */
    createEmptyList(&list);
    print_list(list);


    /* insert */
    strcpy(item1.nickname, "nick3");
    insertItem(item1, LNULL, &list);
    print_list(list);

    strcpy(item1.nickname, "nick1");
    insertItem(item1, first(list), &list);
    print_list(list);

    strcpy(item1.nickname, "nick5");
    insertItem(item1, LNULL, &list);
    print_list(list);

    strcpy(item1.nickname, "nick2");
    insertItem(item1, next(first(list),list), &list);
    print_list(list);

    strcpy(item1.nickname, "nick4");
    insertItem(item1, last(list), &list);
    print_list(list);


    /* find */
    pos = findItem("nick33", list);
    if (pos == LNULL) {
        printf("nick33 Not found\n");
    }

    pos = findItem("nick3", list);
    item2 = getItem(pos, list);
    printf("%s found\n", item2.nickname);


    /* update */
    item2.numPlay = 100;
    updateItem(item2, pos, &list);
    item2 = getItem(pos, list);
    printf("%s updated numPlay %d\n", item2.nickname, item2.numPlay);
    print_list(list);


    /* remove */
    deleteAtPosition(next(first(list),list), &list);
    print_list(list);

    deleteAtPosition(previous(last(list),list), &list);
    print_list(list);

    deleteAtPosition(first(list),&list);
    print_list(list);

    deleteAtPosition(last(list),&list);
    print_list(list);

    deleteAtPosition(first(list),&list);
    print_list(list);

    insertItem(item1, LNULL, &list);
    print_list(list);

}
