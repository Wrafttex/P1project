#include "header.h"

/********************************************************************************/
/*                                                                              */
/* Purpose: The function purpose is to multiply ingredients with                */
/* how many people                                                              */
/* Parameters: Int amountOfPeople, structIngrediens ingrediens[] and            */
/*             int amountOfIngredients.                                         */
/* Returns: NONE.                                                               */
/*                                                                              */
/* Notes:  uses amount of ingredients to how many ingdrients their needs to be  */
/*         multiply                                                             */
/********************************************************************************/

void multiplier(int amountOfPeople, structIngrediens ingrediens[], int amountOfIngredients) 
{
   int i; 
   for (i = 0; i < amountOfIngredients; i++)
   {
      ingrediens[i].volume = amountOfPeople * ingrediens[i].volume; 
   } 
}