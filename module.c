#include "module.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){
    List li = NULL;
    Cellule_t *c1 = creationCellule(1, 2, "C1");
    Cellule_t *c2 = creationCellule(6, 9, "C2");
    Cellule_t *c3 = creationCellule(4, 5, "C3");
    Cellule_t *c4 = creationCellule(45, 98, "C4");
    Cellule_t *c5 = creationCellule(33, 39, "C5");
    li = insertion(li, c1);
    li = insertion(li, c2);
    li = insertion(li, c3);
    li = insertion(li, c4);
    li = insertion(li, c5);
    affichage(li);
    printf("----------------\n");
    li = SuppCellule(li, c1);
    affichage(li);
    printf("----------------\n");
    li=ChangeDate(li, 6, 94);
    affichage(li);
}

Cellule_t* creationCellule(int deb, int fin, char *texte){
    Cellule_t *nouv;
    nouv = (Cellule_t*)malloc(sizeof(Cellule_t));
    if(nouv==NULL){
        printf("Problème d'allocation mémoire\n");
        exit(1);
    }
    nouv->deb= deb;
    nouv->fin= fin;
    strcpy(nouv->texte,texte);
    nouv->suiv = NULL;
    return nouv;
}



List insertion(List li, Cellule_t* cell){
    Cellule_t *cellPrec;
    if(li==NULL){
        return cell;
    }
    else {
        cellPrec= recherchePrec(li, cell->deb);
        if(cellPrec==NULL){
            cell->suiv=li;
            li=cell;
            return li;
        }
        else{
            cell->suiv=cellPrec->suiv;
            cellPrec->suiv=cell;
            return li;
        }
    }
}


Cellule_t* recherchePrec(List li, int date){
    Cellule_t *pre=li;
    while(pre->suiv != NULL && pre->suiv->deb<date){
        pre = pre->suiv;
    }
    return pre;
}

void affichage(List l){
	int i=0;
    if(l!=NULL){
        while(l != NULL){
            printf("%d: deb=%d fin=%d texte: %s\n",i, l->deb, l->fin, l->texte);
            l = l->suiv;
            i++;
        }
    }
    else{
        printf("La liste est vide\t RIEN A AFFICHER!!\n");
    }
}

List SuppCellule(List li, Cellule_t* cell){
    Cellule_t* cellPrec;
    if(li==NULL)printf("La liste est vide  !!\n");
    else{
        if(li->suiv==NULL){
            free(li);
        }
        else{
            if(li==cell){
                li=cell->suiv;
                free(cell);
            }
            else{
                if(li->suiv!= NULL){
                    cellPrec=recherchePrec(li, cell->deb);
                    cellPrec->suiv=cell->suiv;
                    free(cell);
                }
                else{
                    printf("Cellule introuvée pour la suppression :/\n");
                }
            }
        }
    }
    return li;
}

List ChangeDate(List li, int date, int newDate){
    List tmp = li;
    if(li==NULL){
        printf("La liste est vide, modification impossible\n");
    }
    else{
        while(tmp->suiv!=NULL){
            if(tmp->deb==date) tmp->deb=newDate;
            tmp=tmp->suiv;
        }
    }
    return li;
}

List newList(){
    return NULL;
}

Bool isEmptyList(List l){
    if(l==NULL){
        return true;
    }
    return false;
}

int listLength(List l){
    int size=0;
    if(!isEmptyList(l)){
        while(l!=NULL){
            size++;
            l=l->suiv;
        }
    }
    return size;
}
