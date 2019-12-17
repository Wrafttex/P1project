#include "header.h"


/********************************************************************************/
/*                                                                              */
/* Purpose: The function purpose is to change which folder the program is in    */
/* as two different meal plans, and each are in their own folders               */
/*                                                                              */
/* Parameters: structIngrediens shoppinglist[], structFilenames allFilenames[]  */
/*              and char direction[]                                            */
/* Returns: amountofAllIngredients;                                             */
/*                                                                              */
/* Notes: always good idea to change the folder back to the starting point      */
/*                                                                              */
/********************************************************************************/

int ShoppingListDirections(structIngrediens shoppinglist[], structFilenames allFilenames[], char direction[])
{
   int amountOfAllIngredients;
   chdir(direction);
   amountOfAllIngredients = forLoopShoppingList(shoppinglist,allFilenames);
   chdir("..");
   return amountOfAllIngredients;
  
}