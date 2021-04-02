#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Chaine.h"

void liberer(Chaines* c){
  if(c){
    CellChaine* tmp=c->chaines;
    while(tmp){
      CellPoint* ptmp=tmp->points;
      while(ptmp){
        tmp->points=tmp->points->suiv;
        free(ptmp);
        ptmp=tmp->points;
      }
    c->chaines=c->chaines->suiv;
    free(tmp);
    tmp=c->chaines;
  }
  free(c);
  }
}


Chaines* lectureChaines(FILE *f){
  int g,n;
  char ligne[500];char reste[400];
  printf("hello World \n");
  if(f && fgets(ligne,500*sizeof(char),f)&&
          sscanf(ligne,"%s %d",reste,&n)==2 &&
          fgets(ligne,500*sizeof(char),f)&&
          sscanf(ligne,"%s %d",reste,&g)==2){
    Chaines* c=(Chaines *)malloc(sizeof(Chaines));
    if(!c){
      printf("erreur d'allocution\n");
      return NULL;
    }
    c->gamma=g;
    c->nbChaines=n;
    c->chaines=NULL;
    int i=0;
    char points[450];
    int j,max;
    while(i<n && fgets(ligne,500*sizeof(char),f) && sscanf(ligne,"%d %d %[^\n]",&j,&max,points)==3){

      CellChaine* cell=(CellChaine*)malloc(sizeof(CellChaine));
      if(!cell){
        printf("Erreur d'allocution\n");
        liberer(c);
        return NULL;
      }
      cell->numero=j;
      cell->suiv=c->chaines;
      c->chaines=cell;
      cell->points=NULL;
      int d=0;
      double x,y;
      while(d<max && sscanf(points,"%lf %lf %[^\n]",&x,&y,points)>1){

        CellPoint* point=malloc(sizeof(CellPoint));
        if(!point){
          printf("Erreur d'allocutions\n");
          liberer(c);
          return NULL;
        }
        point->x=x;
        point->y=y;
        point->suiv=cell->points;
        cell->points=point;
        d=d+1;
      }
      i=i+1;
    }
    return c;
  }
  return NULL;
}


void afficher(Chaines* c){
  if (c){
    printf("Nbchain: %d\nGamma: %d\n",c->nbChaines,c->gamma);
    CellChaine* tmp=c->chaines;
    while(tmp){
      printf("%d\t",tmp->numero);
      CellPoint* ptmp=tmp->points;
      while(ptmp){
        printf("%.2f %.2f ",ptmp->x,ptmp->y);
        ptmp=ptmp->suiv;
      }
      printf("\n");
      tmp=tmp->suiv;
    }
  }
}

void ecrireChaines(Chaines *C, FILE *f){
  if (C && f){
    fprintf(f,"Nbchain: %d\nGamma: %d\n",C->nbChaines,C->gamma);
    CellChaine* tmp=C->chaines;
    while(tmp){
      fprintf(f,"%d ",tmp->numero);
      CellPoint* ptmp=tmp->points;
      int i;
      for(i=0;ptmp;i++)ptmp=ptmp->suiv;
      fprintf(f,"%d ",i);
      ptmp=tmp->points;
      while(ptmp){
        fprintf(f,"%.2f %.2f ",ptmp->x,ptmp->y);
        ptmp=ptmp->suiv;
      }
      fprintf(f,"\n");
      tmp=tmp->suiv;
    }
  }

}

double longueurChaine(CellChaine *c){
  if(c){
    double x,y;
    double l=0;
    CellPoint* tmp1, *tmp2;
    for(tmp1=c->points;tmp1->suiv;tmp1=tmp1->suiv){
      for(tmp2=tmp1->suiv;tmp2;tmp2=tmp2->suiv){
        x=(tmp1->x-tmp2->x)*(tmp1->x-tmp2->x);
        y=(tmp1->y-tmp2->y)*(tmp1->y-tmp2->y);
        l=l+sqrt(x+y);
      }
    }
    return l;
  }
  printf("longueurChaine:La cellule n'existe pas\n");
  return -1.;
}

double longueurTotale(Chaines *C){
  if(C){
    double l=0.;
    CellChaine *c;
    for(c=C->chaines;c;c=c->suiv){
      l=l+longueurChaine(c);
    }
    return l;
  }
  printf("longueurTotale:La structure Chaines n'existe pas\n");
  return -1.;
}

int comptePointsTotal(Chaines *C){
  if (C){
    CellChaine* c;
    CellPoint* p;
    int cpt=0;
    for(c=C->chaines;c;c=c->suiv){
      for(p=c->points;p;p=p->suiv){
        cpt=cpt+1;
      }
    }
    return cpt;
  }
  printf("comptePointsTotal:La Structure Chaines n'existe pas\n");
  return -1;
}
/*int main(){
  FILE *f=fopen("00014_burma.cha","r");
  Chaines* c=lectureChaines(f);
  afficher(c);
  fclose(f);
  f=fopen("resultat","w");
  if (!f) return -1;
  ecrireChaines(c,f);
  fclose(f);
  liberer(c);
  return 0;
}*/
