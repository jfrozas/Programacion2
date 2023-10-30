#include <stdio.h>
#include <string.h>

#include "../user_list.h"

void print_list(tUserList list) {
    tUserPos pos;
    tUserItem item;

    printf("(");
    if (!isEmptyList(list)) {
        pos = first(list);
        while (pos != NULL_USER) {
            item = getItem(pos, list);
            printf(" %s totalPlayTime %d", item.nickname, item.totalPlayTime);
            pos = next(pos, list);
        }
    }
    printf(")\n");
}

int main() {
    tUserList list;
    tUserPos pos;
    tUserItem item1, item2;

    /* init */
    item1.totalPlayTime = 0;


    /* create */
    createEmptyList(&list);
    print_list(list);


    /* insert */
    strcpy(item1.nickname, "nick3");
    insertItem(item1, &list);
    print_list(list);

    strcpy(item1.nickname, "nick1");
    insertItem(item1, &list);
    print_list(list);

    strcpy(item1.nickname, "nick5");
    insertItem(item1, &list);
    print_list(list);

    strcpy(item1.nickname, "nick2");
    insertItem(item1, &list);
    print_list(list);

    strcpy(item1.nickname, "nick4");
    insertItem(item1, &list);
    print_list(list);


    /* find */
    pos = findItem("nick33", list);
    if (pos == NULL_USER) {
        printf("nick33 Not found\n");
    }

    pos = findItem("nick3", list);
    item2 = getItem(pos, list);
    printf("%s found\n", item2.nickname);


    /* update */
    item2.totalPlayTime = 100;
    updateItem(item2, pos, &list);
    item2 = getItem(pos, list);
    printf("%s updated totalPlayTime %d\n", item2.nickname, item2.totalPlayTime);
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

    insertItem(item1, &list);
    print_list(list);

}


