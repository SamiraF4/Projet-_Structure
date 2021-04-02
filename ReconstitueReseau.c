#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Reseau.h"
#include "Chaine.h"
#include "SVGwriter.h"

int main(int argc,char *argv){
  if (argc<3){
    printf("Il n'y a pas assez de paramètres\n");
    return -1;
  }
  int n=atoi(argv[2])
  if (n>=4 || n<=0){
    printf("Erreur de paramètres: l'entier doit être compris 1 et 3\n");
    return -1;
  }
  if(n=1){
    printf("Liste Chainée\n");

  }
  if(n=2){
    printf("Table de hachage\n");
  }
  else {
    printf("Arbre\n");
  }
  return 0;
}
