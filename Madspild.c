#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_LGT 500
#define SMALL_STR_LGT 15
#define MEDIUM_STR_LGT 30

// Magni bruger denne
typedef struct
{
   double volume;
   char navn [MAX_NAME_LGT];
} singrediens;

typedef struct 
{
   char rettensNavn [MAX_NAME_LGT];
   char antalPersoner [MAX_NAME_LGT];
   char forberedningsTid [MAX_NAME_LGT];
   char ingredienser [MAX_NAME_LGT];
   char fremgangsMaade [MAX_NAME_LGT];
} retter;

void readDataIngredienser(singrediens ingrediens[]);
void readDataBase (void);
void gangerOp(int antalPersoner, singrediens ingrediens[]);

int main (void)
{
   int valg;
   int antalPersoner;
   int i;

   singrediens ingrediens[10]={0,""};
   printf("-------Den Digitale Madplan-------\n");
   printf(" Alle madplaner gaelder for 7 dage,\n og inkludere inkoebsliste, opskrifter\n og dato for andvendelse\n\n");
   printf("Vaelg en af de nedstaeende madplaner\n");
   printf("1) Vegansk\n");
   printf("2) Proteinbaseret\n");
   printf("3) Kylling\n");
 
   /*getting input*/
   scanf("%d", &valg);

   printf("Antal personer: ");
   scanf("%d", &antalPersoner);
 
   /*Finding which choice was asked for (my style of using brackets may be different than yours */
   if (valg == 1){
      printf("Du valgte en vegansk madplan!\n");
   }
   else if (valg == 2){
      printf("Du valgte en proteinbaseret madplan!\n");
   }
   else if (valg == 3){
      printf("Du valgte en madplan baseret paa kylling!\n");
   }
   else if (valg == 4){
      printf("Indkoebsliste!\n");
   }
   else if (valg == 5){
      printf("Afslut menu!\n");
   }
   //readDataBase();
   readDataIngredienser(ingrediens);
   gangerOp(antalPersoner, ingrediens);
   size_t n = (sizeof(ingrediens)/sizeof(singrediens));
   for (i = 0; i < n; i++)
   {
      printf("%5.2lf %s\n", ingrediens[i].volume, ingrediens[i].navn);
   }
   
   return 0;
}

/* reads from files */
/*
void readDataBase (void)
{
   retter ret;
   FILE* opskrifter;

   opskrifter = fopen("SingleMadplan.txt", "r");

   if (opskrifter == NULL) {
    }

   fscanf(opskrifter, "%*s %*s %*s %[^;]; %[^;]; %[^;]; %[^&]& %[^&]&", &ret.rettensNavn, &ret.antalPersoner, &ret.forberedningsTid, &ret.ingredienser, &ret.Fremgangsmaade);
   printf("%s\n \n%s\n \n%s\n \n%s \n%s", ret.rettensNavn, ret.antalPersoner, ret.forberedningsTid, ret.ingredienser, ret.fremgangsmaade);

   fclose(opskrifter);
} 
*/
/* This function reads the ingrediens and puts it into a double and a string,
 * so that we can change the value of how much a person should use ;D
 * From the '$' in the file to the int 69420 appears, we read the ingredient volume and ingredient name */

 void readDataIngredienser (singrediens ingrediens[]) 
 {
   int checker = 0, i = 0;
   FILE* opskrifter;
   opskrifter = fopen("SingleMadplan.txt", "r"); 
   fscanf(opskrifter,"%*[^$]$");
   while (checker != 69420){
      fscanf(opskrifter, "%lf %[^:]: %d",&ingrediens[i].volume, &ingrediens[i].navn, &checker);
      ++i; 
   }
   fclose(opskrifter);
 }


void gangerOp(int antalPersoner, singrediens ingrediens[]) 
{
   int i; 
   size_t n= (sizeof(ingrediens)/sizeof(singrediens));
   for (i = 0; i < n; i++)
   {
      ingrediens[i].volume = antalPersoner * ingrediens[i].volume; 
      printf("kører den? \n");
   }
     
}
