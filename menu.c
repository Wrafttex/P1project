#include "header.h"

/********************************************************************************/
/*                                                                              */
/* Purpose: The function purpose is to print out the instructions               */
/*                                                                              */
/* Parameters: NONE                                                             */
/*                                                                              */
/* Returns: NONE.                                                               */
/*                                                                              */
/* Notes:                                                                       */
/*                                                                              */
/********************************************************************************/

void instructions (void) 
{
   printf("-------------------------Den Digitale Madplan-------------------------\n\n");
   printf("Alle madplaner gaelder for 7 dage,og inkludere inkoebsliste og opskrifter.\n\n");
   printf("Brug aa, ae og oe i stedet for danske bogstaver.\n\n");
   printf("Vaelg antal personer der skal foelge madplanen.\n\n");
   printf("Hvilken madplan vil du bruge, ud fra de givne valg.\n\n");
   printf("Ved at vaelge en af de to indkoebslister vil den blive vist.\n\n");
   printf("Hvis du har problemmer eller har valgt forkert vlaeg hjaelp.\n\n");
   printf("I hjaelp, vil der vaere mulighed for at gaa tilbage til starten.\n\n");
   printf("Eller aat se instruktionerne igen. Efter madplanen er blevet udskrevet\n\n");
   printf("vil der vaere mulighed for at gaa tilbage ti starten eller afslutte programmet\n\n");
}

/********************************************************************************/
/*                                                                              */
/* Purpose: this function show which possibility the user has, then runs the    */
/*          nexts funtion based on what the user choice                         */
/*                                                                              */
/* Parameters: structFilenames normalFilenames[],                                */
/*   structFilenames mindreKoedFilenames[], structDishName dishes[],            */
/*   int amountOfPeople, structIngrediens groceryListNormal[],                  */
/*   structIngrediens groceryListLessMeat[],                                    */
/*   int amountOfIngredientsInLessMeatShoppingList                              */
/*   int amountOfIngredientsInNormalShoppingList                                */
/*                                                                              */
/* Returns: Choice.                                                             */
/*                                                                              */
/* Notes:                                                                       */
/*                                                                              */
/********************************************************************************/
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
/********************************************************************************/
/*                                                                              */
/* Purpose: it prints out the meals for the weak.                               */
/*                                                                              */
/* Parameters: NONE                                                             */
/*                                                                              */
/* Returns: NONE.                                                               */
/*                                                                              */
/* Notes:  NONE:                                                                */
/*                                                                              */
/********************************************************************************/

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
/********************************************************************************/
/*                                                                              */
/* Purpose: Prints out the Help.                                                */
/*                                                                              */
/* Parameters: NONE                                                             */
/*                                                                              */
/* Returns: scandataBetween.                                                    */
/*                                                                              */
/* Notes:  NONE:                                                                */
/*                                                                              */
/********************************************************************************/
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
/********************************************************************************/
/*                                                                              */
/* Purpose: navigate between Mealplan and instructions                          */
/*                                                                              */
/* Parameters: int destination                                                  */
/*                                                                              */
/* Returns: NONE.                                                               */
/*                                                                              */
/* Notes:  NONE:                                                                */
/*                                                                              */
/********************************************************************************/
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