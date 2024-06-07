//Kitchen Management System
#include<conio.h>
#include<stdio.h>
#include<string.h>

//Preprocessor statements 
void display_menu();
void display_alt();
void reserve();	
void Review();
void menu();
void login();

//Decalaring global vars
int i = 0;

//struct to hold student data
struct Student
{
char name[30], ID[30];
}student[99];

//function to display menu, to do this, read from file that has already been created
void display_menu(){
	FILE *fptr;
    char food[50];
	
	
	printf("\t\t\t------Todays Meal-----------\n");
	//opening file to be read and assigning it to pointer
	fptr = fopen("Meal_Menu.txt","r+");

	//Check to see if pointer to file is empty 
    if(fptr == NULL){
        printf("No file");
    }

    while(fgets(food, 50,fptr))
    {
    	fscanf(fptr, "%s",food);
        printf("%s\n", food);
    }
	//closing file
	fclose(fptr);
}
// This function displays  alternative meals in an event  where the student can not eat what has been listed.
void display_alt(){
	// To display alternative meals, we read from the meal_menu file but only display the alternative meals.s
    char alt_food[50];	
    FILE *fptr;
	
	//opening file to be read and assigning it to pointer
	fptr=fopen("Alternative_Meal_Menu.txt","r+");

	printf("\t\t\t----------Alternative meal------------\n");

	//Check to see if pinoter to file is empty 
    if(fptr == NULL){
        printf("No file");
    }
    while(fgets(alt_food, 50, fptr))
    {
        printf("%s", alt_food);
    }
	//closing file
    fclose(fptr);
}
//  This function enables you make reservaion
void reserve(){
	FILE *fp;
	char *name = student[i].name, *SID = student[i].ID;// This variable will be used to store the name of the student that needs the reservation
	int reason;

	//here
	fp=fopen("reservation.txt","w+");

	//Check to see if pinoter to file is empty 
	if(fp == NULL){
		printf(" No File ");
		return;
	}else
	{
		//The two reasons valids, user must only select from the two to get the meal reserved
		puts("What is your reason for making a reservation?");
		puts("1. Sick?");
		puts("2. Out of campus?");
		//collecting user's reason
		puts("Enter choice: ");
		scanf("%d", &reason);

		//Switch statment to run based on user input
		switch(reason)
		{
			case 1:
				//Telling the user that their reason is valid
				puts("Valid Reason, Meal reserved");
				//Writing student name and ID to file  
				fprintf(fp, " %s - %s  reason for reservation = Sick", name, SID);
				break;
			
			case 2:
				//Telling the user that their reason is valid
				puts("Valid Reason, Meal reserved");
				//Writing student name and ID to file 
				fprintf(fp, " %s - %s  reason for reservation = Out of campus", name, SID);
				break;
			default:
				//if reason is anything besides valid reason then default is triggered
				puts("Invalid Reason, reservation Failed");
				break;
		}
		menu();
	}
	//closing file
    fclose(fp);
}

//This function when called enables user to give review of the meal.
void Review(){
	//pointer to file
	FILE *fp;
	//Taking in user review
	char review[1000];

	//opeing file and assiging pointer fp to it
	fp = fopen("Meal_Review.txt","w+");

	//Check to see if pinoter to file is empty 
	if(fp == NULL){
		printf("No File");
	}else{
		//Taking in review
		puts("How did you find the meal?");
		scanf("%s", review);
		fprintf(fp, "%s", review);
	}
	
	//closing file
    fclose(fp);
}

 void login()
{
    //Pointer for a file
    FILE *fp;
    //Declaraing char array to be used as strings
    char c,name[30], ID[7];
    //Declaraing count to be used to loop through ID 
    int count = 0;
    //Declaing cheaking vars to check the user input and file
    int check_name, check_SID;

    //Opening file "student_details.txt" and giving it instructions to read the file "rb"
    fp = fopen("Student_ID_List.txt","rb");

    //Log in page
    printf("\n\t\t\t\t^^^^^^^^^^^^^^^^^^^^^^");
    printf("\n\n\t\t\t\tSTUDENT LOG IN FOR KITCHEN");
    printf("\n\t\t\t\t^^^^^^^^^^^^^^^^^^^^^^");

    //for loop to run through statments till either break or i < 1000
    for(i = 0; i < 1000; i++)
    {
        //Asking user for name
        printf("\n\n\t\t\t\t  ENTER FIRST NAME: ");

        //Collecting user name
        scanf("%s",name);

        //Asking user for student ID
        printf("\n\n\t\t\t\t  ENTER STDUENT ID: ");

        //Collecting user student ID as individual charaters using while loop
        //while loop will collect char's less than 11 because Student ID max length is 10 
        while(count < 7)
        {
            scanf("%c", &c);
            //Collecting chars and increasing count with each loop
            //Count increase makes sure char's are saved in different index's
            student[i].ID[count++] = c;
            if(count == 6)
            break;
        }

        //Making the last number in the array index = '\0' or end character
        ID[count += 1] = '\0';

        char a;

        //while loop to loop through the file to EOF(end of file) using fp - pointer to file
        while(!feof(fp))
        {
            //Reading file one line ar a time 
            //Using instance of student to stuct at index [i] and allocatting memory based of size of student instance
            //Reading pointer fp
            fread(&student[i], sizeof(student[i]), 1, fp);

            //File string will be compared to the string the user entered
            //if strings name and student[i].name are the same strcmp returns 0
            check_name = strcmp(name, student[i].name);

            //File string will be compared to the string the user entered
            //if strings ID and student[i].ID are the same strcmp returns 0
            check_SID = strcmp(ID, student[i].ID);

            //Checking to see if both setting of strings are true
            if(check_name == 0 && check_SID == 0)
            {

                //Printing user success
                printf("\n\n\n\t\t\tWELCOME %s YOUR LOG IN WAS SUCCESSFUL", name);

                //Sending user to menu function
                menu();

                //Breaking out of loop
                break;
            }

            //Checking to see if Student ID entered is the same as the one in the file 
            else if(check_name == 0 && check_SID != 0)
            {
                //Telling user that the student ID is wrong
                printf("\n\n\n\t\t\tWRONG STUDENT ID!! ");

                //Option for retrying login
                printf("\n\n\t\t\t\t  (Press 'Y' to re-login) ");
                scanf("%c", &a);

                //if user input is equal to 'Y' or 'y' the login
                if(a == 'y'|| a == 'Y')

				//calling login function to re-try log-in
                login();
            }

            //Checking to see if Student name entered is the same as the one in the file 
            else if(check_name != 0 && check_SID == 0)
            {
                //Student name not valid
                printf("\n\n\n\t\t\tStudent name not valid\n \t\t\tPress enter to register yourself");

                //Option for retrying login
                printf("\n\n\t\t\t\t  (Press 'Y' to re-login)");
                scanf("%c", &a);

                //if user input is equal to 'Y' or 'y' the login
                if(a == 'y'|| a == 'Y')
                login();
            }
            menu();
        }
		//closing file
		fclose(fp);
        break;
    }
}

void menu()
{
	//Var to collect user input
	int options;

	//Menu 
	puts("-----Welcome To The NU Kitchen-------------");
	puts("Select option 1 to display todays menu.");
	puts("Select option 2 to display alternative.");
	puts("Select option 3 to make a meal reservation.");
	puts("Select option 4 to give a review.");
	puts("Press the escape button to end.");
	scanf("%d",&options);

	//Work begins
	FILE*fptr;

	switch(options){
	case 1:

	//call the function that displays menu
	display_menu();
	break;
			
	
	case 2:

	//call the function to display alternative	
	display_alt();
	menu();
	break;	
	
	case 3:

	// Call review function	
	reserve();
	menu();	
	break;	
		
	case 4:
		
	// Call review function
	Review();
	break;	

	case 5:
		
	break;
	}
		
}

int main(){

    login();
    
    return 0;
 
}
