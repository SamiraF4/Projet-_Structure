#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Reseau.h"
#include "Chaine.h"

Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){
  /*Variable cellule et noeud*/
  CellNoeud *c=R->noeuds;
  Noeud *n;

  /*Parcours des noeuds du réseau*/
  while(n){
    n=c->nd;
    /*Si x et y sont le même alors on retourne le noeud*/
    if((n->x=x) && (n->y=y)){
      return n;
    }
    c=c->suiv;
  }

  /*Si le noeud n'existe pas dans le réseau*/
  n=R->noeuds->nd;//on sauvegarde le premier noeud

  /*On alloue un CellNoeud et on le met dans le reseau*/
  c=(CellNoeud *)malloc(sizeof(CellNoeud));
  if(!c){
    printf("Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y) Erreur d'allocation de CellNoeud\n");
    return NULL;
  }
  c->suiv=R->noeuds;
  R->noeuds=c;

  /*On alloue un noeud et on l'affecte à la cellule et  on retourne le noeud*/
  Noeud *m=(Noeud *)malloc(sizeof(Noeud));
  if(!m){
    printf("Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y) Erreur d'allocation de Noeud\n");
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

void libererReseau(Reseau *R){
  if(R){
    CellNoeud* cn=R->noeuds;
    while(cn){
      R->noeuds=cn->suiv;
      Noeud*n=cn->nd;
      CellNoeud* v=n->voisins;
      while(v){
        n->voisins=v->suiv;
        free(v);
        v=n->voisins;
      }
      free(cn);
      cn=R->noeuds;
    }
    CellCommodite *c=R->commodites;
    while(c){
      R->commodites=c->suiv;
      free(c);
      c=R->commodites;
    }
    free(R);
  }
}

Reseau* reconstitueReseauListe(Chaines *C){
  if (C){
    Reseau* R=(Reseau *)malloc(sizeof(Reseau));
    if(!R){
      printf("Reseau* reconstitueReseauListe(Chaines *C) Erreur d'allocation de Reseau\n");
      return NULL;
    }
    R->nbNoeuds=0;
    R->gamma=C->gamma;
    R->noeuds=NULL;
    R->commodites=NULL;
    CellChaine* tmp=C->chaines;
    while(tmp){
      CellPoint* ptmp=tmp->points;
      CellPoint* debut=tmp->points;
      Noeud* a;
      Noeud* b;
      while(ptmp && ptmp->suiv){
        a=rechercheCreeNoeudListe(R,ptmp->x,ptmp->y);
        b=rechercheCreeNoeudListe(R,ptmp->suiv->x,ptmp->suiv->y);
        if(!a || !b){
          printf("Reseau* reconstitueReseauListe(Chaines *C) Erreur de noeuds\n");
          libererReseau(R);
          return NULL;
        }
        CellNoeud* A=(CellNoeud *)malloc(sizeof(CellNoeud));
        if(!A){
          printf("Reseau* reconstitueReseauListe(Chaines *C)  Erreur d'allocation de A\n");
          libererReseau(R);
          return NULL;
        }
        CellNoeud* B=(CellNoeud *)malloc(sizeof(CellNoeud));
        if(!B){
          printf("Reseau* reconstitueReseauListe(Chaines *C)  Erreur d'allocation de A\n");
          libererReseau(R);
          return NULL;
        }
        A->nd=a;
        A->suiv=a->voisins;
        a->voisins=A;
        B->nd=b;
        B->suiv=b->voisins;
        b->voisins=B;
        ptmp=ptmp->suiv;
      }
      /*Allocation de la commodité et on le place dans le Reseau*/
      CellCommodite *c=(CellCommodite *)malloc(sizeof(CellCommodite));
      if(!c){
        printf("Reseau* reconstitueReseauListe(Chaines *C)  Erreur d'allocation de c\n");
        libererReseau(R);
        return NULL;
      }
      c->extrA->x=debut->x;
      c->extrA->y=debut->y;

      c->extrB->x=ptmp->x;
      c->extrB->y=ptmp->y;

      c->suiv=R->commodites;
      R->commodites=c;
      tmp=tmp->suiv;
    }
  }
  return NULL;
}




int nbLiaisons(Reseau *R){
  if(R){
    int res=0;
    CellNoeud *noeuds=R->noeuds;
    while(noeuds){
      CellNoeud *voisins=noeuds->nd->voisins;
      while(voisins){
        res++;
        voisins=voisins->suiv;
      }
      noeuds=noeuds->suiv;
    }
    return res/2;
  }
  printf("il n'y a pas de réseau\n");
  return -1;
}

int nbCommodites(Reseau *R){
  if(R){
    int res=0;
    CellCommodite *c=R->commodites;
    while(c){
      res++;
      c=c->suiv;
    }
    return 0;
  }
  printf("Il n'y a pas de Reseau\n");
  return -1;
}

void ecrireReseau(Reseau *R, FILE *f){
  if (!(R && f)){
    printf("Problème de paramètre\n");
  }
  else{
    fprintf(f,"NbNoeuds: %d",R->nbNoeuds);
    fprintf(f,"NbLiaisons: %d",nbLiaisons(R));
    fprintf(f,"NbCommodites: %d",nbCommodites(R));
    fprintf(f,"Gamma: %d",R->gamma);
    fprintf(f,"\n");
    CellNoeud *cn=R->noeuds;
    while(cn){
      Noeud *n=cn->nd;
      fprintf(f,"v %d %f %f",n->num,n->x,n->y);
      cn=cn->suiv;
    }

  }
}

int main(){
  /*FILE *f=fopen("00014_burma.cha","r");
  if (!f) return -1;
  Chaines* c=lectureChaines(f);
  Reseau *R= reconstitueReseauListe(c);
  rechercheCreeNoeudListe(R,1.0,2.0);
  nbLiaisons(R);
  nbCommodites(R);
  ecrireReseau(R,f);
  fclose(f);
  libererReseau(R);*/
  return 0;
}

