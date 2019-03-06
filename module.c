#include "module.h"


List chargeList(List li){
    FILE *flot;
    int deb, fin;
    Cellule_t *mess;
    char texte[100];
    flot = fopen("/Users/pereiraloann/desktop/TP_SDD/TP1/TP1/sauve.txt", "r");
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

Cellule_t* recherchePrec(List li, int date){
    Cellule_t *pre=li;
    while(pre->suiv != NULL && pre->suiv->deb<date){
        pre = pre->suiv;
    }
    return pre;
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
	int i=0;
    if(l!=NULL){
        while(l != NULL){
            printf("%d: deb=%d fin=%d texte: %s\n",i+1, l->deb, l->fin, l->texte);
            l = l->suiv;
            i++;
        }
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

void sauvegarde(List li){
    List tmp = li;
    FILE* monfic = NULL;
    monfic = fopen("/Users/pereiraloann/desktop/TP_SDD/TP1/TP1/sauve.txt", "w");
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
    int i =0;
    int j=0;
    Bool contient =false;
    Bool stop=false;
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
