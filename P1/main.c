/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Guillermo Fernandez Sanchez LOGIN 1: guillermo.fernandezs
 * AUTHOR 2: Javier Fernandez Rozas      LOGIN 2: j.frozas
 * GROUP: 6.1
 * DATE: 31 / 03 / 21
 */

#include <stdio.h>
#include <string.h>
#include "types.h"

#define MAX_BUFFER 255

#ifdef STATIC_LIST
#include "static_list.h"
#endif
#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef TEST_LIST
#include "list/list.h"
#endif



bool newUser(char *param1, char *param2, tList *list){
    /*
     Goal: Creates a new user and inserts it in the list
     Inputs: param1: Name of the user to be added to the list; Type char
             param2: Type of user: standard or premium user. Type char
             list: List where the user is being added to. Type tList
     Output: A Boolean value to check if the operation was a success
             The list, with the new user if the username inserted was not already in the list.
     Precondition: The list is initialized
    */


    /*searches for the user to check if it is already in the list, if there is an user
     with that nickname the new user will not be added and the function returns false*/
    if ( findItem(param1,*list) != LNULL ){
        return false;
    } else{

        tItemL tempItem; //Creation of a temporal item to insert the elements and later it is added to the list

        strcpy(tempItem.nickname, param1);//copy the param1 to the nickname of the temporal item

        tempItem.numPlay=0;//initializes the plays of the users to 0


        //compares the param2 to obtain que category of the user
        if ( strcmp(param2,"standard") == 0 ){

            tempItem.userCategory=standard;
        }
        else if ( strcmp(param2,"premium") == 0 ){

            tempItem.userCategory=premium;
        }
        else return false;

        //inserts the item into the list, if it fails, it returns false
        if ( insertItem(tempItem,LNULL,list) ){

            return true;

        }

        else return false;
    }
}



const char* getCategoryName(tUserCategory category){
    /*
    Goal: Return, as a string, the name of the tUserCategory introduced
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



int UsersNum(tUserCategory category, tList list){
    /*
    Goal: Counting the number of users in a category
    Input: Category: type tUserCategory; The category which users we want to count
           list: List where we want to count the users. Type tList
    Output: The number of users in the category specified. Type int
    Precondition: The category is valid and the list is initialized
     */

    tPosL pos; //Creates a variable of the type tPosL to use on the loop
    tItemL item; //creates an item which will be used to store the item in each iteration
    int num = 0; //Creates a variable for the number of users and it is initialized to 0

    pos = first(list);

    /*This loop goes around the list, in each iteration checks if the users belongs to the category
      inserted and if it is the case, it sums 1 user to the total*/
    while ( pos != LNULL ) {

        item = getItem(pos, list);

        if (item.userCategory==category){
            num++;
        }

        pos = next(pos, list);
    }

    return num;

}



int PlaysNum(tUserCategory category, tList list){
    /*
    Goal: Counting the total number of plays of the users in a category
    Input: category: The category which user's plays we want to count. Type tUserCategory
           list: List where we want to count the plays. Type tList
    Output: The total number of plays of the users in the category specified. Type int
    Precondition: The category is valid and the list is initialized*/


    tPosL pos; //Creates a variable of the type tPosL to use on the loop
    tItemL item; //creates an item which will be used to store the item in each iteration
    tNumPlay num = 0;//Creates a variable for the number of plays and it is initialized to 0


    pos = first(list);

    /*This loop goes around the list, in each iteration checks if the users belongs to the category
      inserted and if it is the case, it sums 1 play to the total*/
    while ( pos != LNULL ) {

        item = getItem(pos, list);

        if ( item.userCategory == category ){
            num+=item.numPlay;
        }

        pos = next(pos, list);
    }

    return num;

}



double average(tUserCategory category, tList list){
    /*
    Goal: Calculates the average number of plays per user of a category
    Input: The category which average of plays is wanted. Type tUserCategory
           list: List which we want the average from. Type tList
    Output: The average of plays of the users from the category specified. Type int
    Precondition: The category is valid and the list is initialized*/

    /* if the number of users or the number of plays is equal to 0, returns 0 to avoid indeterminations */
    if ( UsersNum(category,list) == 0 || PlaysNum(category,list) == 0 ) return 0;

    double a = PlaysNum(category,list);
    double b = UsersNum(category,list);

    return a/b;//Returns the average

}



bool stats(tList list){
    /*
    Goal: Printing the list of the current VIMFIC users and their data
    Input: list: list where the data wanted to be printed is stored. Type tList
    Output: Boolean value to check if the operation was successful. Type bool
    Precondition: The list is initialized.
    Postcondition: The list of current users is printed*/

    tPosL pos; //Creates a variable which is used on the loop
    tItemL item;//Creates an item to store and print the item in each iteration

    if (isEmptyList(list)){

        return false;

    } else if ( !isEmptyList(list) ) {

            pos = first(list);

            /*The loop goes all over the list (until the position is LNULL) and prints the list*/
            while (pos != LNULL) {

                item = getItem(pos, list); //stores the item into the variable to be able to print its elements

                printf("Nick %s category %s numplays %d\n", item.nickname,getCategoryName(item.userCategory), item.numPlay);

                pos = next(pos, list);

            }

            printf("Category   Users  Plays  Average\n");
            printf("Standard    %d     %d     %.2f\n",UsersNum(standard,list),PlaysNum(standard,list),average(standard,list));
            printf("Premium     %d     %d     %.2f\n",UsersNum(premium,list),PlaysNum(premium,list),average(premium,list));

            return true;

    }

    return false;

}



bool deleteUser(tNickname nickname, tList *list){

    /*
    Goal: Deleting an user from the list
    Input: nickname: the name of the user to be deleted. Type tNickname
           list: List where the user is stored. Type tList
    Output: A boleean value to check if the operation was a success. Type bool
            The list with the user deleted. Type tList
    Precondition: The list is initialized.*/

    tPosL pos;//Creates a variable to store the position where the user with the nickname inserted it located
    tItemL item;//creates an item to be able to print its elements

    /*If the list is empty or the user is not in the list, the operation cannot proceed, therefore it returns false*/
    if( (isEmptyList(*list)) || (findItem(nickname, *list) == LNULL ) ){

        return false;

    } else{

        pos = findItem(nickname, *list);
        item = getItem(pos, *list);

        printf("* Delete: nick %s category %s numplays %d\n",item.nickname,getCategoryName(item.userCategory),item.numPlay);

        deleteAtPosition(pos, list);/*Deletes the item in the position got when finding the nickname of the user*/

        return true;

    }

}



bool playVid(tNickname nickname,tTitleVideo video,tList *list){

    /*
    Goal: Adding a play to the user’s data
    Input: nickname: name of the user who plays the video. Type tNickname
           video: name of the video to be played. Type char
           list: List where that user is stored. Type tList
    Output: A Boolean value to check if the operation was successful
            The new list with the play added to the user. Type tList
    Precondition: The list is initialized
     */


    /*Creates a variable tPosL and tItemL to get a temporal item, edit it and update it on the list*/
    tPosL pos;
    tItemL item;

    if ( isEmptyList(*list) || (findItem(nickname, *list) == LNULL )){

        return false;

    } else {

        pos = findItem(nickname, *list);
        item = getItem(pos, *list);

        item.numPlay++;//Adds 1 play to the total of plays of the user

        updateItem(item, pos, list);//Updates the data of the user in the list

        printf("* Play: nick %s plays video %s numplays %d\n",nickname,video,item.numPlay);

        return true;

    }

}



void processCommand(char *commandNumber, char command, char *param1, char *param2, tList *list) {


    printf("********************\n");

    switch(command) {

        /*COMMAND N (New)*/
        case 'N': {

            printf("%s %c: nick %s category %s\n", commandNumber, command, param1, param2);


            /*If the newUser function fails, it prints the error message*/
            if ( newUser(param1,param2,list) ){

                printf("* New: nick %s category %s\n",param1, param2);

            } else {

                printf("+ Error: New not possible\n");

            }
            break;
        }

        /*COMMAND D (Delete)*/
        case 'D': {


            printf("%s %c: nick %s\n", commandNumber, command, param1);

            /*If the deleteUser function fails, it prints the error message*/
            if ( deleteUser(param1,list) ){

            }else {

                printf("+ Error: Delete not possible\n");

            }
            break;
        }

        /*COMMAND P (Play)*/
        case 'P': {

            printf("%s %c: nick %s video %s\n", commandNumber, command, param1, param2);

            /*If the PlayVid function fails, it prints the error message*/
            if ( playVid(param1,param2,list) ){

            } else {

                printf("+ Error: Play not possible\n");

            }
            break;
        }

        /*COMMAND S (Stats)*/
        case 'S': {

            printf("%s %c\n", commandNumber, command);

            /*If the stats function fails, it prints the error message*/
            if ( stats(*list) ){

            }else {

                printf("+ Error: Stats not possible\n");

            }
            break;
        }


        default: break;


    }
}



void readTasks(char *filename) {
    FILE *df;
    char *commandNumber, *command, *param1, *param2;

    /*A new list is created and initialized*/
    tList list;
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
            processCommand(commandNumber, command[0], param1, param2, &list);
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






