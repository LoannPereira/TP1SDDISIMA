#include "module.h"

List chargeList(List li){
    FILE *flot;
    int deb, fin;
    Cellule_t *mess;
    char texte[100];
    flot = fopen(FICHIER, "r");
    if (!flot){
        printf("Erreur lors de l'ouverture du fichier\n");
        exit(1);
    }
    fscanf(flot, "%d %d%*c", &deb, &fin);
    fgets(texte, 100, flot);
    texte[strlen(texte) - 1] = 0;
    while (!feof(flot)){
        mess = (Cellule_t *)malloc(sizeof(Cellule_t));
        if (!mess){
            printf("Erreur lors de l'allocation mémoire !\n");
            exit(0);
        }
        mess->deb = deb;
        mess->fin = fin;
        strcpy(mess->texte, texte);
        mess->suiv = NULL;

        ajoutListe(&li, mess);
        fscanf(flot, "%d %d%*c", &deb, &fin);
        fgets(texte, 100, flot);
        texte[strlen(texte) - 1] = 0;
    }
    return li;
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


void ajoutListe(List *liste, Cellule_t *elt)
{
    List *adr = rechercherElt(liste, elt->deb);
    elt->suiv = (*adr);
    (*adr) = elt;

}


List *rechercherElt(List *liste, int date)
{
    Cellule_t *cour = *liste;
    List *prec = liste;

    while (cour != NULL && cour->deb < date)
    {
        prec = &(cour->suiv);
        cour = cour->suiv;
    }

    return prec;
}


void affichage(List l){
	int i=1;
    if(l!=NULL){
        while(l != NULL){
            printf("%d %d  %s\n", l->deb, l->fin, l->texte);
            l = l->suiv;
            i++;
        }
        printf("%d\n",i);
    }
    else{
        printf("La liste est vide\t RIEN A AFFICHER!!\n");
    }
}

int getDate(void){
    time_t t = time(NULL);
    struct tm temps = *localtime(&t);
    return (temps.tm_year + 1900) * 10000 + (temps.tm_mon + 1) * 100 + temps.tm_mday;
}

void affichageDateDuJour(List l){
    List tmp=l;
    if(tmp!=NULL){
        printf("Message(s) NON expiré(s):\n");
        while(tmp != NULL){
            if(tmp->fin>=getDate()){
                printf("Date d'émission: %d \t Message: %s\n",tmp->deb,tmp->texte);
            }
            tmp = tmp->suiv;
        }
    }
}

void SuppMessage(List *li){
    List curr = *li;
    List *tmp=li;
    while(curr!=NULL){
        if(curr->fin<getDate()){
            suppCell(tmp,curr);
        }
        else tmp=&(curr->suiv);
        curr=curr->suiv;
    }
    
}

void suppCell(List* li, Cellule_t* cell){
    *li=cell->suiv;
    free(cell);
}

void ChangeDate(List *li, int date, int newDate){
    List* tmp=li;
    List curr=*li;
    if(*li==NULL){
        printf("La liste est vide, modification impossible\n");
    }
    else{
        while(curr!=NULL){
            if(curr->deb==date){
                curr->deb=newDate;
                curr->fin=newDate+100;//Ajout du mois en plus
                *tmp=curr->suiv;// on saute la cellule
                ajoutListe(li, curr);// on le "ré-insère" dans la liste au bon endroit
            }
            else tmp=&(curr->suiv);
            curr=*tmp;//le courrant pointe sur la cellule suivante (correspondant au suiv du tmp)
        }
    }
}

void sauvegarde(List li){
    List tmp = li;
    FILE* monfic = NULL;
    monfic = fopen(FICHIER, "w");
    if(monfic==NULL){
        printf("\n!!!!!problème d'ouverture du fichier!!!!!\n\n");
        exit(1);
    }
    else {
        while(tmp!=NULL){
        fprintf(monfic, "%d %d %s\n",tmp->deb,tmp->fin,tmp->texte);
        tmp=tmp->suiv;
        }
        fclose(monfic);
    }
}

void rechercheMotif(List li, char* motif){
    List tmp = li;
    if(tmp!=NULL){
        printf("Message contenant: %s:\n",motif);
        while(tmp!=NULL){
            if(compare(tmp->texte, motif)==true){
                printf("Date d'émission: %d  Date d'expiration: %d  Message:%s\n",tmp->deb,tmp->fin,tmp->texte);
            }
            tmp=tmp->suiv;
        }
    }
}

Bool compare(char *s1,char *s2){
    int i=0,j=0;
    Bool contient=false, stop=false;
    while(s1[i]!='\0'&&stop==false){
        if(s1[i]==s2[j]){
            if(s2[j+1]=='\0'){
                contient=true;
                stop=true;
            }
            if(s1[i+1]!=s2[j+1]) j=0;
            else j++;
        }
        i++;
    }
    return contient;
}
