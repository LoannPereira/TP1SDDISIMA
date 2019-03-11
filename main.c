//
//  main.c
//  TP1
//
//  Created by Pereira Loann on 05/02/2019.
//  Copyright © 2019 Pereira Loann. All rights reserved.
//

#include "module.h"



int main(int argc, char **argv){
    const char* fichier = argv[1];
    List li = NULL;
    li=chargeList(li, fichier);
    affichage(li);
    ChangeDate(&li, 20170403, 20200101);
    printf("---------------\n");
    affichage(li);
    
}
