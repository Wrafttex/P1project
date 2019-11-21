#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    int choice;
   
   /*Displaing on screen*/
   printf("-------Den Digitale Madplan-------\n");
   printf(" Alle madplaner gaelder for 7 dage,\n og inkludere inkoebsliste, opskrifter\n og dato for andvendelse\n\n");
   printf("Vaelg en af de nedstaeende madplaner\n");
   printf("1) Vegansk\n");
   printf("2) Proteinbaseret\n");
   printf("3) Kylling\n");
 
   /*getting input*/
   scanf("%d", &choice);
 
   system("CLS");
 
   /*Finding which choice was asked for (my style of using brackets may be different than yours*/
   if (choice == 1){
      printf("Du valgte en vegansk madplan!\n");
   }
   else if (choice == 2){
      printf("Du valgte en proteinbaseret madplan!\n");
   }
   else if (choice == 3){
      printf("Du valgte en madplan baseret paa kylling!\n");
   }
 
   system("PAUSE");
   return 0;
}
