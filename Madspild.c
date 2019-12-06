#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LGT 500
#define SMALL_STR_LGT 15
#define MEDIUM_STR_LGT 30

// Magni bruger denne
typedef struct structIngredien
{
   double volume;
   char navn [MAX_NAME_LGT];
} singrediens;

typedef struct structRetter
{
   char rettensNavn [MAX_NAME_LGT];
   char antalPersoner [MAX_NAME_LGT];
   char forberedningsTid [MAX_NAME_LGT];
   char ingredienser [MAX_NAME_LGT];
   char fremgangsMaade [MAX_NAME_LGT];
} sretter;

/* Prototypes */
int readDataIngredienser (structIngrediens ingrediens[],char filename[], structRetter retter[]);
void gangerOp (int antalPersoner, structIngrediens ingrediens[], int antalIngrediens);
void instructions (void);
int mealplanChooser ();
int scanDataValg (void);
int scanDataAntalPersoner (void);
char* scanDataFilename (char filename[]);

int main (void)
{
   structRetter retter[4];
   int valg;
   int antalPersoner;
   int i;
   char filename[25];
   int antalIngrediens;
   structIngrediens ingrediens[25]={0,""};
 
   instructions();
   antalPersoner = scanDataAntalPersoner();
   valg = mealplanChooser();
   strcpy(filename,scanDataFilename(filename));

   printf("%s",filename); // Test

   antalIngrediens = readDataIngredienser(ingrediens, filename, retter);
   gangerOp(antalPersoner, ingrediens, antalIngrediens);
   printf("\n%s \n%s %d \n%s \n%s \n",retter[0].rettensNavn,retter[0].antalPersoner, antalPersoner, retter[0].forberedningsTid, retter[0].ingredienser);
   for (i = 0; i < antalIngrediens; i++)
   {
      printf("%5.2lf %s\n", ingrediens[i].volume, ingrediens[i].navn);
   }
   printf("%s",retter[1].fremgangsMaade);
   
   return 0;
}

int scanDataValg (void)
{
   int valg;
   scanf("%d", &valg);
   return valg;
}

/* HUSK AT FIXE */
int scanDataAntalPersoner (void)
{
   int antalPersoner;
   printf("Antal personer: ");
   scanf("%d", &antalPersoner);
   return antalPersoner;
}

char* scanDataFilename (char filename[])
{
   printf("filename is SingleMadplan: ");
   scanf("%s", filename);
   return filename;
}

/* Instruktioner for brug af madplanen */
void instructions (void) 
{
   printf("-------Den Digitale Madplan-------\n");
   printf("Alle madplaner gaelder for 7 dage,\nog inkludere inkoebsliste, opskrifter.\n\n");
   printf("Vaelg antal personer der skal foelge madplanen.\n");
   printf("Hvilken madplan vil du bruge, ud fra de givne valg.\n");
   printf("Ved at trykke paa (i) vil indkoebslisten blive vist.\n");
   printf("Hvis du har problemmer eller har valgt forkert tryk paa (h) for hjaelp.\n");
   printf("I hjaelp\n\n");
}

/* Vælger ens madplan */
int mealplanChooser (void)
{
   int valg;
   printf("Vaelg en af de nedstaeende madplaner\n");
   printf("1) Den normale\n");
   printf("2) Mindre koed\n");
   printf("3) Afslut menu\n"); 

   scanDataValg(&valg); // Du er så smart kure :O

   /*Finding which choice was asked for (my style of using brackets may be different than yours */
   if (valg == 1)
   {
      // Normal madplan
      printf("Normal Madplan\n");
   }
   else if (valg == 2)
   {
      // Mindre kød
      printf("Madplan med mindre koed\n");
   }
   else if (valg == 3)
   {

      printf("Indkoebslist\n");
   }
   else if (valg == 4)
   {
      printf("Afslut menu!\n");
      EXIT_SUCCESS;
   }

   return valg;
}

/* This function reads the ingrediens and puts it into a double and a string,
 * so that we can change the value of how much a person should use ;D
 * From the '$' in the file to the int 69420 appears, we read the ingredient volume and ingredient name */

 int readDataIngredienser (structIngrediens ingrediens[], char filename[], structRetter retter[]) 
 {
   int checker = 0, i = 0;
   strcat(filename, ".txt"); /* f.eks filename = kodboller + .txt, dette vil give filename som kodboller, og dette kan vi bruge til opne filen med */
   FILE *opskrifter;
   if (opskrifter == NULL)
   {
      printf("The file name entered isn't viable. Please try again");
   }

   opskrifter = fopen(filename, "r"); 
   fscanf(opskrifter, "%[^;]; %[^;]; %[^;]; %[^;];", &retter[i].rettensNavn, &retter[i].antalPersoner, &retter[i].forberedningsTid, &retter[i].ingredienser);
   while (checker != 69420){
      fscanf(opskrifter, "%lf %[^:]: %d",&ingrediens[i].volume, &ingrediens[i].navn, &checker);
      ++i;
   }
   
   fscanf(opskrifter,"%[^&]&", &retter[1].fremgangsMaade);
   fclose(opskrifter);

   return i;
 }

void gangerOp(int antalPersoner, structIngrediens ingrediens[], int antalIngrediens) 
{
   int i; 
   for (i = 0; i < antalIngrediens; i++)
   {
      ingrediens[i].volume = antalPersoner * ingrediens[i].volume; 
   }
     
}

/*int jumpAround(){




}*/