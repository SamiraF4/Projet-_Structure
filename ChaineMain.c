#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Chaine.h"
#include "SVGwriter.h"

void afficheChainesSVG(Chaines *C, char* nomInstance){
    int i;
    double maxx=0,maxy=0,minx=1e6,miny=1e6;
    CellChaine *ccour;
    CellPoint *pcour;
    double precx,precy;
    SVGwriter svg;
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        while (pcour!=NULL){
            if (maxx<pcour->x) maxx=pcour->x;
            if (maxy<pcour->y) maxy=pcour->y;
            if (minx>pcour->x) minx=pcour->x;
            if (miny>pcour->y) miny=pcour->y;
            pcour=pcour->suiv;
        }
    ccour=ccour->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        SVGlineRandColor(&svg);
        SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
        precx=pcour->x;
        precy=pcour->y;
        pcour=pcour->suiv;
        while (pcour!=NULL){
            SVGline(&svg,500*(precx-minx)/(maxx-minx),500*(precy-miny)/(maxy-miny),500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            precx=pcour->x;
            precy=pcour->y;
            pcour=pcour->suiv;
        }
        ccour=ccour->suiv;
    }
    SVGfinalize(&svg);
}

int main(){
  FILE *f=fopen("00014_burma.cha","r");
  if (!f) return -1;
  Chaines* c=lectureChaines(f);
  afficheChainesSVG(c,"resulat");
  afficher(c);
  printf("%.2f\n",longueurChaine(c->chaines));
  printf("%.2f\n",longueurTotale(c));
  printf("%d\n",comptePointsTotal(c));
  fclose(f);
  f=fopen("resultat","w");
  if (!f) return -1;
  ecrireChaines(c,f);
  fclose(f);
  liberer(c);
  return 0;
}
