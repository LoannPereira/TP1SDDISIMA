//
//  main.c
//  TP1
//
//  Created by Pereira Loann on 05/02/2019.
//  Copyright © 2019 Pereira Loann. All rights reserved.
//

#include <stdio.h>
#include "module.h"



int main(void){
    List li = NULL;
    li=chargeList(li);
    affichage(li);
    affichageDateDuJour(li);
    rechercheMotif(li, "");
//    sauvegarde(li);
//    printf("TEST DATE\n");
//
//    int temps2= getDate();
//    printf("%d\n", temps2);
    
}
