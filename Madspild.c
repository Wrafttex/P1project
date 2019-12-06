#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LGT 500
#define SMALL_STR_LGT 15
#define MEDIUM_STR_LGT 30

// Magni bruger denne
typedef struct structIngrediensDeclare
{
   double volume;
   char name [MAX_NAME_LGT];
} structIngrediens;

typedef struct structMealDeclare
{
   char mealName [MAX_NAME_LGT];
   char amountOfPeople [MAX_NAME_LGT];
   char preparationTime [MAX_NAME_LGT];
   char ingredients [MAX_NAME_LGT];
   char procedure [MAX_NAME_LGT];
} structMeal;

/* Prototypes */
int readDataIngredients (structIngrediens ingrediens[],char filename[], structMeal meals[]);
void multiplier (int amountOfPeople, structIngrediens ingrediens[], int amountOfIngredients);
void instructions (void);
int mealplanChooser ();
int scanDataChooser (void);
int scanDataAmountOfPeople (void);
char* scanDatafilename (char filename[]);
void loopPrint(structIngrediens ingrediens[], structMeal meals[],int amountOfPeople, char filename[], int amountOfIngredients);

int main (void)
{
   structMeal meals[4];
   int choice;
   int amountOfPeople;
   int i;
   char filename[25];
   int amountOfIngredients;
   structIngrediens ingrediens[25]={0,""};
 
   instructions();
   amountOfPeople = scanDataAmountOfPeople();
   choice = mealplanChooser();
   
   strcpy(filename,scanDatafilename(filename));

   printf("%s",filename); // Test

   amountOfIngredients = readDataIngredients(ingrediens, filename, meals);
   multiplier(amountOfPeople, ingrediens, amountOfIngredients);
   loopPrint(ingrediens, meals, amountOfPeople, filename, amountOfIngredients);
   return 0;
}

int scanDataChooser (void)
{
   int choice = 0;
   do
   {
      if ((choice >= 5 || choice < 0))
      {
         printf("Dit valg passer ikke med de givne muligheder ");
         fflush(stdin);
         choice = -1;
      }
         
      scanf("%d", &choice);
   } while ((choice >= 5 || choice < 0));
   
   return choice;
}

int scanDataAmountOfPeople(void)
{
   int amountOfPeople = 0;
   
   do
   {
      printf("Antal personer: ");
      scanf("%d", &amountOfPeople);
   } while (!(amountOfPeople > 0));
   
   return amountOfPeople;
}

/* scans for which file you want to access, and puts into a char array that is called filnavn*/
char* scanDatafilename (char filename[])
{
   int i;
   int daysInAWeek = 7;
   int inputTruthValue = 0;
   char weekdays[7][8] = {"Mandag", "Tirsdag", "Onsdag", "Torsdag", "Fredag", "Loerdag", "Soendag"};

   do
   {
      printf("Hvilken dag vil du se madplan for, foerste bogstav skal vaere caps: ");
      scanf("%s", filename);
      fflush(stdin);
      for(i = 0; i < daysInAWeek; ++i)
      {
         if(strcmp(filename, weekdays[i]) == 0)
         {
            inputTruthValue = 1;
         }
      }
   } while (inputTruthValue == 0);
  
   return filename;
}

/* Instruktioner for brug af madplanen */
void instructions (void) 
{
   printf("-------Den Digitale Madplan-------\n");
   printf("Alle madplaner gaelder for 7 dage,\nog inkludere inkoebsliste, opskrifter.\n\n");
   printf("Brug aa, ae og oe i stedet for danske bogstaver.\n");
   printf("Vaelg antal personer der skal foelge madplanen.\n");
   printf("Hvilken madplan vil du bruge, ud fra de givne valg.\n");
   printf("Ved at trykke paa (i) vil indkoebslisten blive vist.\n");
   printf("Hvis du har problemmer eller har valgt forkert tryk paa (h) for hjaelp.\n");
   printf("I hjaelp\n\n");
}

/* Vælger type af madplan */
int mealplanChooser (void)
{
   int choice;
   printf("Vaelg en af de nedstaeende madplaner\n");
   printf("1) Den normale\n");
   printf("2) Mindre koed\n");
   printf("3) indkoebsliste\n");
   printf("4) Afslut menu\n"); 

   choice = scanDataChooser();

   /*Finding which choice was asked for (my style of using brackets may be different than yours */
   if (choice == 1)
   {
      // Normal madplan
      printf("Normal Madplan\n");
   }
   else if (choice == 2)
   {
      // Mindre kød
      printf("Madplan med mindre koed\n");
   }
   else if (choice == 3)
   {

      printf("Indkoebsliste\n");
   }
   else if (choice == 4)
   {
      printf("Afslut menu!\n");
      exit(0);
   }

   return choice;
}

/* This function reads the ingrediens and puts it into a double and a string,
 * so that we can change the value of how much a person should use ;D
 * From the '$' in the file to the int 69420 appears, we read the ingredient volume and ingredient name */

 int readDataIngredients (structIngrediens ingrediens[], char filename[], structMeal meals[]) 
 {
   int checker = 0, i = 0;
   strcat(filename, ".txt"); /* f.eks filnavn = kodboller + .txt, dette vil give filnavn som kodboller, og dette kan vi bruge til opne filen med */
   FILE *recipe;
   
   if (recipe == NULL)
   {
      printf("The file name entered isn't viable. Please try again");
   }

   recipe = fopen(filename, "r"); 
   fscanf(recipe, "%[^;]; %[^;]; %[^;]; %[^;];", &meals[i].mealName, &meals[i].amountOfPeople, &meals[i].preparationTime, &meals[i].ingredients);
   
   if (strcmp(filename,"Soendag.txt")!=0){
      while (checker != 69420){
      fscanf(recipe, "%lf %[^:]: %d",&ingrediens[i].volume, &ingrediens[i].name, &checker);
      ++i;
    }
   
   fscanf(recipe,"%[^&]&", &meals[1].procedure);
   }
   fclose(recipe);

   return i;
 }

/*Funktion der ganger mængden af ingredienser op med det valgte antal af personer*/
void multiplier(int amountOfPeople, structIngrediens ingrediens[], int amountOfIngredients) 
{
   int i; 
   for (i = 0; i < amountOfIngredients; i++)
   {
      ingrediens[i].volume = amountOfPeople * ingrediens[i].volume; 
   } 
}

/*Function der printer */

void loopPrint(structIngrediens ingrediens[], structMeal meals[],int amountOfPeople, char filename[], int amountOfIngredients){
   int i;
   printf("\n%s \n%s %d \n%s \n%s \n",meals[0].mealName,meals[0].amountOfPeople, amountOfPeople, meals[0].preparationTime, meals[0].ingredients);
   for (i = 0; i < amountOfIngredients; i++)
   {
      printf("%5.2lf %s\n", ingrediens[i].volume, ingrediens[i].name);
   }
   if(strcmp(filename,"soendag.txt")!=0)
      printf("%s\n",meals[1].procedure);   
}