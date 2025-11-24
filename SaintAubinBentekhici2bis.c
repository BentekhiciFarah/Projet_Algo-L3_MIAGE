//
// Created by saint on 22/11/2025.
/****************** binôme : farah.bentekhici@universite-paris-saclay.fr / saintaubinreginald@gmail.com  ****/
//
#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/*                                               */
/*                type booléen                   */
/*                                               */
/*************************************************/

typedef enum {false, true} bool;

/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/

typedef struct Bloc
{
    int valeur ;
    struct Bloc * suite;
} Bloc;

typedef Bloc *Liste ;

/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/

Liste ajoute(int x, Liste l)
{   Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->valeur = x ;
    tmp->suite = l ;
    return tmp ;
}

/*****************************/
/*                           */
/*       Affiche             */
/*                           */
/*****************************/

void affiche_liste(Liste l) {
    printf("[");
    while (l != NULL) {
        printf("%d", l->valeur);
        if (l->suite != NULL) {
            printf(", ");
        }
        l = l->suite;
    }
    printf("]");
}
//Création d'une nouvelle structure de données