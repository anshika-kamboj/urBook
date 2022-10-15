/*Author: ANSHIKA KAMBOJ (EMP61884)*/

#include <stdlib.h>
#include<stdio.h>
#include<string.h>
#define size 1024

    char *ch1;//these variables will store choices entered by user.
    char *date; //stores date as string
    char* temp;
    char*y; //stores year for journal
    char*month;  //stores month for journal
    char *data; //stores string entered by user while creating new file
    char*day; //stores day number for journal
    char*q= "saved journals.txt" ;

    FILE *prsntfile;   //pointer to an already created,i.e. running file
    FILE *newfile;//pointer to file that is being created
    FILE *list;

    void journalhometab(); //user have 3 option either to access existing file,to create new fie or to exit general writing tab
    int cases();
    char* readdate();//reads the date input by user
    char* modifyfilename(char*);  //file name is modified to date.p
    void createnewfile(); // a new file is created here
    void editfileslist(char*);
    void accesssavedfile();// saved file is accessed here
    void deletefile();
    void printastrik();
    void journal_main();

void journal_main()
{

    //in journalhometab user selects if they want to close ,edit or create journal
    journalhometab();
    int r =cases( );
   while(r)
   {
     r=  cases();
   }
}


void journalhometab()
{
    printf("\n enter 'o' to access saved journal,'n' to create journal for a fresh day ,'d' to delete  any saved journal and 'c' to exit journal  \n");
    ch1=(char*)malloc(1);
     gets(ch1);
}


int cases()
{
 switch (*ch1)
    {
        //if 'o' is entered accesssavedfile is called to access an already created file and if the file does not exist it shows an appropriate message
    case 'o':
        {
         accesssavedfile();
         journalhometab();
           return 1;
        }
        // if 'n' is entered createnewfile is called to create a new file with filename as "username_date.txt"
    case 'n' :
        {
         createnewfile();
         journalhometab();
         return 1;
        }
        //if user enters d then the selected file will be deleted
    case 'd':
        {
            deletefile();
            journalhometab();
            return 1;
        }
       //if user selects 'c' then journal  is closed
    case 'c':
        {
    return 0;
        }
    default :
        {
            printf("\n please select valid option\n");
            journalhometab();
            return 1;
        }
    }
}


char* readdate()
{

    date=(char*)malloc(15);
    printf("\n date format : (for 22 march 2019 enter 22 as date ,march as month and 2019 as year:\n");
    printf("\n  date  :\n");
    //day store date
    day=(char*)malloc(2);
    gets(day);
    printf("  month  :\n") ;
    month=(char*)malloc(9);
    gets(month);
    printf("  year  :\n ");
    y=(char*)malloc(4);
    gets(y);
    temp=(char*)malloc(4);
    temp=strcat(day,month);
    //temp stores concatenated day and month
    date=strcat(temp,y);
    //date stores concatenated date,month and year for further use
    return date;
}


//this function takes the entered date as parameter and modified it to file name of a text file
//the modified file name is returned by this function

char *modifyfilename(char *d)
{

   char*n;
   //stores  entered date.txt
   n=strcat(d,".txt");
   return n;

}


 //if user enters "n" i.e.  choose to create a journal for new day then  this function is called
//a new file is created in this function

 void createnewfile()

 {   printf(" \n Enter todays date :\n");
  char * usedate=NULL;
   usedate=readdate();
  // usedate stores the date returned by readdate()
  char *n=NULL;
  n=modifyfilename(usedate);
  // n stores date modified to filename
   newfile=fopen(n,"w");
   //file is opened in write mode
   printf("\n how was  ur day:\n");
   //data entered by user is printed to file
   data=(char*)malloc(size);//here data stores strings entered by user in journal
   fgets(data,size,stdin);
   fputs(data,newfile);
   fputs("    ",newfile);
    printf("\n your data has been successfully saved \n");
    printastrik();
    editfileslist(day);
    fclose(newfile);
}


void editfileslist( char* d)
{
    list=fopen(q,"a+");
    fprintf(list,"\n =>  %s \n",d);
    fclose(list);
}


 //if user enters 'o' i.e. access saved file then this function is called and further changes are made accordingly

void accesssavedfile()
{
    printf("\n enter the date of the journal that is to be viewed \n");
     char * usedate=NULL;
     usedate=readdate();
     //usedate =the date updated  to file name
     char * n=NULL;
     n=modifyfilename(usedate);
     // n stores name of file for further use
     prsntfile=fopen(n,"r");
     if(prsntfile==NULL)
        {
            printf("\n FILE DO NOT EXIST\n");
            fclose(prsntfile);
        } //end of if

     else
     {   printf("\n\n journal data : \n\n\n");
         //existing data is read
        char str;
         str=fgetc(prsntfile);
         while(str!=EOF)
           {
         printf("%c",str);
         str=fgetc(prsntfile);
           }
         fclose(prsntfile); //file closed
      printf("\n enter e to edit data else press enter key to close :\n");
      //if user enters "e"   the file is opened in append mode and edited
     char*p=(char*)malloc(1);
      gets(p);
      if(*p == 'e')
        {
            printf("\n edit here ....    ;) \n") ;
             prsntfile=fopen(n,"a");
             char*edit; //stores string of  edited data
             edit=(char*)malloc(size);
             gets(edit);
             fputs(edit,prsntfile);//appends  edited data to file
             fclose(prsntfile);
             printf( "\n edited data saved successfully ;) \n");
             printastrik();
        }
       else
        {
            printf(" \n the saved journal was viewed successfully and no edit was made:) \n");
            printastrik();
        }
     }
}



void deletefile()
{
    printf("\n enter the date of the file that is to be deleted \n");
     char * usedate=NULL;
   usedate=readdate();
  // usedate stores the date returned by readdate()
  char *n=NULL;
  n=modifyfilename(usedate);
  int r;
  r =remove(n);
    if(r==0)
    printf("\nThe file has been successfully deleted\n");
    else
        printf("\n the file was not deleted \n please try again \n");
}


 void printastrik()
 {
     int i=0;
     printf("\n");
     for(i;i<40;i++)
        printf(" * ");
     printf("\n");
 }
