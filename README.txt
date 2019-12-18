---Velkommen til README-filen for denDigitaleMadplan.exe---

I dette program kan en madplan præsenteres for ugen.
Gennem programmet bliver du stillet overfor en række af valg i terminalen, hvor du kan
agere efter dit eget ønske. Programmet er som udgangspunktskrevet i programmeringssproget C 
og kompileret med gcc-kompilatoren. exe-filen bliver kørt i dit operativsystems kommandoprompt.

----------------------------------------------------------------------------------------------

Der er vedlagr en exe fil ved navn denDigitaleMadplan.exe, som er en compilet version af
programmet. Ved at køre denne fil vil et vindue åbne med programmet i. Hvis denne exe fil ikke
virker af en eller anden grund er der en makefil inkluderet. For at compile programmet med en
makefil åber du din compiler finder frem til mappen. I compileren skal du skrive "make" ind og
trykke enter. Hvis din compiler ikke godtager makefilen skriv følgende kommandoer i denne
rækkefølge:

gcc -c scanData.c
gcc -c menu.c
gcc -c readData.c
gcc -c fileNames.c
gcc -c printFunctions.c
gcc -c calculations.c
gcc -c changeDir.c
gcc Madspild.c scanData.o menu.o readData.o fileNames.o printFunctions.o calculations.o changeDir.o -ansi -Wall -pedantic -o denDigitaleMadpaln.exe

Hvis kommandoerne er kørt i den rigtige rækkefølge vil der nu være en ny 
denDigitaleMadplan.exe som vil kunne kørers

----------------------------------------------------------------------------------------------

Et par ofte stillede spørgsmål, forsøgt besvaret bedst muligt: 

Hvad gør jeg hvis jeg vil redigere i programmets kildekode? 
- Åben c-filen og rediger efter eget ønske. Husk at kompilere programmet med en kompetent
  kompilator, så programmet bliver opdateret når der er lavet ændringer. 

Hvorfor er programmet lavet? 
- Programmet er lavet i forbindelse med projektgruppens emne om madspild, med formål at mindske
  det. 

----------------------------------------------------------------------------------------------
Du kan lave og initialisere dine egne opskrifter med understående skabelon. 
Tekst i paranteser skal selv angives af brugeren. 
 
Skabelon:

(Opskriftens navn):; 
(Tid i forberedelse): (i minutter);
Ingredienser:;
(Maengde i tal) ? (type af enhed(stk., dl., etc.)). (navn på ingrediens): 1
(sidste maengde) (sidste type af enhed). (sidste ingrediens); -1
Fremgangsmaade:
(skrevet her, ny linje for hvertstep)
&

Den "hjemmelavede" opskrift skal gemmes i en seperat txt-fil i den ønskede mappe mappe. 
Filen skal navngives som den dag på ugen, du ønsker at lave retten ex."Mandag.txt". 
Du kan frit benytte de pre-definerede mapper "recipe" eller "mindrekoedrecipe". 
----------------------------------------------------------------------------------------------
