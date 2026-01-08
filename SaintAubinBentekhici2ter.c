//
// Created by saint on 28/11/2025.
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

// Définition du nouveau type "file" = pointeur sur le dernier bloc 
typedef struct File {
    Bloc * dernier ; // pointeur sur le dernier élement 
} File ; 

/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/

Liste ajoute(int x, Liste l)
{   Liste tmp = malloc(sizeof(Bloc)) ;
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

// Initialisation d'une file : 

File * NouvelleFile() {
    File * F = (File *)malloc(sizeof(File)) ; 
    F->dernier = NULL ; 
    return F ; 
}

// Entrée (Ajouter un element dans la file c-à-d il devient le premier élement) : 
void Entree(int x, File * f) {
    Bloc * nouveau = (Bloc *)malloc(sizeof(Bloc)) ; 
    nouveau->valeur = x ; 

    if(f->dernier == NULL) {
        nouveau->suite= nouveau ; 
        f->dernier = nouveau ; 
        f->dernier->suite = nouveau ; 
    }
    else {
        nouveau->suite = f->dernier->suite ; // Coller nouveau au debut de la file (C-à-d vers la ou pointait le dernier)
        f->dernier->suite = nouveau ;    // Faire pointer le dernier sur l'élément que je viens d'ajouter 
    }

}

// Sortie (Retirer le dernier élement de la file)

void Sortie(int *x, File *f){ // Placer la valeur retirée dans x (comme il est en inout)
    if(f->dernier == NULL) {
        printf("File vide !\n") ; 
        *x = 0 ; // Comme je ne retourne rien
    }
    else {
        Bloc * premier = f->dernier->suite ; 
        *x = premier->valeur ; 

        if(premier->suite = NULL) { // Le cas d'une liste composée d'un seul élement
            f->dernier = NULL ; 
        }
        else {
            f->dernier->suite = premier->suite ; // Faire pointer le dernier sur le 2 ème elem
        }
        free(premier) ; 
    }
}

// Une fonction pour afficher la file (On ne peut plus utiliser afficher liste car le dernier bloc ne pointe plus sur NULL mais sur le premier)
void affiche_file(File *f) {
    if (f->dernier == NULL) {
        printf("[]\n") ; 
        return ; 
    }
    printf("[");

    Bloc * premier = f->dernier->suite ; // Récupérer le premier 
    Bloc * courant = premier ; 

    printf("%d", courant->valeur) ;  // L'afficher en dehors de la boucle 
    courant = courant->suite ; 

    while (courant != premier) {
        printf(", %d", courant->valeur);
        courant = courant->suite ; 
    }
    printf("]");
}
