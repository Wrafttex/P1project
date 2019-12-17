#include "header.h"


/********************************************************************************/
/*                                                                              */
/* Purpose: The function purpose is to read each txt files name in the folder   */
/* so that we can use it later for checking that the user has written the file  */
/* correctly                                                                    */
/* Parameters:    structFilenames filename[]                                    */
/*                                                                              */
/* Returns: NONE.                                                               */
/*                                                                              */
/* Notes:                                                                       */
/*                                                                              */
/********************************************************************************/

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


/********************************************************************************/
/*                                                                              */
/* Purpose: The function purpose is to read each txt files name in the folder   */
/* so that we can use it later for checking that the user has written the file  */
/* correctly                                                                    */
/* Parameters:    structFilenames filename[]                                    */
/*                                                                              */
/* Returns: NONE.                                                               */
/*                                                                              */
/* Notes:  NONE.                                                                */
/*                                                                              */
/********************************************************************************/


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
/********************************************************************************/
/*                                                                              */
/* Purpose: this function is used to open each file by using a loop, by         */                                                                    
/*          sending one txt file name to readdatashoppinglist                   */                                                                           
/*                                                                              */
/* Parameters: structIngrediens ingrediens[], structFilenames allFilenames[]    */
/*                                                                              */
/* Returns: amountOfIngredients                                                 */
/*                                                                              */
/* Notes:                                                                       */
/*                                                                              */
/********************************************************************************/
int forLoopShoppingList(structIngrediens ingrediens[], structFilenames allFilenames[])
{
   int i;
   int amountOfIngredients = 0;

   for (i = 0; i<allFilenames[0].amountOfFiles; i++){
      amountOfIngredients += readDataShoppingList(ingrediens,allFilenames[i].filenames);
   }
   return amountOfIngredients;
}