//
//  liste_C.c
//  TP1
//
//  Created by Pereira Loann on 11/03/2019.
//  Copyright © 2019 Pereira Loann. All rights reserved.
//

#include "liste_C.h"

Cellule_t* creationCellule(int deb, int fin, char *texte)
{
    Cellule_t *nouv=NULL;
    
    nouv = (Cellule_t*)malloc(sizeof(Cellule_t));
    if(nouv==NULL)
    {
        printf("Problème d'allocation mémoire\n");
        exit(1);
    }
    nouv->deb= deb;
    nouv->fin= fin;
    strcpy(nouv->texte,texte);
    nouv->suiv = NULL;
    return nouv;
}


void ajoutListe(List_t *liste, Cellule_t *elt)
{
    List_t *adr = rechercherElt(liste, elt->deb);
    elt->suiv = (*adr);
    (*adr) = elt;
    
}


List_t *rechercherElt(List_t *liste, int date)
{
    Cellule_t   * cour = *liste;
    List_t      * prec = liste;
    
    while (cour != NULL && cour->deb < date)
    {
        prec = &(cour->suiv);
        cour = cour->suiv;
    }
    
    return prec;
}

void suppCell(List_t* li, Cellule_t* cell){
    *li=cell->suiv;
    free(cell);
}
