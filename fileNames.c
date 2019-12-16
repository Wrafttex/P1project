#include "header.h"


/*Function reading different files in given directory in a while loop for every file*/
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

int forLoopShoppingList(structIngrediens ingrediens[], structFilenames allFilenames[])
{
   int i;
   int amountOfIngredients = 0;

   for (i = 0; i<allFilenames[0].amountOfFiles; i++){
      printf("\n \n%d\n \n",amountOfIngredients);
      amountOfIngredients += readDataShoppingList(ingrediens,allFilenames[i].filenames);
   }
   return amountOfIngredients;
}