#include "tp1.h"

/* Module tp1:                                                                   */
/* contient l'ensemble des fonctions permettant de gérer les messages en mémoire */



/* -------------------------------------------------------------------- */
/* ChargeList   Permet de mettre en mémoire les messages du fichier     */
/*                                                                      */
/* En entrée: li: liste vide de message                                  */
/*            fichier: char de caractère comportant le nom du fichier    */
/* En sortie: li: la liste ainsi chargée                                  */
/* -------------------------------------------------------------------- */

List_t chargeList(List_t li,const char* fichier)
{
    FILE      * flot=NULL;  /*pointeur de flux pour ouvrir le fichier*/
    int         deb, fin;   /*entier pour récolter les valeurs contenu dans le fichier*/
    char        texte[100]; /*char pour récolter les valeurs contenu dans le fichier*/
    Cellule_t * mess=NULL;  /*pointeur de message que l'on "rempliera" avec les valeurs*/
    

    flot = fopen(fichier, "r");
    if (!flot)                         /* permet de vérifier si le fichier c'est bien ouver*/
    {
        printf("Problème d'ouverture du fichier\n");
        exit(0);
    }
        fscanf(flot, "%d %d%*c", &deb, &fin); /* on lit la première ligne du fichier*/
        fgets(texte, 100, flot);
        texte[strlen(texte) - 1] = 0; /*on ajoute \0 à la fin de la chaîne de caractère*/
        while (!feof(flot))           /* s'il y a une ligne supplémentaire on continue la lecture*/
        {
            mess=creationCellule(deb, fin, texte);
            ajoutListe(&li, mess);    /* ajout du nouveau message récupérer dans la liste*/
            fscanf(flot, "%d %d%*c", &deb, &fin); /* lecture de la ligne suivante*/
            fgets(texte, 100, flot);
            texte[strlen(texte) - 1] = 0;
        }
        fclose(flot);
    return li;
}


/* -------------------------------------------------------------------- */
/* affichage   Permet d'afficher la liste (utile pour le débogage)      */
/*                                                                      */
/* En entrée: li: liste  de message                                      */
/* -------------------------------------------------------------------- */
void affichage(List_t l)
{
    if(l!=NULL)          /* si la liste donnée n'est pas vide*/
    {
        while(l != NULL) /*tant qu'il y a un message */
        {
            printf("%d %d  %s\n", l->deb, l->fin, l->texte);
            l = l->suiv;
        }
    }
    else
    {
        printf("\tLa liste est vide\t RIEN A AFFICHER!!\n");
    }
}

/* -------------------------------------------------------------------- */
/* getDate             Permet de récupérer la date système              */
/*                                                                      */
/* En sortie: la date système dans un int sous la forme suivante        */
/*            aaaammjj                                                  */
/*Utilisation de  la structure time_t qui permet grâce à ses fonctions   */
/*associés de récupérer le nombre d'année écoulées depuis 1900 (tm_year)*/
/*l'indice du mois (tm_mon) de 0 à 11 et l'indice du jour (tm_mday)     */
/* -------------------------------------------------------------------- */

int getDate(void)
{
    time_t t = time(NULL); /* variable de type time_t permettant de récupérer la date */
    struct tm temps = *localtime(&t);
    return (temps.tm_year + 1900) * 10000 + (temps.tm_mon + 1) * 100 + temps.tm_mday;
    /*les multiplications par 10000 et 100 permettent de décaler l'année et le mois vers la gauche*/
    /* et ainsi obtenir un format de ce type aaaammjj*/
}

/* -------------------------------------------------------------------- */
/* affichageDateJour   Permet d'afficher les messages encore valides    */
/*                                                                      */
/* En entrée: li liste  de message                                      */
/*--------------------------------------------------------------------- */
int affichageDateDuJour(List_t l)
{
    List_t tmp=l;                   /*pointeur temporaire pour parcourir la liste*/
    int retour=0;                   /*si = 0 problème d'exécution de la fcontion*/
    while(tmp != NULL)          /*tant qu'il y a un message */
    {
        if(tmp->fin>=getDate()) /* si la date de fin du message est supérieure à la date sytème*/
        {
            printf("Date d'émission: %d \t Message: %s\n",tmp->deb,tmp->texte); /*on affiche le message*/
            retour = 1;         /*indique qu'il y a bien des message affichés même si cela est fait autant de fois qu'il y aura de message à afficher on a pas le choix*/
        }
        tmp = tmp->suiv;        /* on passe au message suivant*/
        
    }
    return retour;
}

/* -------------------------------------------------------------------- */
/* SuppMessage     Permet de supprimer les messages devenus obsolètes   */
/*                                                                      */
/* En entrée: *li: un pointeur sur la liste  de message                 */
/*--------------------------------------------------------------------- */

void SuppMessage(List_t *li)
{
    List_t      curr = *li;     /*pointeur de cellule sur le message courant*/
    List_t    * tmp=li;         /*pointeur de liste temporaire pour le parcours*/
    
    while(curr!=NULL)           /* parcours de la liste de message*/
    {
        if(curr->fin<getDate()) /*si la date de fin du message pointé est inférieure à la date système*/
        {
            suppCell(tmp,curr); /*on supprime le message de la liste*/
        }
        else tmp=&(curr->suiv); /* on passe au message suivant si la date est encore correcte*/
        curr=curr->suiv;        /*on incrémente dans tout les cas curr*/
    }
    
}


/* -------------------------------------------------------------------- */
/* ChangeDate     Change la date de début de tout les messages          */
/*                  comportant la date mis en paramètre                 */
/*                                                                      */
/* En entrée: *li: un pointeur sur la liste  de message                  */
/*             date: date que l'on veut remplacer                        */
/*             NewDate: nouvelle date                                    */
/*--------------------------------------------------------------------- */

void ChangeDate(List_t *li, int date, int NewDate)
{
    List_t    * tmp=li;         /*pointeur de liste temporaire pour le parcours*/
    List_t      curr=*li;       /*pointeur de cellule sur le message courant*/
    
    if(*li==NULL)
    {
        printf("La liste est vide, modification impossible");
    }
    else
    {
        while(curr!=NULL)             /* parcours de la liste de message*/
        {
            if(curr->deb==date)       /*si l'on trouve la date que l'on veut remplacer*/
            {
                curr->deb=NewDate;
                curr->fin=NewDate+100;/*Ajout du mois en plus*/
                *tmp=curr->suiv;      /*on saute la cellule*/
                ajoutListe(li, curr); /* on le "ré-insère" dans la liste au bon endroit*/
            }
            else tmp=&(curr->suiv);
            curr=*tmp;/*le courant pointe sur la cellule suivante (correspondant au suiv du tmp)*/
        }
    }
}


/* -------------------------------------------------------------------- */
/* sauvegarde     Permet d'enregistrer dans un fichier le contenu       */
/*                              de la liste                             */
/*                                                                      */
/* En entrée:  li: la liste  de message                                  */
/*             fichier: char de caractère comportant le nom du fichier   */
/*--------------------------------------------------------------------- */

int sauvegarde(List_t li,const char* fichier)
{
    List_t    tmp = li;             /*pointeur temporaire sur Cellule_t*/
    FILE    * MonFic = NULL;        /*pointeur de flux pour ouvrir le fichier*/
    int       retour = 0;
    if(tmp!=NULL)
    {
        MonFic = fopen(fichier, "w");
        if(MonFic==NULL)                /*On vérifie si l'ouverture en écriture du fichier se passe mal*/
        {
            printf("Problème d'ouverture du fichier");
            exit(0);                    /*on quitte le programme si oui*/
        }
        while(tmp!=NULL)
        {
            fprintf(MonFic, "%d %d %s\n",tmp->deb,tmp->fin,tmp->texte); /*on écrit dans le fichier*/
            tmp=tmp->suiv;
        }
        fclose(MonFic);/*on ferme le flot*/
        retour =1;     /*tout c'est bien passé*/
    }
    return retour;
}

/* -------------------------------------------------------------------- */
/* rechercheMotif     Permet d'afficher tout les messages comportant    */
/*                       la chaîne de caractère passé en paramètre      */
/*                                                                      */
/* En entrée:  li: la liste  de message                                  */
/*             motif: chaîne de caractère correspondant au motif         */
/*             à trouver.                                               */
/*--------------------------------------------------------------------- */

int rechercheMotif(List_t li, char* motif)
{
    List_t tmp = li; /*pointeur temporaire sur Cellule_t*/
    int retour = 0;
    
    while(tmp!=NULL)
    {
        if(compare(tmp->texte, motif)==true) /*si la fonction compare indique que le message courant contient le motif*/
        {
            printf("\tDeb: %d  Fin: %d  Message:%s\n",tmp->deb,tmp->fin,tmp->texte);
            retour = 1;
        }
        tmp=tmp->suiv;
    }
    
    return retour;
}

/* -------------------------------------------------------------------- */
/* compare         Indique grâce à un boolean si dans le première       */
/*             chaîne de caractère il y a le motif (deuxième chaîne)    */
/*                                                                      */
/* En entrée: s1:  chaîne de caractère                                   */
/*            s2:  chaîne de caractère: motif que l'on recherche dans s1 */
/* En sortie: contient: un boolean indiquant si oui ou non s2 est        */
/*            présent dans s1                                           */
/* -------------------------------------------------------------------- */

Boolean_t compare(char *s1,char *s2)
{
    int         i=0,j=0; /*i pour le parcours de s1 et j pour le parcours de s2(motif)*/
    Boolean_t   contient=false, stop=false; /*stop permet d'arrêter la boucle while*/
    
    while(s1[i]!='\0'&&stop==false) /*si l'on arrive pas à la fin de s1 ou si l'on doit pas arrêter la boucle*/
    {
        if(s1[i]==s2[j])        /*caractère égale*/
        {
            if(s2[j+1]=='\0')   /*si on arrive à la fin de s1*/
            {
                contient=true;  /*alors le motif s2 et contenu dans s1*/
                stop=true;      /*on doit arrêter la boucle whiles*/
            }
            if(s1[i+1]!=s2[j+1])/*si au prochain caractère du motif et de s1 il y a une différence*/
                j=0;  /*on replace l'indice de caractère au début du motif car on doit éxaminer l'égalité avec le reste de s1*/
            else j++; /*on passe au caractère suivant de s2 (motif) si il y a égalité des caractères*/
        }
        i++;                    /*dans tout les cas on passe au caractère suivant de s1*/
    }
    return contient;
}
