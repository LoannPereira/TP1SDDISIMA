//
//  liste_C.h
//  TP1
//
//  Created by Pereira Loann on 11/03/2019.
//  Copyright © 2019 Pereira Loann. All rights reserved.
//

#ifndef liste_C//.h
#define liste_C//.h
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct maillon {
    int deb;
    int fin;
    char texte[100];
    struct maillon *suiv;
} Cellule_t, *List;

Cellule_t* creationCellule(int deb, int fin, char *texte);
void ajoutListe(List *liste, Cellule_t *elt);
List *rechercherElt(List *liste, int date);
void suppCell(List* li, Cellule_t* cell);


#endif /* liste_C.h */
