//
//  main.c
//  TP1
//
//  Created by Pereira Loann on 05/02/2019.
//  Copyright © 2019 Pereira Loann. All rights reserved.
//

#include "tp1.h"
#include "liste_C.h"


int main(int argc, char **argv){
    int retour=0;
    if(argc==2){
        const char* fichier = argv[1];
        //const char* fichier = "/Users/pereiraloann/desktop/TP_SDD/TP1/TP1/sauve.txt"; pour Loann
        List li = NULL;
        li=chargeList(li, fichier);
        affichage(li);
        ChangeDate(&li, 20170403, 20200101);
        printf("---------------\n");
        affichage(li);
        retour=0;
    }
    else{
        printf("Veuillez renseigner l'adresse du fichier en ligne de commande \n");
        retour=1;
    }
    return retour;
    
}
