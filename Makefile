EXEC = ChaineMain

all: ChaineMain

ChaineMain: ChaineMain.o Chaine.o SVGwriter.o
	gcc -o ChaineMain ChaineMain.o Chaine.o SVGwriter.o -lm

ChainMain.o:ChaineMain.c Chaine.h SVGwriter.h
	gcc -Wall -c main.c

SVGwriter.o: SVGwriter.c SVGwriter.h
	gcc -Wall -c SVGwriter.c

Chaine.o: Chaine.c Chaine.h
	gcc -Wall -c Chaine.c -lm




clean :
	rm -f *.o
	rm -f prog
