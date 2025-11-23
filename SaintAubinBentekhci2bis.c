//
// Created by saint on 22/11/2025.
/****************** binôme : farah.bentekhici@universite-paris-saclay.fr / saintaubinreginald@gmail.com  ****/
//
#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/*                                               */
/*                type bool�en                   */
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


/*** les 5 fonctionnalit�s suivantes sont plus du sucre syntaxique que du code utile  ***/
/*** sauf � vouloir pouvoir basculer � moindre frais sur une impl�menation des listes ***/
/**** diff�rentes des listes chain�es propos�es dans le cadre de ce projet            ***/

// Liste Vide() { return NULL ; }
// void initVide(Liste *L) { *L = NULL ; }
// bool estVide(Liste l) { return l == NULL ; }
// int premier(Liste l) { return l->valeur ; }
// Liste suite(Liste l) { return l->suite ; }

/****************/

void depile(Liste *L)
{   Liste tmp = *L ;
    *L = (*L)->suite ;
    free(tmp) ;
}

/*******/

Liste ajoute(int x, Liste l)
{   Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->valeur = x ;
    tmp->suite = l ;
    return tmp ;
}

/*******/

void empile(int x, Liste *L)
{ *L = ajoute(x,*L) ; }

/*****************************/
/*                           */
/*       Affiche             */
/*                           */
/*****************************/

void affiche_rec(Liste l)
{
    if (l == NULL)
        printf("\n");
    else
    {
        printf("%d ", l->valeur);
        affiche_rec(l->suite);
    }
}


/*******/

void affiche_iter(Liste l)
{
    Liste L2 = l;
    while( L2 != NULL )
    {
        printf("%d ", L2->valeur);
        L2 = L2->suite;
    }
    printf("\n");
}

/****************************/
/*                          */
/*       Longueur           */
/*                          */
/****************************/

int longueur_rec (Liste l)
{
    if (l == NULL)
         return 0 ;
    else return (1 + longueur_rec(l->suite)) ;
}

/*******/

int longueur_iter (Liste l)
{
    Liste P = l;
    int cpt = 0 ;
    while (P != NULL)
    {   P = P->suite ;
        cpt++ ;
    }
    return cpt ;
}

/*****************************************/
/*                                       */
/*                 VireDernier           */
/*     avec un depile                    */
/* � la main opportuniste (version iter) */
/* ou en utilisant depile (version rec ) */
/*                                       */
/*****************************************/

void VD (Liste *L)
          // *L non NULL ie liste non vide
{
     if ( (*L)->suite == NULL )
            depile(L) ;   // moralement : depile(& (*L)) ;
     else VD (& (*L)->suite) ;
}

void VireDernier_rec (Liste *L)
{
     if ( *L != NULL )
          VD(L);        // moralement : VD(& (*L)) ;
}

/*************/

void VireDernier_iter (Liste *L)
{
    if ( *L != NULL)
    {
        while ( (*L)->suite != NULL )
                 L = & (*L)->suite  ;   //  &  (**L).suite  ;
        free(*L) ;
        *L = NULL ;
     }
}


/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideListe(Liste *L)
{
    if ( *L != NULL )
    {
        depile(L);
        VideListe(L);
    }

}

/*Fonction __de concaténation*/

Liste concatenation (Liste L1, Liste L2) {
    if (L1==NULL) {
        return L2 ;
    }
    Liste nouvelle_liste = L1 ;
    while (nouvelle_liste->suite != NULL) {
        nouvelle_liste=nouvelle_liste->suite;
    }
    nouvelle_liste->suite=L2 ;
    return L1 ;

}
Liste Placedevant(int x,Liste L) {
    if (L==NULL) {
        return NULL ;
    }
    Liste l_ensortie=NULL ;
    Liste L2=L; //C'est la liste de copie
    Liste d= NULL ;
    while (L2!=NULL) {
        Liste bloc_x=(Liste)malloc(sizeof(Bloc)) ;
        bloc_x->valeur= x ;
        Liste l_base=(Liste)malloc(sizeof(Bloc)) ;
        l_base->valeur=L2->valeur ;
        l_base->suite=NULL;
        bloc_x->suite=l_base ;
        l_ensortie=bloc_x ;
        L2=L2->suite ;
    }
    return l_ensortie ;
}
