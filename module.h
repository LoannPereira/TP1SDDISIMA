#include <stdio.h>
#include <stdlib.h>

typedef enum{
    true,
    false
} Bool;

typedef struct maillon {
	int deb;
	int fin;
	char texte[100];
	struct maillon *suiv;
} Cellule_t, *List;


Cellule_t* creationCellule(int deb, int fin, char *texte);
Cellule_t* recherchePrec(Cellule_t *ptdeb, int date);
List insertion(Cellule_t *ptdeb, Cellule_t* cell);
void affichage(List l);
Bool isEmptyList(List l);
int listLength(List l);
List newList();
List SuppCellule(List li, Cellule_t* cell);
List ChangeDate(List li, int date, int newDate);
void sauvegarde(List li);
List chargeList(List li);
List *rechercherElt(List *liste, int date);
void ajoutListe(List *liste, Cellule_t *elt);
