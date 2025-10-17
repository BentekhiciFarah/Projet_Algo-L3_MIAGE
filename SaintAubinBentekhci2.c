
/************     Mon�me rosaz@lisn.fr    ******/

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

/********************************************/
/*                                          */
/*          UnPlusDeuxgalTrois              */
/*                                          */
/********************************************/

bool UnPlusDeuxEgalTrois (Liste L) {
    if (L == NULL)
        return false; 
    if ((L->valeur + L->suite->valeur) == L->suite->suite->valeur)
        return true ; 
}
   
/********************************************/
/*                                          */
/*             PlusCourte                   */
/*                                          */
/********************************************/

bool PlusCourteRec (Liste L1, Liste L2) {
    if (L1 == NULL && L2 != NULL)
        return true; 
    if (L2 == NULL && L1 != NULL)
        return false;
    if(L1 == NULL && L2 == NULL)    // Rien à dire car c strictement inf qui est demandé 
        return false; 
    return PlusCourteRec(L1->suite, L2->suite);  
}

/*******/

// Compter le nbr d'éléments de manière simultanée, dès que y en a une qui se finit on dit qu'elle est plus courte
bool PlusCourteIter (Liste L1, Liste L2) {
    int cpt1 = 0; int cpt2 = 0; 

    while (L1 != NULL && L2 != NULL) {
        cpt1++; 
        cpt2++; 
        L1 = L1->suite; 
        L2 = L2->suite; 
    }
    if (L1 == NULL)     // car on sait pas laquelle s'est terminée en premier 
        cpt2++; 
    else 
        cpt1++; 
    if(cpt1 < cpt2)
        return true; 
    return false; 
}
   
  
/********************************************/
/*                                          */
/*              Verifiek0                   */
/*                                          */
/********************************************/

bool VerifiekORec (Liste L, int k) {
    if (L==NULL && k==0)
        return true;
    if (L==NULL && k>0)
        return false;
    if (L->valeur == 0 && k>0) {
        return VerifiekORec(L->suite, k-1) ;
    }
    return VerifiekORec(L->suite, k);

}
   
/*******/

bool VerifiekOIter (Liste L, int k) {
    if (L==NULL && k==0)
        return true ;
    if (L==NULL && k>0)
        return false ;
    Liste L_aux=L ;
    while (L_aux != NULL && k>0) {
        if (L_aux->valeur == 0) {
            k=k-1 ;
        }
        L_aux = L_aux->suite ;
    }
    return (k == 0); 
}
   

/********************************************/
/*                                          */
/*     NombreTermesAvantZero                */
/*                                          */
/********************************************/

int NTAZ_It (Liste L)
   { return 0 ; }

/*******/

int NTAZ_Rec (Liste L)
   { return 0 ; }

/*******/

int NTAZ_RTSF (Liste L)
   { return 0 ; }

/*******/

int NTAZ_RTSP (Liste L)
   { return 0 ; }


/********************************************/
/*                                          */
/*              TuePos                      */
/*                                          */
/********************************************/
void TuePosRec_aux(Liste *L, int i) {
    if(*L == NULL)
        return; 
    if((*L)->valeur == i)
        depile(L); 
    else 
        TuePosRec_aux(&(*L)->suite, i++); 
}

void TuePosRec (Liste * L) { // * L car on veut modifier le contenu 
    if (* L == NULL)
        return; 
    TuePosRec_aux(L, 1); 
}


/*******/

void TuePosIt (Liste * L) {}

/********************************************/
/*                                          */
/*            TueRetroPos                   */
/*                                          */
/********************************************/

void TueRetroPos (Liste * L) {}

/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/


// int main(int argc, char** argv)

int main()
{
Liste l ;
    // Initialisation liste l  
    l = NULL; 
    l = ajoute(1, l); 
    l = ajoute(3, l); 
    l = ajoute(0, l); 
    affiche_rec(l);


    // Initialisation liste m 
    Liste m = NULL; 
    m = ajoute(5, m); 
    m = ajoute(3, m); 
    m = ajoute(2, m); 
    m = ajoute(4, m); 
    affiche_rec(m);

    // Test plus courte rec
    if(PlusCourteRec (l, m) == true)
        printf("PlusCourteRec : true\n");
    else  
        printf("PlusCourteRec : false\n"); 

    // Test plus courte iter
    if(PlusCourteIter (l, m) == true)
        printf("PlusCourteIter : true\n");
    else  
        printf("PlusCourteIter :false\n");

    // Test Verifiek0 rec
    if(VerifiekORec(l,2) == true)
        printf("VerifiekORec : true\n");
    else  
        printf("VerifiekORec :false\n");

    // Test Verifk0 iter  
    if(VerifiekOIter(l,2) == true)
        printf("VerifiekOIter : true\n");
    else  
        printf("VerifiekOIter :false\n");


    // Teste UnPlusDeux
    if(UnPlusDeuxEgalTrois(l) == true) 
        printf("UnPlusDeuxEgalTrois : true\n");
    else 
        printf("UnPlusDeuxEgalTrois : false\n");  

    TuePosRec (l); 
    affiche_rec(l); 


    //VireDernier_rec  (&l) ;
    //VireDernier_iter (&l) ;
    //affiche_rec(l) ; 
    //affiche_iter(l) ; 
    //printf(" %d \n", longueur_iter(l)) ; 
    //printf(" %d \n", longueur_rec(l)) ; 
    //VideListe(&l);
    return 0;
}








