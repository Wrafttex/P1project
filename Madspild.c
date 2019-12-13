#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#define MAX_NAME_LGT 500
//tror jeg kommer til at skift hvordan ingrediens virker fordi jeg må nok få fat type af volume, får at kunne gøre indkøbliste korrekt

typedef struct structDishNameDeclare
{
   char dishName [MAX_NAME_LGT];
} structDishName;

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
int continueProgram (void);
int scanDataAmountOfPeople (void);
int scanDataBetween (int HigestOption, int lowestOption);
int readDataShoppingList(structIngrediens shoppinglist[], char filename[]);
int forLoopShoppingList(structIngrediens shoppinglist[], structFilenames allFilenames[]);
int ShoppingListDirections(structIngrediens shoppinglist[],  structFilenames allFilenames[], char direction[]);
int readDataIngredients (structIngrediens ingrediens[], char filename[], structMeal meals[]);
int encodeFilename (structFilenames normalFilenames[], structFilenames mindreKoedFilenames[], 
                     char filename[], int choice, structIngrediens ingrediens[], structMeal meals[], int amountOfPeople);
int userChoice (structFilenames normalFilenames[], structFilenames mindreKoedFilenames[], structDishName dishes[],
                int amountOfPeople, structIngrediens groceryListNormal[], structIngrediens groceryListLessMeat[],
                int amountOfIngredientsInLessMeatShoppingList, int amountOfIngredientsInNormalShoppingList);
char* scanDatafilename (char filename[], structFilenames allFiles[]);
void instructions (void);
void navFunction(int destination);
void mealPlan(void);
void findingNormalTxt(structFilenames normalFilenames[]);
void findingMindreKoedTxt(structFilenames mindreKoedFilenames[]);
void mealPlanOverview (structDishName dishes[], structFilenames normalFilenames[]);
void printShoppingList(structIngrediens ingrediens[], int amountOfingredients, int amountOfPeople);
void readDataDishNames (structFilenames normalFilenames[], structFilenames mindreKoedFilenames[], structDishName dishes[], int choice);
void multiplier (int amountOfPeople, structIngrediens ingrediens[], int amountOfIngredients);
void loopPrint(structIngrediens ingrediens[], structMeal meals[], int amountOfPeople, char filename[], int amountOfIngredients);


int main (void)
{
   mealPlan();

   return 0;
}

/*******************************************************************************/
/*                                                                             */
/* Purpose: The function purpose is to clean main, so main is more simple      */
/*          and clear to read for other persons.                               */
/* Parameters: NONE                                                            */
/*                                                                             */
/* Returns: NONE.                                                              */
/*                                                                             */
/* Notes:  Functions scanning directories for files.                           */
/*         Function printing user-instructions as output.                      */
/*******************************************************************************/
void mealPlan (void)
{
   /*Declaring variables used in main*/
   char filename[30];
   int amountOfIngredients;
   int amountOfPeople;
   int choice;
   int amountOfIngredientsInNormalShoppingList;
   int amountOfIngredientsInLessMeatShoppingList;

   structMeal meals[4];
   structDishName dishes[7] = {{""}};
   structIngrediens ingrediens[25] = {{0,""}};  /* Declaring 0 to int volume and inserting empty string(char name), which is default setting */
   structIngrediens groceryListNormal[50] = {{0,""}};
   structIngrediens groceryListLessMeat[50]={{0,""}};
   structFilenames normalFilenames[20] = {{"",0}};
   structFilenames mindrekoedFilenames[20] = {{"",0}};

   
   findingNormalTxt(normalFilenames);
   findingMindreKoedTxt(mindrekoedFilenames);
   amountOfIngredientsInNormalShoppingList = ShoppingListDirections(groceryListNormal, normalFilenames, "recipe");
   printf("\n%d\t", amountOfIngredientsInNormalShoppingList);
   amountOfIngredientsInLessMeatShoppingList = ShoppingListDirections(groceryListLessMeat, mindrekoedFilenames, "mindrekoedrecipe");
   printf("\nhello%d", amountOfIngredientsInLessMeatShoppingList);


   do
   {  
      //set dir home
      //chdir
      instructions();

      amountOfPeople = scanDataAmountOfPeople();
   
      choice = userChoice(normalFilenames, mindrekoedFilenames, dishes, amountOfPeople, groceryListNormal, groceryListLessMeat, amountOfIngredientsInLessMeatShoppingList, amountOfIngredientsInNormalShoppingList);
      if (choice != 5 && choice != 6)
      {
         amountOfIngredients = encodeFilename(normalFilenames, mindrekoedFilenames, filename, choice, ingrediens, meals, amountOfPeople);
         chdir("..");
         loopPrint(ingrediens, meals, amountOfPeople, filename, amountOfIngredients);
      }
   } while (continueProgram());
   
}

/*******************************************************************************/
/*                                                                             */
/* Purpose: The purpose of the program is to return to start when programs done*/
/*          without exicute.                                                   */
/* Parameters: NONE                                                            */
/*                                                                             */
/* Returns: Retuner 0 and 1.                                                   */
/*                                                                             */
/* Notes: The user need to write J and N with caps.                            */
/*                                                                             */
/*******************************************************************************/
int continueProgram (void)
{
   char continueValue;

   do
   {
      printf("Vil du koere programmet igen? (J/N) ");
      scanf(" %c", &continueValue);
   } while (continueValue != 'J' && continueValue != 'N');
   
   if (continueValue == 'J')
      return 1;   
   else
      return 0; 
}

int encodeFilename (structFilenames normalFilenames[], structFilenames mindreKoedFilenames[], char filename[], 
                  int choice, structIngrediens ingrediens[], structMeal meals[], int amountOfPeople)
{
    if (choice == 1){
      memcpy(filename,scanDatafilename(filename, normalFilenames),strlen(normalFilenames[6].filenames));
      chdir("recipe");
      return readDataIngredients(ingrediens, filename, meals);
   }
   else if (choice == 2){
      strcpy(filename,scanDatafilename(filename, mindreKoedFilenames));
      chdir("mindrekoedrecipe");
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
   printf("I hjaelp, vil der vaere mulighed for at gaa tilbage til starten.\n\n");
}

/* Choosing type of mealplan */
int userChoice (structFilenames normalFilenames[], structFilenames mindreKoedFilenames[], structDishName dishes[],
                   int amountOfPeople, structIngrediens groceryListNormal[], structIngrediens groceryListLessMeat[],
                            int amountOfIngredientsInLessMeatShoppingList, int amountOfIngredientsInNormalShoppingList)
{
   int choice;
   int destinations;

   printf("Vaelg en af de nedstaeende muligheder\n");
   printf("1) Standard madplan\n");
   printf("2) Mindre koed madplan\n");
   printf("3) Hjaelp!\n");
   printf("4) Normal Indkoebsliste\n");
   printf("5) Mindre koed Indkoebsliste\n");
   printf("6) Afslut menu\n\n"); 

   choice = scanDataBetween(7, 0);

   /*Finding which choice was asked for (my style of using brackets may be different than yours) */
   switch (choice)
   {
   case 1:
      printf("Du har valgt en standard madplan, her er en oversigt.\n");
      printf("\n");
      readDataDishNames(normalFilenames, mindreKoedFilenames, dishes, choice);
      mealPlanOverview(dishes, normalFilenames);
      printf("\n");
      break;
   case 2:
      printf("Du har valgt en madplan med mindre koed, her er en oversigt.\n");
      printf("\n");
      readDataDishNames(normalFilenames, mindreKoedFilenames, dishes, choice);
      mealPlanOverview(dishes, normalFilenames);
      printf("\n");
      break;
   case 3:
      destinations = help();
      navFunction(destinations);
      choice = userChoice(normalFilenames, mindreKoedFilenames, dishes, amountOfPeople, groceryListNormal, groceryListLessMeat, amountOfIngredientsInLessMeatShoppingList, amountOfIngredientsInNormalShoppingList);
      break;
   case 4:
      printShoppingList(groceryListNormal, amountOfIngredientsInNormalShoppingList, amountOfPeople);
      break;
   case 5:
      printShoppingList(groceryListLessMeat, amountOfIngredientsInLessMeatShoppingList, amountOfPeople);
      break;
   case 6:
      exit(0);
      break;
   default:
      break;
   }

   return choice;
}

void mealPlanOverview (structDishName dishes[], structFilenames normalFilenames[])
{
   printf("---------------Madplans oversigt---------------\n");
   printf("%-7s: %s\n", normalFilenames[6].filenames, dishes[6].dishName);
   printf("%-7s: %s\n", normalFilenames[1].filenames, dishes[1].dishName);
   printf("%-7s: %s\n", normalFilenames[5].filenames, dishes[5].dishName);
   printf("%-7s: %s\n", normalFilenames[0].filenames, dishes[0].dishName);
   printf("%-7s: %s\n", normalFilenames[2].filenames, dishes[2].dishName);
   printf("%-7s: %s\n", normalFilenames[4].filenames, dishes[4].dishName);
   printf("%-7s: %s\n", normalFilenames[3].filenames, dishes[3].dishName);
}

void readDataDishNames (structFilenames normalFilenames[], structFilenames mindreKoedFilenames[], structDishName dishes[], int choice)
{
   int i = 0;
   char filename[MAX_NAME_LGT];
   FILE *localRecipe;
   structFilenames localNormalFilenames[20] = {{"",0}};
   structFilenames localMindrekoedFilenames[20] = {{"",0}};
   
   for (i = 0; i < 7; i++)
   {
      strcpy(localNormalFilenames[i].filenames, normalFilenames[i].filenames);
      strcpy(localMindrekoedFilenames[i].filenames, mindreKoedFilenames[i].filenames);
   }
   

   if (choice == 1)
   {
      chdir("recipe");

      for (i = 0; i < 7; i++)
      {
         strcpy(filename,strcat(localNormalFilenames[i].filenames, ".txt"));
         localRecipe = fopen(filename, "r");
         fscanf(localRecipe, "%[^;];", dishes[i].dishName);
         fclose(localRecipe);
      }
   } 
   else if (choice == 2)
   {
      chdir("mindrekoedrecipe");

      for (i = 0; i < 7; i++)
      {
         strcpy(filename,strcat(localMindrekoedFilenames[i].filenames, ".txt"));
         localRecipe = fopen(filename, "r");
         fscanf(localRecipe, "%[^;];", dishes[i].dishName);
         fclose(localRecipe);
      }
   }
   chdir("..");
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
      EXIT_FAILURE;
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
   multiplier(amountOfPeople, ingrediens, amountOfIngredients);
   printf("\n%s \n%s %d \n%s \n%s \n", meals[0].mealName, meals[0].amountOfPeople, amountOfPeople, meals[0].preparationTime, meals[0].ingredients);

   for (i = 0; i < amountOfIngredients; i++)
   {
      printf("%5.2f %s\n", ingrediens[i].volume, ingrediens[i].name);
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
   closedir(dr);
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
   closedir(dr);
} 

int help (void)
{
   printf("---------------Hjaelp---------------\n\n");
   printf("Mulige funktioner du kan tilgaa her\n\n");
   printf("er: instruktioner, start menu og afslut menu.\n\n");
   printf("Instruktioner viser instruktionerne som blev vist i starten.\n\n");
   printf("Start menu tager dig helt til bage til starten.\n\n");

   printf("1) Start menu\n2) Instruktioner\n");

   return scanDataBetween(3, 0);
}

void navFunction (int destination)
{
   switch (destination)
   {
   case 1:
      mealPlan();
      break;
   case 2:
      instructions();
      break;
   default:
      break;
   }
}

int forLoopShoppingList(structIngrediens ingrediens[], structFilenames allFilenames[])
{
   int i;
   int amountOfIngredients = 0;

   for (i = 0; i<allFilenames[0].amountOfFiles; i++){
      printf("\n \n%d\n \n",amountOfIngredients);
      amountOfIngredients += readDataShoppingList(ingrediens,allFilenames[i].filenames);
   }
   return amountOfIngredients;
}

int readDataShoppingList(structIngrediens ingrediens[], char filename[])
{
   int checker = 0;
   int index = 0;
   int amountOfIngrediens = 0;
   FILE *recipe;
   double localVolume = 0;
   char localIngrediensName[100] = "";
   char localfilename[30];
   strcpy(localfilename,filename);
   strcat(localfilename, ".txt");
   printf("%s",filename);
   recipe = fopen(localfilename, "r");
   
   if (recipe == NULL)
   {
      printf("The file name entered isn't viable. Please try again");
      EXIT_FAILURE;
   }

   fscanf(recipe, "%*[^;]; %*[^;]; %*[^;]; %*[^;];");
   if (strcmp(localfilename,"Soendag.txt") != 0 && strcmp(localfilename,"SoendagMindreKoed.txt") !=0)
   {
      while (checker != -1){
         // printf("%s",filename);
         index = -1;
         //printf("test %d\n", amountOfIngrediens);
         fscanf(recipe, "%lf %[^:]: %d", &localVolume, localIngrediensName, &checker);
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
          //printf("%f %s... %f %s (%d) |%d| <%d>\n", ingrediens[index].volume, ingrediens[index].name, localVolume, localIngrediensName, index,strcmp(ingrediens[index].name, localIngrediensName), checker );
            
         }while(strcmp(ingrediens[index].name, localIngrediensName) != 0);
      }
   }
   fclose(recipe);

   return amountOfIngrediens;
}

/*******************************************************************************/
/*                                                                             */
/* Purpose: it prints everything that is in the struct ingredients by using    */
/*             for loop, and a variable that has amount of how many ingredients*/
/*             there is in the Grocery list                                    */
/*                                                                             */
/* Parameters: structIngrediens ingrediens[] contains both the volume and      */
/*                string of the ingredients.                                   */
/*             int amountOfIngredients contains the value for how many         */
/*               ingredients their're in the grocery list                      */
/*             int amountOfPeople contain the number for how many people       */
/*                you're going to make the meal plan for                       */
/* Returns: NONE.                                                              */
/*                                                                             */
/* Notes: it calls the function multipier, because ingredients only holds      */
/*            the volume for one person.                                       */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/

void printShoppingList(structIngrediens ingrediens[], int amountOfIngredients, int amountOfPeople)
{
   int i;
   structIngrediens localingredients[60]={{0,""}};
   for (i = 0; i < amountOfIngredients; i++)
   {
      localingredients[i].volume=ingrediens[i].volume;
      memcpy(localingredients[i].name, ingrediens[i].name, strlen(ingrediens[i].name)+1);
   }
   multiplier(amountOfPeople,localingredients,amountOfIngredients);
   for (i = 0; i < amountOfIngredients; i++)
   printf("%5.3f %s\n", localingredients[i].volume, localingredients[i].name);
}

int ShoppingListDirections(structIngrediens shoppinglist[], structFilenames allFilenames[], char direction[])
{
   int amountOfAllIngredients;
   chdir(direction);
   amountOfAllIngredients = forLoopShoppingList(shoppinglist,allFilenames);
   chdir("..");
   return amountOfAllIngredients;
  
}