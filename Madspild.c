#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

//#include "ScanData.h"

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
int help(void);
int choiceChooser (void);
int scanDataAmountOfPeople (void);
int scanDataBetween (int HigestOption, int lowestOption);
int readDataIngredients (structIngrediens ingrediens[], char filename[], structMeal meals[]);
int shoppingList(structIngrediens ingrediens[], char Filenames[]);
int forLoopShoppingList(structIngrediens ingrediens[], structFilenames allFilenames[]);
int encodeFilename (structFilenames normalFilenames[], structFilenames mindreKoedFilenames[], 
                     char filename[], int choice, structIngrediens ingrediens[], structMeal meals[]);
char* scanDatafilename (char filename[], structFilenames allFiles[]);
void instructions (void);
void navFunction(int destination);
void findingNormalTxt(structFilenames normalFilenames[]);
void findingMindreKoedTxt(structFilenames mindreKoedFilenames[]);
void multiplier (int amountOfPeople, structIngrediens ingrediens[], int amountOfIngredients);
void loopPrint(structIngrediens ingrediens[], structMeal meals[], int amountOfPeople, char filename[], int amountOfIngredients);
void printShoppingList(structIngrediens ingrediens[], int amountOfIngredients);

void main (void)
{
   /*Declaring variables used in main*/
   char filename[30];
   int amountOfIngredients;
   int amountOfPeople;
   int choice;

   structMeal meals[4];
   structIngrediens ingrediens[150] = {{0,""}};  /* Declaring 0 to int volume and inserting empty string(char name), which is default setting */
   structFilenames normalFilenames[20] = {{"",0}};
   structFilenames mindrekoedFilenames[20] = {{"",0}};
   
   /*Functions scanning directories for files*/
   // De her er træls!
   findingNormalTxt(normalFilenames);
   findingMindreKoedTxt(mindrekoedFilenames);
   
   /*Function printing user-instructions as output*/
   instructions();
   
   amountOfPeople = scanDataAmountOfPeople();
   
   choice = choiceChooser();
   amountOfIngredients = encodeFilename(normalFilenames, mindrekoedFilenames, filename, choice, ingrediens,meals);
   
  // amountOfIngredients = readDataIngredients(ingrediens, filename, meals);
   multiplier(amountOfPeople, ingrediens, amountOfIngredients);
   loopPrint(ingrediens, meals, amountOfPeople, filename, amountOfIngredients);
   //chdir("..");
   exit(0);
}

int encodeFilename (structFilenames normalFilenames[], structFilenames mindreKoedFilenames[], char filename[], 
                  int choice, structIngrediens ingrediens[], structMeal meals[])
{
   int tester;
   if (choice == 1){
      strcpy(filename,scanDatafilename(filename, normalFilenames));
      chdir("recipe");
      tester =forLoopShoppingList(ingrediens,normalFilenames);
      printShoppingList(ingrediens, tester);

      return readDataIngredients(ingrediens, filename, meals);
     
   }
   else if (choice == 2){
      strcpy(filename,scanDatafilename(filename, mindreKoedFilenames));
      chdir("mindrekoedrecipe");
      tester =forLoopShoppingList(ingrediens,mindreKoedFilenames);
      printShoppingList(ingrediens, tester);
      return readDataIngredients(ingrediens, filename, meals);
   }
   return 0;
}

int scanDataBetween (int highestOption, int lowestOption)
{
   int choice = 0;

   do
   {
      if ((choice >= highestOption || choice < lowestOption))
      {
         printf("Dit valg passer ikke med de givne muligheder ");
         fflush(stdin);
         choice = -1;
      }
      printf("Indtast valg: ");   
      scanf("%d", &choice);
      printf("\n");
   } while ((choice >= highestOption || choice < lowestOption));
   
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
   printf("I hjaelp, vil der vaere mulighed for at gaa tilbage til starten, eller gaa til det forrige skridt.\n\n");
}

/* Choosing type of mealplan */
int choiceChooser (void)
{
   int choice;
   int destinations;

   printf("Vaelg en af de nedstaeende muligheder\n");
   printf("1) Standart madplan\n");
   printf("2) Mindre koed\n");
   printf("3) Hjaelp!\n");
   printf("4) Afslut menu\n\n"); 

   choice = scanDataBetween(5, 0);

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
      choice = choiceChooser();
      break;
   case 4:
      exit(0);
      break;
   default:
      break;
   }

   return choice;
}

/* This function reads the ingredients and puts value into a double and ingredient-name into a string,
 * so that we can change the value of how much a person should use
 * From the '$' in txt-file to the int -1 appears, we  read the ingredient volume and ingredient name */
int readDataIngredients (structIngrediens ingrediens[], char filename[], structMeal meals[]) 
{
   int checker = 0, i = 0;
   strcat(filename, ".txt"); 
   FILE *recipe;

   recipe = fopen(filename, "r"); 

   if (recipe == NULL)
   {
      printf("The file name entered isn't viable. Please try again");
      exit(-1);
   }
   
   fscanf(recipe, "%[^;]; %[^;]; %[^;]; %[^;];", meals[i].mealName, meals[i].amountOfPeople, meals[i].preparationTime, meals[i].ingredients);
   
   if (strcmp(filename,"Soendag.txt") != 0 && strcmp(filename,"SoendagMindreKoed.txt") !=0 )
   {
      while (checker != -1)
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
   
   if(strcmp(filename,"soendag.txt") != 0 && strcmp(filename,"SoendagMindrekoed.txt") != 0)
      printf("%s\n", meals[1].procedure);    
}

/*Function reading different files in given directory in a while loop for every file*/
void findingNormalTxt(structFilenames filename[])
{
   struct dirent* recipe;
   int i = 0;
   
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
         i++;
         ++filename[0].amountOfFiles;
      }
   }
}

void findingMindreKoedTxt(structFilenames mindreKoedFilename[])
{
   struct dirent *recipe;
   int i = 0;

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
         ++i;
         mindreKoedFilename[0].amountOfFiles++;
      }
   }
} 

int help (void)
{
   printf("---------------Hjaelp---------------\n\n");
   printf("Mulige funktioner du kan tilgaa her\n\n");
   printf("er: instruktioner, start menu og afslut menu.\n\n");
   printf("Instruktioner viser instruktionerne som blev vist i starten.\n\n");
   printf("Start menu tager dig helt til bage til starten.\n\n");

   printf("1) Instruktioner\n2) Start menu\n");

   return scanDataBetween(3, 0);
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

int forLoopShoppingList(structIngrediens ingrediens[], structFilenames allFilenames[]){
   int i;
   int amountOfIngredients = 0;
   for (i = 0; i<allFilenames[0].amountOfFiles; i++){
      printf("\n \n%d\n \n",amountOfIngredients);
      amountOfIngredients += shoppingList(ingrediens,allFilenames[i].filenames);
   }
   return amountOfIngredients;
}

int shoppingList(structIngrediens ingrediens[], char filename[]){
   int checker = 0;
   int index = 0;
   int amountOfIngrediens = 0;
   FILE *recipe;
   double localVolume = 0;
   char localIngrediensName[400] = ""; 
   strcat(filename, ".txt");
   recipe = fopen(filename, "r");
   if (recipe == NULL)
   {
      printf("The file name entered isn't viable. Please try again");
      EXIT_FAILURE;
   }

   fscanf(recipe, "%*[^;]; %*[^;]; %*[^;]; %*[^;];");
   if (strcmp(filename,"Soendag.txt") != 0 && strcmp(filename,"SoendagMindreKoed.txt") !=0 )
   {
      while (checker != -1){
          printf("%s",filename);
         index = -1;
         printf("test %d\n", amountOfIngrediens);
         fscanf(recipe, "%lf %[^:]: %d", &localVolume, &localIngrediensName, &checker);
         amountOfIngrediens++;
         do{
            index++;
            if (strcmp(ingrediens[index].name, localIngrediensName) == 0){
               ingrediens[index].volume += localVolume;
               amountOfIngrediens--;
            }

            
            else if (strcmp(ingrediens[index].name, "") == 0){
               strcpy(ingrediens[index].name, localIngrediensName);
               ingrediens[index].volume += localVolume;
            }
            else {}
           // printf("%f %s... %f %s (%d) |%d| <%d>\n", ingrediens[index].volume, ingrediens[index].name, localVolume, localIngrediensName, index,strcmp(ingrediens[index].name, localIngrediensName), checker );
            
         }while(strcmp(ingrediens[index].name, localIngrediensName) != 0);

      
      }


   }
  
   fclose(recipe);
    
   return amountOfIngrediens;
}

void printShoppingList(structIngrediens ingrediens[], int amountOfingredients){
   multiplier(1,ingrediens,amountOfingredients);
   int i;
   for (i = 0; i < amountOfingredients; i++)
   printf("%5.3f %s.... %d %d\n", ingrediens[i].volume, ingrediens[i].name , i , amountOfingredients);
}