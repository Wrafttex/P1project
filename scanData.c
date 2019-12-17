#include "header.h"
/********************************************************************************/
/*                                                                              */
/* Purpose: This function reads the ingredients and puts value into a           */
/*            double and ingredient-name into a string, so that we can change   */
/*            change the value of how much a person should use From the '$'     */
/*            in txt-file to the int -1 appears, we  read the ingredient volume */                                                               
/*            and ingredient name                                               */
/* Parameters: NONE                                                             */
/*                                                                              */
/* Returns: NONE.                                                               */
/*                                                                              */
/* Notes:                                                                       */
/*                                                                              */
/********************************************************************************/

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
/********************************************************************************/
/*                                                                              */
/* Purpose: This function reads what the user input, and checks that it is      */
/*            inside of the parementers, and that a letter will be decline      */
/* Parameters: NONE                                                             */
/*                                                                              */
/* Returns: NONE.                                                               */
/*                                                                              */
/* Notes:                                                                       */
/*                                                                              */
/********************************************************************************/
int scanDataAmountOfPeople(void)
{
   int amountOfPeople = 0;
   
   do
   {
      printf("\nAntal personer: ");
      scanf("%d", &amountOfPeople);
      printf("\n");
      fflush(stdin);
   } while (!(amountOfPeople > 0));
   
   return amountOfPeople;
}
/********************************************************************************/
/*                                                                              */
/* Purpose: scans for which file you want to access,                            */
/*          and puts into a char array that is called filename                  */
/*                                                                              */
/* Parameters: NONE                                                             */
/*                                                                              */
/* Returns: Filename.                                                           */
/*                                                                              */
/* Notes: Do-while-loop scanning for given day of the week,                     */
/*  comparing chosen weekday(declared in weekdays string array)                 */
/* with filename, returning filename                                            */ 
/********************************************************************************/

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