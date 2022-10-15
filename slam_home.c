/*Author: NIPUN MITTAL (NBTG14450)*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_size 1024

unsigned int current_screen; //to select the course from homepage
unsigned int subscreen; //to use for viewing 
unsigned int next_continue; //to use for entry to be viewed
unsigned int editscreen; //choose edit screen
unsigned int edit_next_continue; //to use for edit to made
unsigned int Last; //last saved entry
const char slam_rec[] = "slam_records.dat"; //will contains complete records
const char last_no[] = "last_saved.dat"; //will contain entry number of last entered entry 
const char slam_list[] = "slam_list.dat"; //will containt a list with number and name for identification
const char slam_rec_new[] = "slam_new_records.dat"; //will containt the contents records after edit
const char slam_list_new[] = "slam_new_list"; //will contain the content of list after edit
FILE *fpr; //to open file slam_records
FILE *fpl; //to open file last_saved
FILE *fps; //to open file slam_list
FILE *fprn; //for the new file of fps
FILE *fpsn; //for the new file of fpr
void slam_main(); //initialising main to be redirected from other functions decalred before

/*defining structure of details for slam book*/
typedef struct slam_info{

    unsigned int no;
    char fname[30];
    char lname[30];
    char bday[10];
    unsigned int age;
    char gender;
    char email[max_size];
    char phone[10];
    // char photo[max_size] = "" //photo to be included if GUI possible
    unsigned int time_period;

} slam_entry; //typedef used for convenience as the structure was used at many places

/*union to store the data of entries saved for quick view*/
typedef union identification{
    unsigned int no;
    char name[30];

}info; //typedef used for convenience

/*function to check and set the last saved entry*/
void set_last(){
    fpl = fopen(last_no,"r");
    fps = fopen(slam_list,"rb");
    if (fpl == NULL || fps == NULL){
        // printf("Null in set last");
        fclose(fpl);
        fclose(fps);
        fpl = fopen(last_no,"w");
        fprintf(fpl,"%d",1);
        fclose(fpl);
        Last = 0;
    }else{
        fclose(fps);
        fscanf(fpl,"%d",&Last);
        fclose(fpl);
        // printf("Last set as %d",Last);
    }
}

/*shows the menu for homescreen of slam book section*/
void home_menu(){

    printf("\n***This is Slam Book Section***\n");
    printf("Please refer to the menu below to continue:\n"
    "Code\tOperation\n"
    " 1. \tAdd Entry to Slam Book\n"
    " 2. \tView Entry in Slam Book\n"
    " 3. \tEdit Entry in Slam Book\n"
    " 4. \tExit to Main Menu\n");

    printf("Code: ");
    scanf("%d",&current_screen); //stored current screen to navigate between screens and functions

}

/*new slam book entry creation*/
void slam_create(){

    getchar(); //to remove the extra '\n' received after scanf
    set_last();
    slam_entry entry;
    entry.no = Last+1;

    printf("\n***This is Slam Book Entry Page***\n");
    printf("Please fill the details below about the person to make entries:\n");

    /*taking in details*/
    printf("First Name: ");
    gets(entry.fname);

    printf("Last Name: ");
    gets(entry.lname);

    printf("Birthdate (DD-MM-YYY): ");
    fgets(entry.bday,11,stdin);

    printf("Age: ");
    scanf("%d",&entry.age);
    getchar();

    printf("Gender(M/F/O): ");
    scanf("%c",&entry.gender);
    getchar();

    printf("Email: ");
    gets(entry.email);

    printf("Phone Number: ");
    fgets(entry.phone,11,stdin);

    printf("Time been friends for: ");
    scanf("%d",&entry.time_period);

    
    /*opening and writing of file of slam book detailed entries*/
    fpr = fopen(slam_rec,"ab+");
    fwrite(&entry,sizeof(entry),1,fpr);
    if(fwrite != 0)
      printf("Page Entry made Succesfully !\n");
    else
      printf("Error writing file !\n");
    fclose(fpr);

    /*updating the last saved entry*/
    fpl = fopen(last_no,"w");
    fprintf(fpl,"%d",entry.no);
    fclose(fpl);

    /*quick view of entries updation or creation*/
    info data;
    data.no = entry.no;
    strcpy(data.name,entry.fname);
    strcat(data.name, " ");
    strcat(data.name,entry.lname);

    fps = fopen(slam_list,"ab+");
    fwrite(&data,sizeof(info),1,fps);
    if(fwrite != 0)
      printf("\n");
    else
      printf("Error writing file !\n");
    fclose(fps);

}

/*view the last saved entry*/
void last_view(){

    set_last();
    slam_entry show_entry;

    fpr = fopen(slam_rec,"rb");
    if (fpr == NULL){
        printf("Please create an entry first!!\n\n");
        fclose(fpr);
    }else{
        fseek(fpr,(Last-1)*sizeof(slam_entry),SEEK_SET); //seek to exact entry from the front 
        fread(&show_entry, sizeof(show_entry), 1, fpr); //read the last saved entry

        printf("\n**Last Entry**\n");
        printf("First Name: %s\t",show_entry.fname);
        printf("Last Name: %s\n",show_entry.lname);
        printf("Birthdate: %s\n",show_entry.bday);
        printf("Age: %d\n",show_entry.age);
        printf("Gender: %c\n",show_entry.gender);
        printf("Email: %s\n",show_entry.email);
        printf("Phone Number: %s\n",show_entry.phone);
        printf("Time been friends for: %d\n\n",show_entry.time_period);
        fclose(fpr);
    }

}

/*view any exact entry in detail*/
void detail_view(){

    slam_entry show_entry;

    fpr = fopen(slam_rec,"rb");
    fseek(fpr,(next_continue-1)*sizeof(slam_entry),SEEK_SET); //seek to requested entry
    fread(&show_entry, sizeof(show_entry), 1, fpr);

    printf("\n**Chosen Entry**\n");
    printf("Entry No: %d\n",show_entry.no);
    printf("First Name: %s\t",show_entry.fname);
    printf("Last Name: %s\n",show_entry.lname);
    printf("Birthdate: %s\n",show_entry.bday);
    printf("Age: %d\n",show_entry.age);
    printf("Gender: %c\n",show_entry.gender);
    printf("Email: %s\n",show_entry.email);
    printf("Phone Number: %s\n",show_entry.phone);
    printf("Time been friends for: %d\n\n",show_entry.time_period);
    fclose(fpr);

}

/*quick view list of the entries made and accordingly redirect to detailed view on request*/
void list_view(){

    set_last();
    info small_list;

    /*displaying the quick list to navigate entries*/
    viewchoice: printf("\n***You are now viewing the list of entries made so far***\n");
    fps = fopen(slam_list,"rb");
    if (fps == NULL){
        printf("\nPlease create an entry first!!\n\n");
        fclose(fps);
    }else{
        printf("Entry No\tName of Person\n");
        for (int i=0; i<Last;i++){
            fseek(fps,i*sizeof(info),SEEK_SET);
            fread(&small_list,sizeof(small_list),1,fps);
            printf("  %d.\t\t%s\n",(i+1),small_list.name);
        }
        fclose(fps);

        printf("Enter the entry no if you wish to open any else enter 0 to go back: ");
        scanf("%d",&next_continue); //guide to the entry to be viewed in detail

        switch ((next_continue+(Last-1))/Last) //0 if 0, 1 if in range [1,Last], default if any higher
        {
        
        case 0:
            break;

        case 1:
            detail_view();
            goto viewchoice;

        default:
            printf("\nEnter a valid code please!!\n");
            goto viewchoice;
        }
    }
}

/*view page menu*/
void slam_view(){

    sview: printf("\n***This is Slam Book View Page***\n");
    printf("Please select a function to execute from below:\n"
    "Code\tFunction\n"
    " 1. \tView Last Saved Entry\n"
    " 2. \tView Entry List\n"
    " 3. \tReturn to Slam Book Homepage\n");
    printf("Code: ");
    scanf("%d",&subscreen);
    switch (subscreen)
    {
    case 1:
        last_view();
        goto sview;

    case 2: 
        list_view();
        goto sview;

    case 3:
        printf("\nNow exiting from slam book view section!!\n...\n....\n\n");
        break;

    default:
        printf("\nEnter a valid code please!!\n");
        goto sview;
    }

}

/*function for convenience to avoid repetition using parameters which would vary*/
/*this function helps in copying the unchanged data to a temp file so that edited data can be inserted in the same place again*/
void copy_old(int Start, int End){

    slam_entry temp_entry;
    info temp_data;

    fpr = fopen(slam_rec,"rb");
    fprn = fopen(slam_rec_new,"ab+");
    fps = fopen(slam_list,"rb");
    fpsn = fopen(slam_list_new,"ab+");
    for (int i=Start;i<End;i++){
        fseek(fpr,(i-1)*sizeof(slam_entry),SEEK_SET);
        fread(&temp_entry,sizeof(slam_entry),1,fpr);
        fwrite(&temp_entry,sizeof(slam_entry),1,fprn);

        fseek(fps,(i-1)*sizeof(info),SEEK_SET);
        fread(&temp_data,sizeof(info),1,fps);
        fwrite(&temp_data,sizeof(info),1,fpsn);
    }
    fclose(fpr);
    fclose(fprn);
    fclose(fps);
    fclose(fpsn);
}

/*function for convenience to avoid repetition using parameters which would vary*/
/*this function changes the edit made on the specified entry*/
void change_edit(int End, slam_entry rec, info data){

    fprn = fopen(slam_rec_new,"ab+");
    fseek(fprn,(End-1)*sizeof(slam_entry),SEEK_SET);
    fwrite(&rec,sizeof(slam_entry),1,fprn);
    fclose(fprn);

    fpsn = fopen(slam_list_new,"ab+");
    fseek(fpsn,(End-1)*sizeof(info),SEEK_SET);
    fwrite(&data,sizeof(info),1,fpsn);
    fclose(fpsn);
}

/*quickly edit the last saved file on the go without wasting time, specially helpfull 
if made a mistake in saving the entry and want to quick fix the mistake*/
void last_edit(){
    
    getchar();
    set_last();
    slam_entry show_entry,new_entry;
    info new_data;

    fpr = fopen(slam_rec,"rb");
    if (fpr == NULL){
        printf("Please create an entry first!!\n\n");
        fclose(fpr);
    }else{
        fseek(fpr,(Last-1)*sizeof(slam_entry),SEEK_SET); //makes use of Last to get to the start point of last creation
        fread(&show_entry, sizeof(show_entry), 1, fpr);

        printf("\n**Last Entry**\n");
        printf("First Name: %s\t",show_entry.fname);
        printf("Last Name: %s\n",show_entry.lname);
        printf("Birthdate: %s\n",show_entry.bday);
        printf("Age: %d\n",show_entry.age);
        printf("Gender: %c\n",show_entry.gender);
        printf("Email: %s\n",show_entry.email);
        printf("Phone Number: %s\n",show_entry.phone);
        printf("Time been friends for: %d\n\n",show_entry.time_period);

        printf("\nPlease enter the new details of the above entry!!\n");
        new_entry.no = show_entry.no;
        printf("First Name: ");
        gets(new_entry.fname);
        printf("Last Name: ");
        gets(new_entry.lname);
        printf("Birthdate: ");
        fgets(new_entry.bday,11,stdin);
        printf("Age: ");
        scanf("%d",&new_entry.age);
        getchar();
        printf("Gender(M/F/O): ");
        scanf("%c",&new_entry.gender);
        getchar();
        printf("Email: ");
        gets(new_entry.email);
        printf("Phone Number: ");
        fgets(new_entry.phone,11,stdin);
        printf("Time been friends for: ");
        scanf("%d",&new_entry.time_period);
        fclose(fpr);

        new_data.no = new_entry.no;
        strcpy(new_data.name,new_entry.fname);
        strcat(new_data.name, " ");
        strcat(new_data.name,new_entry.lname);

        copy_old(1,Last);
        change_edit(Last,new_entry,new_data);

        remove(slam_rec);
        rename(slam_rec_new,slam_rec);
        remove(slam_list);
        rename(slam_list_new,slam_list);
        printf("\nYour Last Entry has been updated!!\n");
    }

}

/*common edit function used to edit any entry in start or middle*/
void middle_edit(int N){

    getchar();
    set_last();
    slam_entry show_entry,new_entry;
    info new_data;

    fpr = fopen(slam_rec,"rb");
    fseek(fpr,(N-1)*sizeof(slam_entry),SEEK_SET);
    fread(&show_entry, sizeof(show_entry), 1, fpr);

    printf("\n**Entry No: %d**\n",show_entry.no);
    printf("First Name: %s\t",show_entry.fname);
    printf("Last Name: %s\n",show_entry.lname);
    printf("Birthdate: %s\n",show_entry.bday);
    printf("Age: %d\n",show_entry.age);
    printf("Gender: %c\n",show_entry.gender);
    printf("Email: %s\n",show_entry.email);
    printf("Phone Number: %s\n",show_entry.phone);
    printf("Time been friends for: %d\n\n",show_entry.time_period);

    printf("\nPlease enter the new details of the above entry!!\n");
    new_entry.no = show_entry.no;
    printf("First Name: ");
    gets(new_entry.fname);
    printf("Last Name: ");
    gets(new_entry.lname);
    printf("Birthdate: ");
    fgets(new_entry.bday,11,stdin);
    printf("Age: ");
    scanf("%d",&new_entry.age);
    getchar();
    printf("Gender(M/F/O): ");
    scanf("%c",&new_entry.gender);
    getchar();
    printf("Email: ");
    gets(new_entry.email);
    printf("Phone Number: ");
    fgets(new_entry.phone,11,stdin);
    printf("Time been friends for: ");
    scanf("%d",&new_entry.time_period);
    fclose(fpr);

    new_data.no = new_entry.no;
    strcpy(new_data.name,new_entry.fname);
    strcat(new_data.name, " ");
    strcat(new_data.name,new_entry.lname);

    if (N!=1){
        copy_old(1,N); //because if n=1 then it is the first entry and no entry exisits before it so no need to copy anything before it
    }
    change_edit(N,new_entry,new_data); //adding the changed entry
    copy_old(N+1,Last+1); //paramters sent to copy the remaing entries after the edit

    /*renaming the temp file to and removing the initial file to keep the records after editing in a file of same name*/
    remove(slam_rec);
    rename(slam_rec_new,slam_rec);
    remove(slam_list);
    rename(slam_list_new,slam_list);
    printf("\nYour Entry has been updated!!\n");
}

/*quick view list for different purpose of editing to not waste time in looking at detailed records to search the
entry number of the page user wants to edit instead gives a quick view of the code and respective entries*/
void view_list(){

    set_last();
    info small_list;

    editchoice: printf("\n***You are now viewing the list of entries made so far***\n");
    fps = fopen(slam_list,"rb");
    if (fps == NULL){
        printf("\nPlease create an entry first!!\n\n");
        fclose(fps);
    }else{
        printf("Entry No\tName of Person\n");
        for (int i=0; i<Last;i++){
            fseek(fps,i*sizeof(info),SEEK_SET);
            fread(&small_list,sizeof(small_list),1,fps);
            printf("  %d.\t\t%s\n",(i+1),small_list.name);
        }
        fclose(fps);

        printf("Enter the entry no you wish to edit or enter 0 to go back: ");
        scanf("%d",&edit_next_continue);

        switch ((edit_next_continue+(Last-1))/Last) //0 if 0, 1 if in range [1,Last], default if any higher
        {
        
        case 0:
            break;

        case 1:
            middle_edit(edit_next_continue);
            goto editchoice;

        default:
            printf("\nEnter a valid code please!!\n");
            goto editchoice;
        }
    }

}

/*edit menu page to direct to respective editing page*/
void slam_edit(){

    sedit: printf("\n***This is Slam Book Edit Page***\n");
    printf("Please select a function to execute from below:\n"
    "Code\tFunction\n"
    " 1. \tEdit Last Saved Entry\n"
    " 2. \tEdit Entry List\n"
    " 3. \tReturn to Slam Book Homepage\n");
    printf("Code: ");
    scanf("%d",&editscreen);
    switch (editscreen)
    {
    case 1:
        last_edit();
        goto sedit;

    case 2: 
        view_list();
        goto sedit;

    case 3:
        printf("\nNow exiting from slam book edit section!!\n...\n....\n\n");
        break;

    default:
        printf("\nEnter a valid code please!!\n");
        goto sedit;
    }

}

/*main page of slam book used to access differnet functions within the file*/
void slam_main(){
    
    home: home_menu();

    switch (current_screen)
    {
    case 1:
        slam_create();
        goto home;

    case 2:
        slam_view();
        goto home;

    case 3:
        slam_edit();
        goto home;

    case 4:
        printf("\nNow exiting from slam book section!!\n...\n....\n\n");
        break;
        // goto escape;
    
    default:
        printf("\nEnter a valid code please!!\n");
        goto home;
    }

    /*this would be used if the slam book exists as seperate entity*/
    // escape: getchar();
}

void main(){

    slam_main();

}