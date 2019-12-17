#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#define MAX_NAME_LGT 500

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
int help(void);
int continueProgram (void);
int scanDataAmountOfPeople (void);
int scanDataBetween (int HigestOption, int lowestOption);
int readDataShoppingList(structIngrediens shoppinglist[], char filename[]);
int forLoopShoppingList(structIngrediens shoppinglist[], structFilenames allFilenames[]);
int ShoppingListDirections(structIngrediens shoppinglist[],  structFilenames allFilenames[], char direction[]);
int readDataRecipe (structIngrediens ingrediens[], char filename[], structMeal meals[]);
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

#endif /* HEADER_H */
