#include "tp1.h"

List_t chargeList(List_t li,const char* fichier)
{
    FILE      * flot=NULL;
    int         deb, fin;
    Cellule_t * mess=NULL;
    char        texte[100];
    

    flot = fopen(fichier, "r");
    if (!flot)
    {
        printf("Problème d'ouverture du fichier");
        exit(0);
    }
        fscanf(flot, "%d %d%*c", &deb, &fin);
        fgets(texte, 100, flot);
        texte[strlen(texte) - 1] = 0;
        while (!feof(flot))
        {
            mess = (Cellule_t *)malloc(sizeof(Cellule_t));
            if (!mess)
            {
                printf("Erreur lors de l'allocation mémoire !\n");
                exit(1);
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

void affichage(List_t l)
{
	int i=1;
    if(l!=NULL)
    {
        while(l != NULL)
        {
            printf("%d %d  %s\n", l->deb, l->fin, l->texte);
            l = l->suiv;
            i++;
        }
        printf("%d\n",i);
    }
    else
    {
        printf("La liste est vide\t RIEN A AFFICHER!!\n");
    }
}

int getDate(void)
{
    time_t t = time(NULL);
    struct tm temps = *localtime(&t);
    return (temps.tm_year + 1900) * 10000 + (temps.tm_mon + 1) * 100 + temps.tm_mday;
}

void affichageDateDuJour(List_t l){
    List_t tmp=l;
    if(tmp!=NULL)
    {
        printf("Message(s) NON expiré(s):\n");
        while(tmp != NULL)
        {
            if(tmp->fin>=getDate())
            {
                printf("Date d'émission: %d \t Message: %s\n",tmp->deb,tmp->texte);
            }
            tmp = tmp->suiv;
        }
    }
}

void SuppMessage(List_t *li)
{
    List_t      curr = *li;
    List_t    * tmp=li;
    
    while(curr!=NULL)
    {
        if(curr->fin<getDate())
        {
            suppCell(tmp,curr);
        }
        else tmp=&(curr->suiv);
        curr=curr->suiv;
    }
    
}



void ChangeDate(List_t *li, int date, int NewDate)
{
    List_t    * tmp=li;
    List_t      curr=*li;
    
    if(*li==NULL)
    {
        printf("La liste est vide, modification impossible");
    }
    else
    {
        while(curr!=NULL)
        {
            if(curr->deb==date)
            {
                curr->deb=NewDate;
                curr->fin=NewDate+100;//Ajout du mois en plus
                *tmp=curr->suiv;// on saute la cellule
                ajoutListe(li, curr);// on le "ré-insère" dans la liste au bon endroit
            }
            else tmp=&(curr->suiv);
            curr=*tmp;//le courrant pointe sur la cellule suivante (correspondant au suiv du tmp)
        }
    }
}

void sauvegarde(List_t li,const char* fichier)
{
    List_t    tmp = li;
    FILE    * MonFic = NULL;
    
    MonFic = fopen(fichier, "w");
    if(MonFic==NULL)
    {
        printf("Problème d'ouverture du fichier");
        exit(0);
    }
    while(tmp!=NULL)
    {
        fprintf(MonFic, "%d %d %s\n",tmp->deb,tmp->fin,tmp->texte);
        tmp=tmp->suiv;
    }
    fclose(MonFic);
}

void rechercheMotif(List_t li, char* motif)
{
    List_t tmp = li;
    
    if(tmp!=NULL)
    {
        printf("Message contenant: %s:\n",motif);
        while(tmp!=NULL)
        {
            if(compare(tmp->texte, motif)==true)
            {
                printf("Date d'émission: %d  Date d'expiration: %d  Message:%s\n",tmp->deb,tmp->fin,tmp->texte);
            }
            tmp=tmp->suiv;
        }
    }
}

Boolean_t compare(char *s1,char *s2)
{
    int         i=0,j=0;
    Boolean_t   contient=false, stop=false;
    
    while(s1[i]!='\0'&&stop==false)
    {
        if(s1[i]==s2[j])
        {
            if(s2[j+1]=='\0')
            {
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
