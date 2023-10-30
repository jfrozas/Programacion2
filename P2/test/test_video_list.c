#include <stdio.h>
#include <string.h>

#include "../video_list.h"

void print_list(tVideoList list) {
    tVideoPos pos;
    tVideoItem item;

    printf("(");
    if (!isEmptyListV(list)) {
        pos = firstV(list);
        while (pos != NULL_VIDEO) {
            item = getItemV(pos, list);
            printf(" %s playTime %d", item.titleVideo, item.playTime);
            pos = nextV(pos, list);
        }
    }
    printf(")\n");
}

int main() {
    tVideoList list;
    tVideoPos pos;
    tVideoItem item1, item2;

    /* init */
    item1.playTime = 0;


    /* create */
    createEmptyListV(&list);
    print_list(list);


    /* insert */
    strcpy(item1.titleVideo, "video3");
    insertItemV(item1, NULL_VIDEO, &list);
    print_list(list);

    strcpy(item1.titleVideo, "video1");
    insertItemV(item1, firstV(list), &list);
    print_list(list);

    strcpy(item1.titleVideo, "video5");
    insertItemV(item1, NULL_VIDEO, &list);
    print_list(list);

    strcpy(item1.titleVideo, "video2");
    insertItemV(item1, nextV(firstV(list), list), &list);
    print_list(list);

    strcpy(item1.titleVideo, "video4");
    insertItemV(item1, lastV(list), &list);
    print_list(list);


    /* find */
    pos = findItemV("video33", list);
    if (pos == NULL_VIDEO) {
        printf("video33 Not found\n");
    }

    pos = findItemV("video3", list);
    item2 = getItemV(pos, list);
    printf("%s found\n", item2.titleVideo);


    /* update */
    item2.playTime = 100;
    updateItemV(item2, pos, &list);
    item2 = getItemV(pos, list);
    printf("%s updated playTime %d\n", item2.titleVideo, item2.playTime);
    print_list(list);


    /* remove */
    deleteAtPositionV(nextV(firstV(list),list), &list);
    print_list(list);

    deleteAtPositionV(previousV(lastV(list),list), &list);
    print_list(list);

    deleteAtPositionV(firstV(list),&list);
    print_list(list);

    deleteAtPositionV(lastV(list),&list);
    print_list(list);

    deleteAtPositionV(firstV(list),&list);
    print_list(list);

    insertItemV(item1, NULL_VIDEO, &list);
    print_list(list);

}
