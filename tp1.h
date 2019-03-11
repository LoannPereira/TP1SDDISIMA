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
} Boolean_t;

List_t chargeList(List_t li, const char* fichier);
void affichage(List_t l);// pour le débuggage
int getDate(void);
void affichageDateDuJour(List_t l);
void SuppMessage(List_t *li);
void ChangeDate(List_t *li, int date, int NewDate);
void sauvegarde(List_t li,const char* fichier);
void rechercheMotif(List_t li, char* motif);
Boolean_t compare(char *s1,char *s2);
#endif
