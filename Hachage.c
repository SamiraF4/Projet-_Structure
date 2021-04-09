#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Chaine.h"

int fonctionCle(int x, int y){
	return (y + (x + y)*(x + y + 1)/2);
}

int fonctionHachage(int cle,int m){
  double v=cle*(sqrt(5)-1)/2;
  return m*(v-(int)v);
}

Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y){
	int cle=fonctionCle(x,y);
	int i=fonctionHachage(cle,H->m);
	CellNoeud* tmp= H->N[i];
	while(tmp){
		noeud *n=tmp->nd;
		if((n->x==x) && (n->y==y){
			return n;
		}
		tmp=tmp->suiv;
	}
	Noeud *new=(Noeud *)malloc(sizeof(Noeud));
	if(!new){
		printf("Erreur d'allocation\n");
		return NULL;
	}
	H->nE=H->nE++;
	new->x=x;
	new->y=y;
	new->num=H->nE;
	new->voisin=NULL;
	CellNoeud *cnH=(Noeud *)malloc(sizeof(Noeud));
	if(!cnH){
		printf("Erreur d'allocation\n");
		free(new);
		return NULL;
	}
	CellNoeud *cnR=(Noeud *)malloc(sizeof(Noeud));
	if(!cnR){
		printf("Erreur d'allocation\n");
		free(new);
		free(cnH);
		return NULL;
	}
	cnH->nd=new;
	cnH->suivant=H->N[i];
	H->N[i]=cnH;

	cnR->nd=new;
	cnR->suivant=R->noeuds;
	R->noeuds=cnR;

	return new;
}

Reseau* reconstitueReseauHachage(Chaines *C, int M){
	Reseau *R=(Reseau *)malloc(sizeof(Reseau));
	R->nbNoeuds=0;
	C->gamma=0;
	R->noeuds=NULL;
	R->commodite=NULL;
	if(!R){
		printf("Erreur d'allocation\n");
		return NULL;
	}
	TableHachage *T= (TableHachage *)malloc(sizeof(TableHachage));
	if(!T){
		printf("Erreur d'allocation\n");
		free(R);
		return NULL;
	}
	CellNoeud **N= (CellNoeud **)malloc(M*sizeof(CellNoeud*));
	if(!N){
		printf("Erreur d'allocation\n");
		free(T);
		free(R);
		return NULL;
	}
	t->nE=0;
	t->m=M;
	t->N=N;
	int i;
	for(i=0; i<m;i++){
		t->N[i]=NULL;
	}
	CellChaine *tmp= C->chaines;
	while(tmp){
		CellPoint *p=tmp->points;
		CellPoint *psuiv=p->suiv;
		Noeud *n=rechercheCreeNoeudHachage(R,H,p->x,p->y);
		if(!n){
			printf("Erreur rechercheCreeNoeud \n");
			libererReseau(R);
			return NULL;
		}
		while(p && psuiv){
			Noeud *n=rechercheCreeNoeudHachage(R,H,psuiv->x,psuiv->y);
			if(!n){
				printf("Erreur rechercheCreeNoeud \n");
				libererReseau(R);
				return NULL;
			}
			p=p->suiv;
		}
		tmp=tmp->suiv;
	}
	return R;
}




int main(int argc, char const *argv[])
{
	printf("%d\n",fonctionCle(2,3));
	printf("%d\n",fonctionCle(1,1));
	return 0;
}