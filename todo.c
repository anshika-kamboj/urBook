/*Author: AVIRAL JAIN (ECN14068)*/

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct ToDo todo;
//Declaration of Structure
struct ToDo
{
    char task[101];         //for char array
    todo* next;             //pointer to acess different parts
    int count;              //to counter number of tasks
};
todo* start = NULL;         //start pointer set to null
void todo_main();
void seetodo();
void createtodo();
void deletetodo();
void adjustcount();

void todo_main()
{
    int choice;
    printf("Instant To-Do List\n");
    int xx = 1;
    while (xx)
    {
        printf("1. To see your ToDo list\n");
        printf("2. To create new ToDo\n");
        printf("3. To delete your ToDo\n");
        printf("4. Exit");
        printf("\nEnter your choice:\t");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            seetodo();
            break;
        case 2:
            createtodo();
            break;
        case 3:
            deletetodo();
            break;
        case 4:
            xx = 0;
            break;
        default:
            printf("\nInvalid Choice :-(\n");
        }
    }
}
//to view the list of all to-do's
void seetodo()
{
    todo* temp;     // for iterating 
    temp = start;
    if (start == NULL)
        printf("\n\nEmpty ToDo \n\n");
    while (temp != NULL)        // to iterate till end
    {
        printf("%d.)", temp->count);
        puts(temp->task);
        fflush(stdin);
        temp = temp->next;
    }
    printf("\n\n\n");
}
//to insert a to-do
void createtodo()
{
    char c;
    todo *add, *temp;
    // infinite loop until 'n' is input by the user
    while (1)
    {
        printf("\nWant to add new ToDo ?? Press 'y' for Yes and 'n' for No  :-)\n\t\t");
        fflush(stdin);
        scanf("%c", &c);
        if (c == 'n')
            break;
        else
        {
            if (start == NULL)
            {
                add = (todo*)calloc(1, sizeof(todo));   //dynamic allocation of memeory
                start = add;
                printf("\nType it.....\n");
                fflush(stdin);
                gets(add->task);
                add->count = 1;
                start->next = NULL;
            }
            else
            {
                temp = (todo*)calloc(1, sizeof(todo));
                printf("\nType it.....\n");
                fflush(stdin);
                gets(temp->task);
                temp->next = NULL;
                add->next = temp;
                add = add->next;
            }
            adjustcount();      //to adjust the count variable
        }
    }
}
void deletetodo()
{
    int x;
    todo *del, *temp;
    printf("\nEnter the ToDo's number that you want to remove.\n\t\t");
    if (start == NULL)
        printf("\n\nThere is no ToDo for today :-)\n\n\n");
    else {
        scanf("%d", &x);
        del = start;
        temp = start->next;     //temp will point here to start next to that we can easil iterate and delete the contents
        while (1)
        {
            if (del->count == x)
            {
                start = start->next;
                free(del);
                adjustcount();
                break;
            }
            if (temp->count == x)
            {
                del->next = temp->next;
                free(temp);
                adjustcount();
                break;
            }
            else 
            {
                del = temp;
                temp = temp->next;
            }
        }
    }
}
void adjustcount()
{
    todo* temp;
    int i = 1;
    temp = start;
    while (temp != NULL)
    {
        temp->count = i;
        i++;
        temp = temp->next;
    }
}
