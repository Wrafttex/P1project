#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define MAX_NAME_LGT 500
//tror jeg kommer til at skift hvordan ingrediens virker fordi jeg må nok få fat type af volume, får at kunne gøre indkøbliste korrekt

typedef struct structIngrediensDeclare
{
   double volume;
   char name [MAX_NAME_LGT];
} structIngrediens;

typedef struct structFilenamesDeclare{
   char filenames[MAX_NAME_LGT];
   int amountOfFiles;
} structFilenames;

typedef struct structMealDeclare
{
   char mealName [MAX_NAME_LGT];
   char amountOfPeople [MAX_NAME_LGT];
   char preparationTime [MAX_NAME_LGT];
   char ingredients [MAX_NAME_LGT];
   char procedure [MAX_NAME_LGT];
} structMeal;

/* Prototypes */
// skift navn på readDataIngredients til noget andet
int readDataIngredients (structIngrediens ingrediens[],char filename[], structMeal meals[]);
void multiplier (int amountOfPeople, structIngrediens ingrediens[], int amountOfIngredients);
void instructions (void);
int mealplanChooser (void);
int scanDataBetween (int x, int y);
int scanDataAmountOfPeople (void);
char* scanDatafilename (char filename[], structFilenames allFiles[]);
void loopPrint(structIngrediens ingrediens[], structMeal meals[], int amountOfPeople, char filename[], int amountOfIngredients);
void findingNormalTxt(structFilenames normalFilenames[]);
void findingMindreKoedtxt(structFilenames mindreKoedFilenames[]);
void navFunction (int destination);
int help (void);

int main (void)
{
   /*Declaring variables used in main*/
   int i;
   int test;
   int choice;
   int amountOfPeople;
   int amountOfIngredients;
   char filename[25];

   structMeal meals[4];
   structIngrediens ingrediens[25] = {0,""};  /* Declaring 0 to int volume and inserting empty string(char name), which is default setting */
   structFilenames normalFilenames[20] = {"",0};
   structFilenames mindrekoedFilenames[20] = {"",0};
   
   /*Functions scanning directories for files*/
   // De her er træls!
   findingNormalTxt(normalFilenames);
   findingMindreKoedtxt(mindrekoedFilenames);

   /*Function printing user-instructions as output*/
   instructions();
   
   amountOfPeople = scanDataAmountOfPeople();
   
   choice = mealplanChooser();
   
   // Move to function.
   if (choice == 1)
      strcpy(filename,scanDatafilename(filename, normalFilenames));
   else if (choice == 2)
      strcpy(filename,scanDatafilename(filename, mindrekoedFilenames));

   printf("%s", filename); // Test

   amountOfIngredients = readDataIngredients(ingrediens, filename, meals);
   multiplier(amountOfPeople, ingrediens, amountOfIngredients);
   loopPrint(ingrediens, meals, amountOfPeople, filename, amountOfIngredients);
   return 0;
}

void encodeFilename (char * normalFilenames, char* mindreKoedFilenames)
{
   // Place to move the strcpy to. Gøres når Magni er done med dem
}

int scanDataBetween (int x, int y)
{
   int choice = 0;

   do
   {
      if ((choice >= x || choice < y))
      {
         printf("Dit valg passer ikke med de givne muligheder ");
         fflush(stdin);
         choice = -1;
      }
      printf("Intast valg: ");   
      scanf("%d", &choice);
      printf("\n");
   } while ((choice >= x || choice < y));
   
   return choice;
}



int scanDataAmountOfPeople(void)
{
   int amountOfPeople = 0;
   
   do
   {
      printf("\nAntal personer: ");
      scanf("%d", &amountOfPeople);
      printf("\n");
   } while (!(amountOfPeople > 0));
   
   return amountOfPeople;
}

/* scans for which file you want to access, and puts into a char array that is cal led filnavn*/
char* scanDatafilename (char filename[], structFilenames allfilenames[])
{
   int i;
   int inputTruthValue = 0;
   //char weekdays[7][8] = {"Mandag", "Tirsdag", "Onsdag", "Torsdag", "Fredag", "Loerdag", "Soendag"};

   /* Do-while-loop scanning for given day of the week, comparing chosen weekday
    * (declared in weekdays string array) with filename, returning filename */
   do
   {
      printf("Hvilken dag vil du se madplan for, foerste bogstav skal vaere caps: ");
      scanf("%s", filename);
      fflush(stdin);
      
      for(i = 0; i < allfilenames[0].amountOfFiles ; ++i)
      {
         if(strcmp(filename, allfilenames[i].filenames) == 0)
         {
            inputTruthValue = 1;
         }
      }
   } while (inputTruthValue == 0);
  
   return filename;
}

/* Function for printing user-instructions */
void instructions (void) 
{
   printf("-------------------------Den Digitale Madplan-------------------------\n\n");
   printf("Alle madplaner gaelder for 7 dage,og inkludere inkoebsliste, opskrifter.\n\n");
   printf("Brug aa, ae og oe i stedet for danske bogstaver.\n\n");
   printf("Vaelg antal personer der skal foelge madplanen.\n\n");
   printf("Hvilken madplan vil du bruge, ud fra de givne valg.\n\n");
   printf("Ved at trykke paa (i) vil indkoebslisten blive vist.\n\n");
   printf("Hvis du har problemmer eller har valgt forkert tryk paa (h) for hjaelp.\n\n");
   printf("I hjaelp, vil der vaere mulighed for at gaa tilbage til starten, eller gaa til det forige skridt.\n");
}

/* Choosing type of mealplan */
int mealplanChooser (void)
{
   int choice;
   int destinations;

   printf("Vaelg en af de nedstaeende muligheder\n");
   printf("1) Standart madplan\n");
   printf("2) Mindre koed\n");
   printf("3) Hjaelp!\n");
   printf("4) Afslut menu\n\n"); 

   choice = scanDataBetween(4, 0);

   /*Finding which choice was asked for (my style of using brackets may be different than yours) */
   switch (choice)
   {
   case 1:
      printf("Du har valgt den normal madplan.\n\n");
      break;
   case 2:
      printf("Du har valgt den madplan med mindre koed.\n\n");
      break;
   case 3:
      destinations = help();
      navFunction(destinations);
      mealplanChooser();
      break;
   case 4:
      exit(0);
      break;
   default:
      break;
   }

   return choice;
}

/* This function reads the ingrediens and puts it into a double and a string,
 * so that we can change the value of how much a person should use ;D
 * From the '$' in the file to the int 69420 appears, we read the ingredient volume and ingredient name */

int readDataIngredients (structIngrediens ingrediens[], char filename[], structMeal meals[]) 
{
   int checker = 0, i = 0;
   strcat(filename, ".txt"); 
   FILE *recipe;

   recipe = fopen(filename, "r"); 

   if (recipe == NULL)
   {
      printf("The file name entered isn't viable. Please try again");
      EXIT_FAILURE;
   }
   
   fscanf(recipe, "%[^;]; %[^;]; %[^;]; %[^;];", meals[i].mealName, meals[i].amountOfPeople, meals[i].preparationTime, meals[i].ingredients);

   
   if (strcmp(filename,"Soendag.txt") != 0)
   {
      while (checker != 69420)
      {
         fscanf(recipe, "%lf %[^:]: %d", &ingrediens[i].volume, ingrediens[i].name, &checker);
         ++i;
      }
   
      fscanf(recipe,"%[^&]&", meals[1].procedure);
   }
   fclose(recipe);

   return i;
}

/*Function multiplying the chosen amount of people, with the amount of ingredients.*/

/*Function multiplying the chosen amount of people, with the amount of ingredients.*/
void multiplier(int amountOfPeople, structIngrediens ingrediens[], int amountOfIngredients) 
{
   int i; 
   for (i = 0; i < amountOfIngredients; i++)
   {
      ingrediens[i].volume = amountOfPeople * ingrediens[i].volume; 
   } 
}

/*Function printing Meal Name, Amount of People, Preparation time and ingredients in a for-loop iterating over the total amount of ingredients */

void loopPrint(structIngrediens ingrediens[], structMeal meals[], int amountOfPeople, char filename[], int amountOfIngredients)
{
   int i;

   printf("\n%s \n%s %d \n%s \n%s \n", meals[0].mealName, meals[0].amountOfPeople, amountOfPeople, meals[0].preparationTime, meals[0].ingredients);

   for (i = 0; i < amountOfIngredients; i++)
   {
      printf("%5.2lf %s\n", ingrediens[i].volume, ingrediens[i].name);
   }
   
   if(strcmp(filename,"soendag.txt") != 0)
      printf("%s\n", meals[1].procedure);    
}


/*Function reading different files in given directory in a while loop for every file*/

void findingNormalTxt(structFilenames filename[])
{
   struct dirent* recipe;
   int i = 0;
   char localNormalFilenames[20][20];

   
   DIR* dr = opendir("recipe");

   if (dr == NULL)
   {
      printf("could not open current directory");
      exit(-1);
   }

   while ((recipe = readdir(dr)) != NULL)
   {
      if (strcmp(recipe->d_name, ".")!=0 && strcmp(recipe->d_name, "..") !=0)
      {
         strncpy(filename[i].filenames, recipe->d_name, strlen(recipe->d_name)-4);
         //printf("%s == %s\n",recipe->d_name, filename[i].filenames); 
         i++;
         ++filename[0].amountOfFiles;
      }
   }
}



void findingMindreKoedtxt(structFilenames mindreKoedFilename[])
{
   struct dirent *recipe;
   int i = 0;
   char localmindreKoedFilenames[20][20];

   DIR *dr = opendir("mindrekoedrecipe");

   if (dr == NULL)
   {
      printf("could not open current directory");
      exit(-1);
   }

   while ((recipe = readdir(dr)) != NULL)
   {
      if (strcmp(recipe->d_name,".")!=0 && strcmp(recipe->d_name,"..") !=0)
      { 
         strncpy(mindreKoedFilename[i].filenames, recipe->d_name, strlen(recipe->d_name)-4);
         //printf("%s == %s\n",recipe->d_name, mindreKoedFilename[i].filenames); 
         ++i;
         mindreKoedFilename[0].amountOfFiles++;
      }
   }
} 

int help (void)
{
   int destination;

   printf("---------------Hjaelp---------------\n\n");
   printf("Mulige funktioner du kan tilgaa her\n\n");
   printf("er: instruktioner, start menu og afslut menu.\n\n");
   printf("Instruktioner viser instruktionerne som blev vist i starten.\n\n");
   printf("Start menu tager dig helt til bage til starten.\n\n");

   printf("1) Instruktioner\n2) Start menu\n");
   destination = scanDataBetween(2, 0);

   return destination;
}

void navFunction (int destination)
{
   switch (destination)
   {
   case 1:
      instructions();
      break;
   case 2:
      main();
      break;
   default:
      break;
   }
}