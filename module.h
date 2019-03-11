#ifndef MODULE
#define MODULE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define FICHIER "/Users/pereiraloann/desktop/TP_SDD/TP1/TP1/sauve.txt"

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



List chargeList(List li);
Cellule_t* creationCellule(int deb, int fin, char *texte);
void ajoutListe(List *liste, Cellule_t *elt);
List *rechercherElt(List *liste, int date);
void affichage(List l);// pour le débuggage
int getDate(void);
void affichageDateDuJour(List l);
void SuppMessage(List *li);
void suppCell(List* li, Cellule_t* cell);
void ChangeDate(List *li, int date, int newDate);
void sauvegarde(List li);
void rechercheMotif(List li, char* motif);
Bool compare(char *s1,char *s2);

#endif
