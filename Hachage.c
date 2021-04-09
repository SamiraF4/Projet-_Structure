#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Chaine.h"

int fonctionCle(int x, int y){
	return (y + (x + y)*(x + y + 1)/2);
}

int fonctionHachage(int k){
	TableHachage *M= sizeof(M);
	double A= (rac(5)-1)/2;
	return (M((k*A)-(k*A)));
}

/*Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y){

}

Reseau* reconstitueReseauHachage(Chaines *C, int M){

}*/


int main(int argc, char const *argv[])
{
	printf("%d\n",fonctionCle(2,3));
	printf("%d\n",fonctionCle(1,1));
	return 0;
}