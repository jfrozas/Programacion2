/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Guillermo Fernandez Sanchez LOGIN 1: guillermo.fernandezs
 * AUTHOR 2: Javier Fernandez Rozas      LOGIN 2: j.frozas
 * GROUP: 6.1
 * DATE: 04 / 05 / 21
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "video_list.h"
#include "user_list.h"

#define MAX_BUFFER 255


/*     AUXILIARY FUNCTIONS     */


const char* getCategoryName(tUserCategory category){
    /*
    Goal: Returning, as a string, the name of the tUserCategory introduced
    Input: category: category of the user: standard or premium. Type tUserCategory
    Output: A string with the name of the category: Type char
    Precondition: The category introduced is valid
     */

    /*returns the name of the category as a string */
    switch ( category ) {

        case standard: return "standard";

        case premium: return "premium";

        default: break;
    }
}


double average(tPlayTime userTimeplay, int userNum){
    /*
    Goal: Calculates the average number of play time per user of a category
    Input: userTimeplay: The total playtime of the users of a category. type tPlayTime
           userNum: Number of users from a category. type int
    Output: The average of plays of the users from the category specified. Type double
    Precondition: The category is valid and the list is initialized
    */

    /* If the number of users or the number of plays is equal to 0, returns 0 to avoid indeterminations */
    if ( userTimeplay == 0 || userNum == 0 ) return 0;

    double a=userTimeplay;
    double b=userNum;

    return a/b; //Returns the average

}


bool printVideos(tVideoList videoList){
    /*
     Goal: Printing the list of videos
     Inputs: videoList: the list of videos to be printed. Type tVideoList
     Output: Boolean value which is false if the list is empty since no videos can be printed, otherwise it's true
     Precondition: The video list is initialized
    */

    /*Creates two variables, one of type tVideoPos, to store the video position on each iteration, and a tVideoItem,
      to store the item to be printed in each iteration*/
    tVideoPos pos;
    tVideoItem videoItem;



    if(isEmptyListV(videoList)){ //If the video list is empty, it returns false, since there are no videos to print

        return false;

    } else{

        pos = firstV(videoList);
        /*The loop goes all over the list (until the position is NULL_VIDEO) and prints the list*/
        while (pos != NULL_VIDEO) {

            videoItem = getItemV(pos, videoList); //stores the item into the variable to be able to print its elements

            printf("Video %s playtime %d\n",videoItem.titleVideo, videoItem.playTime);


            pos = nextV(pos, videoList);

        }
        return true;
    }

}


void deleteVideoList(tUserPos userPos, tUserList userList){
    /*
     Goal: Deleting the list of videos of an user.
     Inputs: userPos: position of the user which video list is wanted to be deleted.
             userlist: User list where the user is stored. Type tUserList.
     Output: The video list is deleted
     Precondition: the video list is initialized and the user position belongs to a valid user item
    */


    /*Creates a temporal item of the user which video list is going to be deleted*/
    tUserItem userItem;
    userItem= getItem(userPos,userList);

    // The last video of the list is deleted until there are no more videos to delete
    while (!isEmptyListV( userItem.videoList )){

        deleteAtPositionV(lastV(userItem.videoList), &userItem.videoList);

    }

    //The user on the list is updated with the same user but with no videos on its video list
    updateItem(userItem, userPos, &userList);


}



 /*     MAIN FUNCTIONS     */



bool newUser(tNickname nickname, char *category, tUserList *userList){
    /*
     Goal: Creates a new user and inserts it in the list
     Inputs: nickname: nick of the user to be added to the list. Type tNickname
             category: type of user: standard or premium user. Type char
             list: User List where the user is being added to. Type tUserList
     Output: A Boolean value to check if the operation was a success
             The list, with the new user if the username inserted was not already in the list.
     Precondition: The list is initialized
    */


    /*searches for the user to check if the nickname is already in the list, if there is an user
     with that nickname the new user will not be added and the function returns false*/
    if ( findItem(nickname,*userList) != NULL_USER ){

        return false;

    } else{

        tUserItem tempItem;   //Creation of a temporal item to insert the elements and later it is added to the list

        /*Copies the nickname to the field on the temporal item and initializes the playtime of the user to 0*/
        strcpy(tempItem.nickname, nickname);
        tempItem.totalPlayTime=0;

        createEmptyListV(&tempItem.videoList); //Initializes the list of videos to an empty list

        //Compares the string category to obtain que category of the user as a tUserCategory type variable
        if ( strcmp(category,"standard") == 0 ){

            tempItem.userCategory=standard;
        }
        else if ( strcmp(category,"premium") == 0 ){

            tempItem.userCategory=premium;
        }
        else return false;

        //inserts the item into the list, if it fails, it returns false
        if ( insertItem(tempItem,userList) ) return true;
        else return false;
    }
}


bool deleteUser(tNickname nickname, tUserList *list){ //done
    /*
    Goal: Deleting an user from the list
    Input: nickname: the name of the user to be deleted. Type tNickname
           list: List where the user is stored. Type tUserList
    Output: A boleean value to check if the operation was a success. Type bool
            The list with the user deleted. Type tUserList
    Precondition: The list is initialized.
     */

    tUserPos userPos;//Creates a variable to store the position where the user with the nickname inserted it located
    tUserItem userItem;  //creates an item to be able to print its elements

    /*If the list is empty or the user is not in the list, the operation cannot proceed, therefore it returns false*/
    if( (isEmptyList(*list)) || (findItem(nickname, *list) == NULL_USER ) ){

        return false;

    } else{

        /* A temporal item is used to print the data of the user to be deleted */
        userPos = findItem(nickname, *list);
        userItem = getItem(userPos, *list);

        /* If the video list has items on it, they get deleted */
        if(!isEmptyListV(userItem.videoList)) deleteVideoList(userPos, *list);



        deleteAtPosition(userPos, list); //Deletes the user
        printf("* Delete: nick %s category %s totalplaytime %d\n",userItem.nickname,getCategoryName(userItem.userCategory),userItem.totalPlayTime);
        return true;



    }

}


bool addVideo(tNickname UserNickname, tTitleVideo VideoTitle, tUserList userList){
    /*
     Goal: Creates a new video item and inserts it to the video list of the user specified
     Inputs: UserNickname: nickname of the user in which list the video is going to be inserted. Type tNickname.
             VideoTitle: name of the video being added. Type tTitleVideo.
             userList: User list where the user item is stored. Type tUserList.
     Output: Boolean value to check if the operation was a success
             The user list with the video inserted to the user's video list
     Precondition: the user list is initialized
    */

    tUserPos UserPos;   // Position of the user in which video list we want to insert the video
    tUserItem UserItem; // Item to temporally store that user

    UserPos = findItem(UserNickname, userList); // Assign the position of the user to UserPos

    if (UserPos == NULL_USER) return false;     // If the user is not in the list, the function returns error

    UserItem = getItem(UserPos, userList);      // Storing the user in the temporal item

    /* If there is a video with the same name of the video to be inserted, the function returns false */
    if (findItemV(VideoTitle, UserItem.videoList) != NULL_VIDEO) return false;



    /*temporal video item to initialize the item to be inserted. Copies the title of the
      video to the title of the temporal item and initializes the video playTime to 0*/
    tVideoItem temp;
    strcpy(temp.titleVideo, VideoTitle);
    temp.playTime=0;


    /* Inserts the temporal video item to the list of the temporal user and updates the user list */
    if(insertItemV(temp, NULL_VIDEO, &UserItem.videoList)){

        updateItem(UserItem, UserPos, &userList);
        return true;

    } else return false;
}


bool PlayVid( tNickname nickname , tTitleVideo video, char* playtime,tUserList *list){
    /*
    Goal: Adding the specified playtime to the user's total playtime and to the video play time
    Input: nickname: name of the user who plays the video. Type tNickname
           video: name of the video to be played. Type tTitleVideo
           playtime: play time of the video. Type char
           list: List where that user is stored. Type tUserList
    Output: A Boolean value to check if the operation was successful
            The new list with the play added to the user. Type tList
    Precondition: The user list is initialized
     */


    /* Creates a variable tUserPos and tUserItem to get a temporal item, edit it and update it on the list */
    tUserPos UserPos;
    tUserItem UserItem;

    /* Creates a videoItem to check if the video is on the user's video list and adding the play to it */
    tVideoPos VideoPos;
    tVideoItem VideoItem;

    if ( isEmptyList(*list) || (findItem(nickname, *list) == NULL_USER)){

        return false;

    } else {

        UserPos = findItem(nickname, *list);
        UserItem = getItem(UserPos, *list);

        VideoPos = findItemV(video, UserItem.videoList); //looks up for the video on the user's video list

        /* If the video is not in the list, it returns false, since you can't play it */
        if(VideoPos==NULL_VIDEO) return false;

        VideoItem = getItemV(VideoPos, UserItem.videoList);

        /*Adds the playtime to the total play time of the user*/
        UserItem.totalPlayTime = UserItem.totalPlayTime + strtol(playtime,NULL, 0);
        /*Adds the playtime to the video play time of the user*/
        VideoItem.playTime = VideoItem.playTime + strtol(playtime,NULL, 0);


        updateItemV(VideoItem, VideoPos, &UserItem.videoList); //Updates the video item on the user's video list

        updateItem(UserItem, UserPos, list);                   //Updates the data of the user in the list

        printf("* Play: nick %s plays video %s playtime %s totalplaytime %d\n",nickname,video,playtime, UserItem.totalPlayTime);

        return true;

    }


}


bool stats(tUserList list){
    /*
    Goal: Printing the list of the current VIMFIC users and their data
    Input: list: list where the data wanted to be printed is stored. Type tUserList
    Output: Boolean value to check if the operation was successful. Type bool
    Precondition: The user list is initialized.
     */

    tUserPos pos;   //Creates a variable to be used on the loop
    tUserItem item; //Creates an user item to store and print the item in each iteration
    int premiumUsers=0, standardUsers=0;
    tPlayTime premiumTimeplay=0, standardTimeplay=0;

    if (isEmptyList(list)){

        return false;

    } else {

        pos = first(list);

        /*The loop goes all over the list (until the position is NULL_USER) and prints the list*/
        while (pos != NULL_USER) {

            item = getItem(pos, list); //stores the user item into the variable to be able to print its elements

            printf("*Nick %s category %s totalplaytime  %d\n", item.nickname,getCategoryName(item.userCategory), item.totalPlayTime);

            if(item.userCategory==standard){
                standardUsers++;
                standardTimeplay+=item.totalPlayTime;
            } else{
                premiumUsers++;
                premiumTimeplay+=item.totalPlayTime;
            }

            /*Calls the function printVideos to print the video list for the user,
              if the function returns false, prints the "No videos" message*/
            if(!printVideos(item.videoList)){
                printf("No videos\n");
            }

            pos = next(pos, list);

        }

        /* The number of users, their play time and the average for each category is printed */
        printf("Category  Users  TimePlay  Average\n");
        printf("Standard %6d %9d %8.2f\n",standardUsers,standardTimeplay,average(standardTimeplay,standardUsers));
        printf("Premium  %6d %9d %8.2f\n",premiumUsers,premiumTimeplay,average(premiumTimeplay,premiumUsers));

        return true;

    }

}


bool RemoveMaxtime(char* maxtime, tUserList *UserList){
    /*
     Goal: Deleting standard users whose total play time exceed the maxtime
     Inputs: maxtime: The maximum play time for an standard user. Type char
             Userlist: User list whose standard users that exceed the maxtime are wanted to be deleted. Type tUserList.
     Output: Boolean value to check if the operation was a success
             The user list without the standard users that exceeded the maxtime
     Precondition: the user list is initialized
    */

    /* Variables of type tUserPos and tUserItem are created to store an user in each iteration of the loop */
    tUserPos pos;
    tUserItem item;

    if(isEmptyList(*UserList)) return false; //If the list is empty, no users can be removed

    bool removed=false; // A variable of type bool is created to check if any user was removed

    /* A variable of type int is created to store the maximum play time as an integer */
    int maxtimeINT = strtol(maxtime,NULL, 0);


    pos = first(*UserList); //the position is initialized to the first one of the list

    /*The loop goes all over the list (until the position is NULL_USER) and if the totalPlayTime is larger
      than the maximum play time (maxtimeINT), the user gets deleted */
    while (pos != NULL_USER) {


        item = getItem(pos, *UserList); //stores the user item into the variable to be able to print its data

        if ((item.totalPlayTime > maxtimeINT) && (item.userCategory == standard)) {

            printf("Removing nick %s, totalplaytime %d\n", item.nickname, item.totalPlayTime);


            /* The item gets deleted, the procedure is similar to the one in deleteUser, first, the videolist is
              deleted if there is any video on it, then the user is deleted*/

            if (!isEmptyListV(item.videoList)) deleteVideoList(pos, *UserList);
            deleteAtPosition(pos, UserList);

            removed = true;    // removed is set to true because at least one user was removed



            if(isEmptyList(*UserList)) return removed; //If the list is empty there are no more


            /*If an user is removed, the loop goes back to the first position to avoid position errors*/
            pos=first(*UserList);

        }  else pos = next(pos, *UserList); //If no user was removed, the position points to the next node

    }
    return removed;
}



void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3,  tUserList *list) {

    printf("********************\n");

    switch(command) {

        /*COMMAND N (New)*/
        case 'N': {

            printf("%s %c: nick %s category %s\n", commandNumber, command, param1, param2);

            /*If the newUser function fails, it prints the error message*/
            if (newUser(param1,param2,list)) printf("* New: nick %s category %s\n",param1, param2);
            else printf("+ Error: New not possible\n");

            break;
        }

        /*COMMAND D (Delete)*/
        case 'D': {

            printf("%s %c: nick %s\n", commandNumber, command, param1);

            /*If the deleteUser function fails, it prints the error message*/
            if ( !deleteUser(param1,list) ) printf("+ Error: Delete not possible\n");

            break;
        }

        /*COMMAND A (Add)*/
        case 'A': {

            printf("%s %c: nick %s video %s\n", commandNumber, command, param1, param2);

            /*If the addVideo function fails, it prints the error message*/
            if (addVideo(param1,param2,*list)) printf("* Add: nick %s adds video %s\n",param1, param2);
            else printf("+ Error: Add not possible\n");

            break;
        }

        /*COMMAND P (Play)*/
        case 'P': {

            printf("%s %c: nick %s video %s minutes %s\n", commandNumber, command, param1, param2, param3);

            /*If the PlayVid function fails, it prints the error message*/
            if (!PlayVid(param1,param2, param3, list)) printf("+ Error: Play not possible\n");

            break;
        }

        /*COMMAND S (Stats)*/
        case 'S': {

            printf("%s %c\n", commandNumber, command);

            /*If the stats function fails, it prints the error message*/
            if (!stats(*list)) printf("+ Error: Stats not possible\n");

            break;
        }

        /*COMMAND R (Remove)*/
        case 'R': {

            printf("%s %c: maxtime %s\n", commandNumber, command, param1);

            /*If the RemoveMaxtime function fails, it prints the error message*/
            if (!RemoveMaxtime(param1, list)) printf("+ Error: Remove not possible\n");

            break;
        }


        default: break;
    }
}


void readTasks(char *filename) {
    FILE *df;
    char *commandNumber, *command, *param1, *param2, *param3;

    /*A new list is created and initialized to an empty list*/
    tUserList list;
    createEmptyList(&list);

    df = fopen(filename, "rb");
    if (df != NULL) {
        const char delimiters[] = " \n\r";
        char buffer[MAX_BUFFER];
        while (fgets(buffer, MAX_BUFFER, df)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);
            processCommand(commandNumber, command[0], param1, param2, param3, &list);
        }
        fclose(df);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}




int main(int nargs, char **args) {

    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name);

    return 0;
}
