/*Author: NIPUN MITTAL (NBTG14450)*/

#include <stdio.h>
#include <stdlib.h>
#include "login.c"   //component included for login secruity to maintain privacy
#include "journal.c" //component included to access and function on daily journal
#include "slam_home.c" //component included to access and function on the slam book having friends' details
#include "todo.c" //component included to access and function your current to-do list

void (* functionality[4])() = {login_system,journal_main,slam_main,todo_main}; //array of pointers to function for easy access to functions in different components

void main(){

    printf("Please login/sign up to verify identity and access your UrBook!!\n");
    (*functionality[0])();

    int GOTO;
    
    /*Menu for the application*/
    urbookhome: printf("\n***********************************************\n"
    "           Welcome to UrBook Homepage\n"
    "\n***********************************************\n"
    "Please refer to the code and functionality table below as per convenience\n"
    "Code\tFunctionality\n"
    " 1. \tAccess your daily journal\n"
    " 2. \tAccess your slam book\n"
    " 3. \tAccess your to-do list\n"
    " 4. \tExit from application\n\n");
    printf("Enter the code: ");
    scanf("%d",&GOTO);
    getchar();

    switch (GOTO)
    {
    case 1 ... 3:

        (*functionality[GOTO])(); //call the function as per demand by the user from the respective component
        goto urbookhome;

    case 4: //case to exit

        printf("Thank You for using UrBook!!\nYour data is safely stored!!\nNow exiting the application...\n...\n...\n\n");
        break;
        goto exited; //goto getchar to not close prompt
    
    default:
        printf("\nEnter a valid code please!!\n");
        goto urbookhome;
    }
    
    exited: getchar(); 

}