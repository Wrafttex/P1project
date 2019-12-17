denDigitaleMadpaln.exe: Madspild.c scanData.o menu.o readData.o fileNames.o printFunctions.o calculations.o changeDir.o
	gcc Madspild.c scanData.o menu.o readData.o fileNames.o printFunctions.o calculations.o changeDir.o -ansi -Wall -pedantic -o denDigitaleMadpaln.exe

scanData.o: scanData.c header.h
	gcc -c scanData.c
menu.o: menu.c header.h
	gcc -c menu.c
readData.o: readData.c header.h
	gcc -c readData.c
fileNames.o: fileNames.c header.h
	gcc -c fileNames.c
printFunctions.o: printFunctions.c header.h
	gcc -c printFunctions.c
calculations.o: calculations.c header.h
	gcc -c calculations.c
changeDir.o: changeDir.c header.h
	gcc -c changeDir.c

clean:
	rm *.o denDigitaleMadplan
