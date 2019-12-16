#include "header.h"

int ShoppingListDirections(structIngrediens shoppinglist[], structFilenames allFilenames[], char direction[])
{
   int amountOfAllIngredients;
   chdir(direction);
   amountOfAllIngredients = forLoopShoppingList(shoppinglist,allFilenames);
   chdir("..");
   return amountOfAllIngredients;
  
}