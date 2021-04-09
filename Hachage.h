#ifndef __HACHAGE_H__
#define __HACHAGE_H__
#include "Chaine.h"


typedef struct TableHachage {
	int taille;
	CellChaine *tableau;
} *TableHachage;

Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y);
Reseau* reconstitueReseauHachage(Chaines *C, int M);

#endif

