//
//  main.c
//  TP1
//
//  Created by Pereira Loann on 05/02/2019.
//  Copyright © 2019 Pereira Loann. All rights reserved.
//

#include "tp1.h"
#include "liste_C.h"

//if(1)--> execute le code
int main(int argc, char **argv){
    int retour=0;
    if(argc==2){
        /*const char* fichier = "/Users/pereiraloann/desktop/TP_SDD/TP1/TP1/sauve.txt";*/
        
        
        /*----------------------------------------------------------------------------*/
        /*                            !!! /TEST\ !!!                                  */
        /*____________________________________________________________________________*/
        const char* fichier = argv[1];
        const char* fichierVide="/Users/pereiraloann/desktop/TP_SDD/TP1/TP1/chargeVide.txt";
        const char* fichierUneLigne="/Users/pereiraloann/desktop/TP_SDD/TP1/TP1/chargeUneLigne.txt";
        const char* fichierMessPerim="/Users/pereiraloann/desktop/TP_SDD/TP1/TP1/chargeMessPerim.txt";
        const char* fichierTousOk="/Users/pereiraloann/desktop/TP_SDD/TP1/TP1/chargeTousOk.txt";
        const char* fichierSauv="/Users/pereiraloann/desktop/TP_SDD/TP1/TP1/sauve.txt";
        
        List_t li = NULL;
        List_t LiVide = NULL;
        List_t LiUneLigne = NULL;
        List_t LiTest = NULL;
        /*-------------------------------------------------------------*/
        /*              Lecture du fichier contenant les données       */
        /*Hypothèse de départ: Les lignes du fichiers ne sont pas triés*/
        /*                     est rempli avec le bon format           */
        /*_____________________________________________________________*/
        /*CAS 1:*/
        /*Si le non de fichier est incorrect*/
        /* li=chargeList(li, "");*/    /*-->on quitte le programme avec le message "Problème ouverture du fichier*/
        /*CAS 2: cas de base*/
        li=chargeList(li, fichier);
        printf("Affichage CAS 2 après le chargement du fichier en mémoire\n\n");
        affichage(li);
        printf("*---------------------------------------------*\n");
        /*on a bien la liste des messages triés par ordre croissant suivant la date*/
        /*CAS 3: si le fichier est vide */
        LiVide=chargeList(LiVide, fichierVide); /*La liste sera vide donc on a rien a afficher*/
        printf("Affichage CAS 3 après le chargement du fichier vide en mémoire\n\n");
        affichage(LiVide);
        printf("*---------------------------------------------*\n");
        /*CAS 4: si le fichier contient une seule ligne*/
        LiUneLigne=chargeList(LiUneLigne, fichierUneLigne); /*La liste sera vide donc on a rien a afficher*/
        printf("Affichage CAS 4 après le chargement du fichier vide en mémoire\n\n");
        affichage(LiUneLigne);
        printf("*---------------------------------------------*\n");
        
        /*-------------------------------------------------------------*/
        /*                   Tests AffichageDateJour                    */
        /*Hypothèse de départ: Les dates sont sous le bon format       */
        /*_____________________________________________________________*/
        printf("\n\n-----||  TESTS de la fonction affichageDateJout(List_l)  ||------ \n\n");
        /*CAS 1: cas de base */
        printf("Affichage CAS 1 AffichageDateJour\n\n");
        if(!affichageDateDuJour(li))
            printf("\tLa liste de message est vide, donc aucun message ne peut être affiché\n");
        printf("*---------------------------------------------*\n");
        /*Cas 2: si la liste est vide*/
        printf("Affichage CAS 2 AffichageDateJour\n\n");
        if(!affichageDateDuJour(LiVide))
            printf("\tLa liste de message est vide, donc aucun message ne peut être affiché\n");
        printf("*---------------------------------------------*\n");
        /*Cas 3: si tous les messages sont périmés*/
        printf("Affichage CAS 3 AffichageDateJour\n\n");
        LiTest = chargeList(LiTest, fichierMessPerim);/*On charge le fichier avec les messages périmés*/
        if(!affichageDateDuJour(LiTest))
            printf("\tLa liste de message est vide, donc aucun message ne peut être affiché\n");
        printf("*---------------------------------------------*\n");
        /*Cas 4: si tous les messages ne sont pas périmés*/
        printf("Affichage CAS 4 AffichageDateJour\n\n");
        LiTest = chargeList(LiTest, fichierTousOk);/*On charge le fichier avec les messages non périmés*/
        if(!affichageDateDuJour(LiTest))
            printf("\tLa liste de message est vide, donc aucun message ne peut être affiché\n");
        printf("*---------------------------------------------*\n");
        supprimmerListe(LiTest);
        /*-------------------------------------------------------------*/
        /*                   Tests sauvegarde                          */
        /*Hypothèse de départ: Les messages sont sous le bon format    */
        /*_____________________________________________________________*/
        printf("\n\n-----||  TESTS de la fonction sauvegarde(List_t li,const char* fichier)  ||------ \n\n");
        /*CAS 1: cas de base*/
        printf("Affichage CAS 1 sauvegarde\n");
        if(!sauvegarde(li, fichierSauv)) /*enregistre les messages triés dans le fichier sauve.txt*/
            printf("\tLa liste de message est vide, donc aucun message ne peut être sauvegardé\n");
        else
            printf("\tSauvegarde effectué!! :D\n");
        printf("*---------------------------------------------*\n");
        /*CAS 2: on donne une liste vide*/
        printf("Affichage CAS 2 sauvegarde\n");
        if(!sauvegarde(LiVide, fichierSauv))
            printf("\tLa liste de message est vide, donc aucun message ne peut être sauvegardé\n");
        else
            printf("\tSauvegarde effectué!! :D\n");
        printf("*---------------------------------------------*\n");
        
        /*-------------------------------------------------------------*/
        /*                   Tests SuppMessage                         */
        /*Hypothèse de départ: Les messages sont sous le bon format    */
        /*_____________________________________________________________*/
        printf("\n\n-----||  TESTS de la fonction  SuppMessage(List_t *li)  ||------ \n\n");
        /*Cas 1: cas de base*/
        printf("Affichage CAS 1 SuppmMessage\n");
        SuppMessage(&li);
        affichage(li);
        supprimmerListe(li);
        printf("*---------------------------------------------*\n");
        /*Cas 2: tout les messages sont obsolètes*/
        printf("Affichage CAS 2 SuppmMessage\n");
        LiTest=NULL;
        LiTest = chargeList(LiTest, fichierMessPerim);
        SuppMessage(&LiTest);
        affichage(LiTest);  /*affiche rien car tous obsolètes*/
        supprimmerListe(LiTest);
        printf("*---------------------------------------------*\n");
        /*Cas 3: tout les messages sont à jour*/
        printf("Affichage CAS 3 SuppmMessage\n");
        LiTest=NULL;
        LiTest = chargeList(LiTest, fichierTousOk);
        SuppMessage(&LiTest);
        affichage(LiTest);  /*affiche tout car tous à jour*/
        supprimmerListe(LiTest);
        printf("*---------------------------------------------*\n");
        
        /*-------------------------------------------------------------*/
        /*                   Tests ChangeDate                          */
        /*Hypothèse de départ: Les messages sont sous le bon format    */
        /*_____________________________________________________________*/
        printf("\n\n-----||  TESTS de la fonction  ChangeDate(List_t *li, int date, int NewDate)  ||------ \n\n");
        printf("Rechargement de li:\n");
        li=NULL;
        li=chargeList(li, fichier);
        affichage(li);
        printf("*---------------------------------------------*\n");
        /*Cas 1: cas de base*/
        printf("\nAffichage CAS 1 ChangeDate\n");
        ChangeDate(&li, 20170403, 20190103); /*remplacer par une date qui est ni la plus ancienne ni la plus récente*/
        affichage(li);
        printf("*---------------------------------------------*\n");
        /*Cas 2: cas de base*/
        printf("Affichage CAS 2 ChangeDate\n");
        ChangeDate(&li, 20190103, 20200103); /*remplacer par une date qui est la plus récente*/
        affichage(li);
        printf("*---------------------------------------------*\n");
        
        /*-------------------------------------------------------------*/
        /*                   Tests rechercheMotif                          */
        /*Hypothèse de départ: Les messages sont sous le bon format    */
        /*_____________________________________________________________*/
        printf("\n\n-----||  TESTS de la fonction  rechercheMotif(List_t li, char* motif)  ||------ \n\n");
        /*Cas 1: cas de base (plusieurs messages contienent le motif*/
        printf("Affichage CAS 1 rechercheMotif\n");
        if(!rechercheMotif(li,"tu")) /*motif présent dans 2 messages*/
            printf("\tLa liste de message est vide ou le motif est vide\n");
        printf("*---------------------------------------------*\n");
        /*Cas 2: le motif n'est présent dans aucun message */
        printf("Affichage CAS 2 rechercheMotif\n");
        if(!rechercheMotif(li,"ISIMA")) /*motif présent dans aucun message*/
            printf("\tLa liste de message est vide ou le motif est vide\n");
        printf("*---------------------------------------------*\n");
        /*Cas 3: le motif est présent dans un seul message */
        printf("Affichage CAS 3 rechercheMotif\n");
        if(!rechercheMotif(li,"oui")) /*motif présent dans 1 message*/
            printf("\tLa liste de message est vide ou le motif est vide\n");
        printf("*---------------------------------------------*\n");
        /*Cas 4: la liste est vide */
        printf("Affichage CAS 4 rechercheMotif\n");
        if(!rechercheMotif(LiVide,"tu")) /*liste vide donc le motif présent dans aucun messages*/
            printf("\tLa liste de message est vide ou le motif est vide\n");
        printf("*---------------------------------------------*\n");
        /*Cas 5: la liste est vide */
        printf("Affichage CAS 5 rechercheMotif\n");
        if(!rechercheMotif(li,"")) /*motif est vide donc présent dans aucun messages*/
            printf("\tLa liste de message est vide ou le motif est vide\n");
        printf("*---------------------------------------------*\n");
        supprimmerListe(li);
    }
    else{
        printf("Veuillez renseigner l'adresse du fichier en ligne de commande \n");
        retour=1;
    }
    return retour;
    return 0;
}
