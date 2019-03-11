#ifndef TP1
#define TP1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "liste_C.h"

typedef enum{
    true,
    false
} Bool;

List chargeList(List li, const char* fichier);
void affichage(List l);// pour le débuggage
int getDate(void);
void affichageDateDuJour(List l);
void SuppMessage(List *li);
void ChangeDate(List *li, int date, int newDate);
void sauvegarde(List li,const char* fichier);
void rechercheMotif(List li, char* motif);
Bool compare(char *s1,char *s2);

#endif
