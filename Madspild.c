#include <stdio.h>
#include <stdlib.h>

void readDataBase (void);

#define MAX_NAME_LGT 500

typedef struct 
{
   char rettensNavn[MAX_NAME_LGT];
   char antalPersoner[MAX_NAME_LGT];
   char forberedningsTid[MAX_NAME_LGT];
   char Ingredienser[MAX_NAME_LGT];
   char Fremgangsmaade[MAX_NAME_LGT];
} retter;

int main (void)
{
   int valg;
   // retter ret[42] = {"","","","",""};
   /*Displaing on screen*/
   printf("-------Den Digitale Madplan-------\n");
   printf(" Alle madplaner gaelder for 7 dage,\n og inkludere inkoebsliste, opskrifter\n og dato for andvendelse\n\n");
   printf("Vaelg en af de nedstaeende madplaner\n");
   printf("1) Vegansk\n");
   printf("2) Proteinbaseret\n");
   printf("3) Kylling\n");
 
   /*getting input*/
   scanf("%d", &valg);
 
   /*Finding which choice was asked for (my style of using brackets may be different than yours*/
   if (valg == 1){
      printf("Du valgte en vegansk madplan!\n");
   }
   else if (valg == 2){
      printf("Du valgte en proteinbaseret madplan!\n");
   }
   else if (valg == 3){
      printf("Du valgte en madplan baseret paa kylling!\n");
   }
 
   readDataBase();
   
   return 0;
}

/* reads from files */
void readDataBase (void)
{
   retter ret;
   FILE* Opskrifter;

   Opskrifter = fopen("FamilieMadplan.txt", "r");

   if (Opskrifter == NULL) {
      printf("Error\n");
      EXIT_FAILURE;
   }

   fscanf(Opskrifter, "%*s %*s %*s %[^;]; %[^;]; %[^;]; %[^&]& %[^&]&", &ret.rettensNavn, &ret.antalPersoner, &ret.forberedningsTid, &ret.Ingredienser, &ret.Fremgangsmaade);
   printf("%s\n \n%s\n \n%s\n \n%s \n%s", ret.rettensNavn, ret.antalPersoner, ret.forberedningsTid, ret.Ingredienser, ret.Fremgangsmaade);



   fclose(Opskrifter);
}
