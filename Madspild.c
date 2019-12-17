#include "header.h"

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
   /* Declaring variables used in main */
   char filename[30];
   int amountOfIngredients;
   int amountOfPeople;
   int choice;
   int amountOfIngredientsInNormalShoppingList;
   int amountOfIngredientsInLessMeatShoppingList;

   structMeal meals[4];
   structDishName dishes[7] = {{""}};
   structIngrediens ingrediens[25] = {{0,""}}; /* Declaring 0 to int volume and inserting empty string(char name), which is default setting */
   structIngrediens groceryListNormal[50] = {{0,""}};
   structIngrediens groceryListLessMeat[50]={{0,""}};
   structFilenames normalFilenames[20] = {{"",0}};
   structFilenames mindrekoedFilenames[20] = {{"",0}};

   findingNormalTxt(normalFilenames);
   findingMindreKoedTxt(mindrekoedFilenames);
   amountOfIngredientsInNormalShoppingList = ShoppingListDirections(groceryListNormal, normalFilenames, "recipe");
   amountOfIngredientsInLessMeatShoppingList = ShoppingListDirections(groceryListLessMeat, mindrekoedFilenames, "mindrekoedrecipe");

   do
   {  
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