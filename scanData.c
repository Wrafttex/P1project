#include "header.h"

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