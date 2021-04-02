#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Reseau.h"

Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){
  /*Variable cellule et noeud*/
  CellNoeud *c=R->noeuds;
  Noeud *n;

  /*Parcours des noeuds du réseau*/
  while(n){
    n=c->nd;
    /*Si x et y sont le même alors on retourne le noeud*/
    if(n->x=x && n->y=y){
      return n;
    }
    c=c->suiv;
  }

  /*Si le noeud n'existe pas dans le réseau*/
  n=R->noeuds->nd;//on sauvegarde le premier noeud

  /*On alloue un CellNoeud et on le met dans le reseau*/
  c=(CellNoeud *)malloc(sizoef(CellNoeud));
  if(!c){
    printf("Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y) Erreur d'allocution de CellNoeud\n");
    return NULL;
  }
  c->suiv=R->noeuds;
  R->noeuds=c;

  /*On alloue un noeud et on l'affecte à la cellule et  on retourne le noeud*/
  Noeud *m=(Noeud *)malloc(sizeof(Noeud));
  if(m!){
    printf("Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y) Erreur d'allocution de Noeud\n");
    return NULL;
  }
  m->num=R->nbNoeuds+1;
  m->x=x;
  m->y=y;
  m->voisins=NULL;
  c->nd=m;
  R->nbNoeuds++;
  return m;
}

Reseau* reconstitueReseauListe(Chaines *C){
  if (c){
    Reseau* R=(Reseau *)malloc(sizeof(Reseau));
    if(R!){
      printf("Reseau* reconstitueReseauListe(Chaines *C) Erreur d'allocution de Reseau\n");
      return NULL;
    }
    R->nbNoeuds=0;
    R->gamma=c->gamma;
    R->noeuds=NULL;
    R->commodites=NULL;
    CellChaine* tmp=c->chaines;
    while(tmp){
      CellPoint* ptmp=tmp->points;
      Noeuds* a,b;
      while(ptmp && ptmp->suiv){
        a=rechercheCreeNoeudListe(R,ptmp->x,ptmp->y);
        b=rechercheCreeNoeudListe(R,ptmp->suiv->x,ptmp->suiv->y);
        if(!a || !b){
          
        }
        ptmp=ptmp->suiv;

      }
      printf("\n");
      tmp=tmp->suiv;
    }
  }
}
