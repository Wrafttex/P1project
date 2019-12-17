#include "header.h"

/********************************************************************************/
/*                                                                              */
/* Purpose: is to print out the recipe                                          */
/*                                                                              */
/* Parameters: NONE                                                             */
/*                                                                              */
/* Returns: NONE.                                                               */
/*                                                                              */
/* Notes:                                                                       */
/*                                                                              */
/********************************************************************************/
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