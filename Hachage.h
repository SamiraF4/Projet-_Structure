#ifndef __HACHAGE_H__
#define __HACHAGE_H__
#include "Chaine.h"


typedef struct table {
int nE;/*nombre d’elements contenus dans la table de hachage */
int m;/*taille de la table de hachage */
CellNoeud ** N;/*table de hachage avec resolution des collisions par chainage */
} TableHachage;

Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y);
Reseau* reconstitueReseauHachage(Chaines *C, int M);

#endif

