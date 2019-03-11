//
//  liste_C.c
//  TP1
//
//  Created by Pereira Loann on 11/03/2019.
//  Copyright © 2019 Pereira Loann. All rights reserved.
//

#include "liste_C.h"

/* creationCellule : Créer un bloc contenant la date de début de validité du message, la date de fin, le texte du message
 * 
 * Entrée :
 * 	deb = entier correspondant à la date de début de validité du message
 * 	fin = entier correspondant à la fin de validité du message
 * 
 * Sortie :
 * 	nouv = pointeur sur la cellule créée
 * 
 */

Cellule_t* creationCellule(int deb, int fin, char *texte)
{
    Cellule_t *nouv=NULL;
    
    nouv = (Cellule_t*)malloc(sizeof(Cellule_t)); /* allocation d'une cellule */
    
    if(nouv==NULL) /* si l'allocation a échoué on sort du programme */
    {
        printf("Problème d'allocation mémoire\n");
        exit(1);
    }
    
    nouv->deb = deb; /* copier la date de début dans la cellule */
    nouv->fin = fin; /* copier la date de fin */
    strcpy(nouv->texte,texte); /* copier le texte du message dans la cellule */
    nouv->suiv = NULL; /* initialisation du pointeur suivant */
    return nouv;
}

/* ajoutListe : insertion du message nouveau dans la liste chainée au bon endroit.
 * 
 * Entrée :
 * 	liste = pointeur sur la tête de la liste
 * 	elt = pointeur sur la cellule à insérer
 * 
 * Sortie :
 * 	rien
 * 
 */

void ajoutListe(List_t *liste, Cellule_t *elt)
{
    List_t *adr = rechercherElt(liste, elt->deb); /* trouver l'adresse du bloc précédent */
    elt->suiv = (*adr); /* chainer le bloc elt avec le suivant du précédent */
    (*adr) = elt; /* chainer le bloc elt avec le précédent */
    
}

/* rechercherElt : recherche selon la date de début, l’emplacement du nouveau message dans la liste chainée.
 * 
 * Entrée :
 * 	liste = pointeur sur la tête de la liste chaînée
 * 	date = entier correspondant à la date de début de validité du message
 * 	 
 * Sortie :
 * 	prec = pointeur sur la cellule après laquelle doit être inséré le message de cette date
 *  
 */

List_t *rechercherElt(List_t *liste, int date)
{
    Cellule_t   * cour = *liste; /* pointeur sur le début de la liste */
    List_t      * prec = liste; /* pointeur sur le bloc précédant le bloc cour */
    
    while (cour != NULL && cour->deb < date) /* tant que la fin de la chaîne n'est pas atteinte et que l'emplacement n'est pas le bon */
    {
        prec = &(cour->suiv); /* progression du pointeur prec */
        cour = cour->suiv; /* progression du pointeur suiv */
    }
    
    return prec;
}

/* suppListe : suppression de la cellule donnée en entrée
 * 
 * Entrée :
 * 	li = pointeur sur la tête de la liste
 * 	cell = pointeur sur la cellule à supprimer
 * 
 * Sortie :
 * 	rien
 * 
 */

void suppCell(List_t* li, Cellule_t* cell){
    *li=cell->suiv; /* déplacer le pointeur de tête de liste */
    free(cell); /* libérer le bloc cell */
}
