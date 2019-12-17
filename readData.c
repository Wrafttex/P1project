#include "header.h"


/********************************************************************************/
/*                                                                              */
/* Purpose: to run function based on what the user choose is                    */
/*                                                                              */
/* Parameters: NONE                                                             */
/*                                                                              */
/* Returns: int from funtion readDataRecipe.                                                               */
/*                                                                              */
/* Notes:                                                                       */
/*                                                                              */
/********************************************************************************/
int encodeFilename (structFilenames normalFilenames[], structFilenames mindreKoedFilenames[], char filename[], 
                  int choice, structIngrediens ingrediens[], structMeal meals[], int amountOfPeople)
{
    if (choice == 1 || choice  == 4){
      memcpy(filename,scanDatafilename(filename, normalFilenames),strlen(normalFilenames[6].filenames));
      chdir("recipe");
      return readDataRecipe(ingrediens, filename, meals);
   }
   else if (choice == 2 || choice == 5){
      strcpy(filename,scanDatafilename(filename, mindreKoedFilenames));
      chdir("mindrekoedrecipe");
      return readDataRecipe(ingrediens, filename, meals);
   }

   return 0;
}
/********************************************************************************/
/*                                                                              */
/* Purpose: The function reads the recipe name of each recipe, in both files    */
/*                                                                              */
/* Parameters: structFilenames normalFilenames[],                               */
/*   structFilenames mindreKoedFilenames[], structDishName dishes[], int choice */
/*                                                                              */
/* Returns: NONE.                                                               */
/*                                                                              */
/* Notes:                                                                       */
/*                                                                              */
/********************************************************************************/

void readDataDishNames (structFilenames normalFilenames[], structFilenames mindreKoedFilenames[], structDishName dishes[], int choice)
{
   int i = 0;
   char filename[MAX_NAME_LGT];
   FILE *localRecipe;
   structFilenames localNormalFilenames[20] = {{"",0}};
   structFilenames localMindrekoedFilenames[20] = {{"",0}};
   
   for (i = 0; i < 7; i++)
   {
      strcpy(localNormalFilenames[i].filenames, normalFilenames[i].filenames);
      strcpy(localMindrekoedFilenames[i].filenames, mindreKoedFilenames[i].filenames);
   }
   

   if (choice == 1)
   {
      chdir("recipe");

      for (i = 0; i < 7; i++)
      {
         strcpy(filename,strcat(localNormalFilenames[i].filenames, ".txt"));
         localRecipe = fopen(filename, "r");
         fscanf(localRecipe, "%[^;];", dishes[i].dishName);
         fclose(localRecipe);
      }
   } 
   else if (choice == 2)
   {
      chdir("mindrekoedrecipe");

      for (i = 0; i < 7; i++)
      {
         strcpy(filename,strcat(localMindrekoedFilenames[i].filenames, ".txt"));
         localRecipe = fopen(filename, "r");
         fscanf(localRecipe, "%[^;];", dishes[i].dishName);
         fclose(localRecipe);
      }
   }
   chdir("..");
}

/********************************************************************************/
/*                                                                              */
/* Purpose: first it reads name of the recipe, sentence: amount of people,      */
/*            sentence: preparetime, and the word ingredients                   */
/*            Then it reads the ingredients and puts value into a               */
/*            double and ingredient-name into a string, so that we can change   */
/*            change the value of how much a person should use From the '$'     */
/*            in txt-file to the int -1 appears, we  read the ingredient volume */                                                               
/*            and ingredient name. after it's done with that, then it will read */
/*            procedure 
/* Parameters: NONE                                                             */
/*                                                                              */
/* Returns: NONE.                                                               */
/*                                                                              */
/* Notes:                                                                       */
/*                                                                              */
/********************************************************************************/

int readDataRecipe (structIngrediens ingrediens[], char filename[], structMeal meals[]) 
{
   int checker = 0, i = 0;
   strcat(filename, ".txt"); 
   FILE *recipe;

   recipe = fopen(filename, "r"); 

   if (recipe == NULL)
   {
      printf("The file name entered isn't viable. Please try again");
      exit(-1);
   }
   
   fscanf(recipe, "%[^;]; %[^;]; %[^;]; %[^;];", meals[i].mealName, meals[i].amountOfPeople, meals[i].preparationTime, meals[i].ingredients);
   
   if (strcmp(filename,"Soendag.txt") != 0 && strcmp(filename,"SoendagMindreKoed.txt") !=0 )
   {
      while (checker != -1)
      {
         fscanf(recipe, "%lf %[^:]: %d", &ingrediens[i].volume, ingrediens[i].name, &checker);
         ++i;
      }
   
      fscanf(recipe,"%[^&]&", meals[1].procedure);
   }
   fclose(recipe);

   return i;
}

/********************************************************************************/
/*                                                                              */
/* Purpose: This function reads the ingredients and puts value into a           */
/*            double and ingredient-name into a string, so that we can change   */
/*            change the value of how much a person should use From the '$'     */
/*            in txt-file to the int -1 appears, we  read the ingredient volume */                                                               
/*            and ingredient name, for each file in that folder                 */
/* Parameters: NONE                                                             */
/*                                                                              */
/* Returns: NONE.                                                               */
/*                                                                              */
/* Notes:                                                                       */
/*                                                                              */
/********************************************************************************/

int readDataShoppingList(structIngrediens ingrediens[], char filename[])
{
   int checker = 0;
   int index = 0;
   int amountOfIngrediens = 0;
   FILE *recipe;
   double localVolume = 0;
   char localIngrediensName[100] = "";
   char localfilename[30];
   strcpy(localfilename,filename);
   strcat(localfilename, ".txt");
   recipe = fopen(localfilename, "r");
   
   if (recipe == NULL)
   {
      printf("The file name entered isn't viable. Please try again");
      exit(-1);
   }

   fscanf(recipe, "%*[^;]; %*[^;]; %*[^;]; %*[^;];");
   if (strcmp(localfilename,"Soendag.txt") != 0 && strcmp(localfilename,"SoendagMindreKoed.txt") !=0)
   {
      while (checker != -1){
         index = -1;
         fscanf(recipe, "%lf %[^:]: %d", &localVolume, localIngrediensName, &checker);
         amountOfIngrediens++;
         do{
            index++;
            if (strcmp(ingrediens[index].name, localIngrediensName) == 0){
               ingrediens[index].volume += localVolume;
               amountOfIngrediens--;
            }

            
            else if (strcmp(ingrediens[index].name, "") == 0){
               strcpy(ingrediens[index].name, localIngrediensName);
               ingrediens[index].volume += localVolume;
            }
            else {}
         }while(strcmp(ingrediens[index].name, localIngrediensName) != 0);
      }
   }
   fclose(recipe);

   return amountOfIngrediens;
}