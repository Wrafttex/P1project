#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LGT 500
#define SMALL_STR_LGT 15
#define MEDIUM_STR_LGT 30

// Magni bruger denne
typedef struct tingredien
{
   double volume;
   char navn [MAX_NAME_LGT];
} singrediens;

typedef struct tretter
{
   char rettensNavn [MAX_NAME_LGT];
   char antalPersoner [MAX_NAME_LGT];
   char forberedningsTid [MAX_NAME_LGT];
   char ingredienser [MAX_NAME_LGT];
   char fremgangsMaade [MAX_NAME_LGT];
} sretter;

/* Prototypes */

int readDataIngredienser (singrediens ingrediens[],char filename[], sretter retter[]);
void readDataBase (void);
void gangerOp (int antalPersoner, singrediens ingrediens[], int reader);
void instructions (void);
int mealplanChooser ();
void scanDataValg (int *valg);
void scanDataAntalPersoner (int *antalPersoner);
char* scanDataFilename (char filename[]);

int main (void)
{
   sretter retter[4];
   int valg;
   int antalPersoner;
   int i;
   char filename[25];
   int reader;
   singrediens ingrediens[25]={0,""};
 
   instructions();
   scanDataAntalPersoner(&antalPersoner);
   valg = mealplanChooser();
   strcpy(filename,scanDataFilename(filename));
   printf("%s",filename);

   reader = readDataIngredienser(ingrediens, filename, retter);
   gangerOp(antalPersoner, ingrediens, reader);
   for (i = 0; i < reader; i++)
   {
      printf("%5.2lf %s\n", ingrediens[i].volume, ingrediens[i].navn);
   }
   printf("%s",retter[1].fremgangsMaade);
   
   return 0;
}


void scanDataValg (int *valg)
{
   scanf("%d", valg);
}

void scanDataAntalPersoner (int *antalPersoner)
{
   printf("Antal personer: ");
   scanf("%d", antalPersoner);
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

      printf("Indkoebslist\n")
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

 int readDataIngredienser (singrediens ingrediens[], char filename[], sretter retter[]) 
 {
   int checker = 0, i = 0;
   strcat(filename, ".txt"); /* f.eks filename = kodboller + .txt, dette vil give filename som kodboller, og dette kan vi bruge til opne filen med */
   FILE *opskrifter;
   if (opskrifter == NULL)
   {
      printf("The file name entered isn't viable. Please try again");

   }
   opskrifter = fopen(filename, "r"); 
   fscanf(opskrifter, "%*[^$]$");
   printf("har gjort foerste fscanf\n");
   while (checker != 69420){
      fscanf(opskrifter, "%lf %[^:]: %d",&ingrediens[i].volume, &ingrediens[i].navn, &checker);
      ++i;
   }
   
    printf("har gjort while\n");
   fscanf(opskrifter,"%[^&]&", &retter[1].fremgangsMaade);
   fclose(opskrifter);

   return i;
 }

void gangerOp(int antalPersoner, singrediens ingrediens[], int reader) 
{
   int i; 
   for (i = 0; i < reader; i++)
   {
      ingrediens[i].volume = antalPersoner * ingrediens[i].volume; 
   }
     
}

/*int jumpAround(){




}*/