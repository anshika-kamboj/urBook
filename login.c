/*Author: AVIRAL JAIN (ECN14068)*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct login
{
    char username[30];
    char password[20];
};
void login_system();
void login();
void registration();
void updation();
void login_system()
{
    int option;
    printf("1. Register (For First Time Users Only)\n");
    printf("2. Login\n");
    printf("3. Update your Credentials\n");
    printf("Enter your choice:");
    scanf("%d",&option);
    getchar();
    if(option == 1)
        {
            registration();
        }
    else if(option == 2)
        {
            login();
        }
    else if(option == 3)
        {
            updation();
        }
}
// function for login 
void login()
{
    char username[30],password[20];
    FILE *log;
    log = fopen("login.txt","r");
    if (log == NULL)
    {
        fputs("Error at opening File!", stderr);
        exit(1);
    }
    struct login l;
    printf("\nPlease Enter your login credentials below\n\n");
    printf("Username:\n");
    scanf("%s",username);
    getchar();
    printf("\nPassword:\n");
    scanf("%s",password);
    getchar();
    while(fread(&l,sizeof(l),1,log))
        {
        if(strcmp(username,l.username)==0 && strcmp(password,l.password)==0)
            {   
                printf("\nSuccessful Login\n\n");
            }
        else 
            {
                printf("\nIncorrect Login Details\nPlease enter the correct credentials\n");
                login();
            }
        }
    fclose(log);
    return;
}
// function for registering the credentials
void registration()
{
    FILE *log;
    log=fopen("login.txt","w");
    if (log == NULL)
    {
        fputs("Error at opening File!", stderr);
        exit(1);
    }
    struct login l;
    printf("Welcome to UrBook. Please choose a username and password as credentials for system login.\nEnsure the username is no more than 30 characters long.\nEnsure your password is at least 8 characters long and contains lowercase, uppercase, numerical and special character values.\n"); 
    printf("\nEnter Username:\n");
    scanf("%s",l.username);
    printf("\nEnter Password:\n");
    scanf("%s",l.password);
    fwrite(&l,sizeof(l),1,log);
    fclose(log);
    printf("\nRegistration Successful!\n");
    login();
}
// function to update the credentials of the user
void updation()
{
    char username[30],password[20];
    FILE *log;
    log = fopen("login.txt","r");
    if (log == NULL)
    {
        fputs("Error at opening File!", stderr);
        exit(1);
    }
    struct login l;
    printf("\nPlease Confirm your login credentials below\n\n");
    printf("Username:\n");
    scanf("%s",username);
    getchar();
    printf("\nPassword:\n");
    scanf("%s",password);
    getchar();
    while(fread(&l,sizeof(l),1,log))
        {
        if(strcmp(username,l.username)==0 && strcmp(password,l.password)==0)        //Checking the Credentials
            {   
                printf("\nCorrect Credentials!\n");
                fclose(log);
                log=fopen("login.txt","w");
                if (log == NULL)
                {
                    fputs("Error at opening File!", stderr);
                    exit(1);
                }
                struct login l;
                printf("Please enter the new Username and Password.\n"); 
                printf("\nEnter Username:\n");
                scanf("%s",l.username);
                printf("\nEnter Password:\n");
                scanf("%s",l.password);
                fwrite(&l,sizeof(l),1,log);             //Updating with New credentials
                fclose(log);
                printf("\nYou have successfully Changed ur details.\n");
                login();
            }
        else 
            {
                printf("\nIncorrect Login Details\nPlease enter the correct credentials\n");
            }
        }
    fclose(log);
    return;
}
