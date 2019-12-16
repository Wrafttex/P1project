#include "header.h"

int encodeFilename (structFilenames normalFilenames[], structFilenames mindreKoedFilenames[], char filename[], 
                  int choice, structIngrediens ingrediens[], structMeal meals[], int amountOfPeople)
{
    if (choice == 1 || choice  == 4){
      memcpy(filename,scanDatafilename(filename, normalFilenames),strlen(normalFilenames[6].filenames));
      chdir("recipe");
      return readDataIngredients(ingrediens, filename, meals);
   }
   else if (choice == 2 || choice == 5){
      strcpy(filename,scanDatafilename(filename, mindreKoedFilenames));
      chdir("mindrekoedrecipe");
      return readDataIngredients(ingrediens, filename, meals);
   }

   return 0;
}

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

/* This function reads the ingredients and puts value into a double and ingredient-name into a string,
 * so that we can change the value of how much a person should use
 * From the '$' in txt-file to the int -1 appears, we  read the ingredient volume and ingredient name */
int readDataIngredients (structIngrediens ingrediens[], char filename[], structMeal meals[]) 
{
   int checker = 0, i = 0;
   strcat(filename, ".txt"); 
   FILE *recipe;

   recipe = fopen(filename, "r"); 

   if (recipe == NULL)
   {
      printf("The file name entered isn't viable. Please try again");
      EXIT_FAILURE;
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
   printf("%s",filename);
   recipe = fopen(localfilename, "r");
   
   if (recipe == NULL)
   {
      printf("The file name entered isn't viable. Please try again");
      EXIT_FAILURE;
   }

   fscanf(recipe, "%*[^;]; %*[^;]; %*[^;]; %*[^;];");
   if (strcmp(localfilename,"Soendag.txt") != 0 && strcmp(localfilename,"SoendagMindreKoed.txt") !=0)
   {
      while (checker != -1){
         // printf("%s",filename);
         index = -1;
         //printf("test %d\n", amountOfIngrediens);
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
          //printf("%f %s... %f %s (%d) |%d| <%d>\n", ingrediens[index].volume, ingrediens[index].name, localVolume, localIngrediensName, index,strcmp(ingrediens[index].name, localIngrediensName), checker );
            
         }while(strcmp(ingrediens[index].name, localIngrediensName) != 0);
      }
   }
   fclose(recipe);

   return amountOfIngrediens;
}