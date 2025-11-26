
/****************** binôme : farah.bentekhici@universite-paris-saclay.fr / saintaubinreginald@gmail.com  ****/
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
    int v1, v2, v3 ; 
    v1 = v2 = v3 = 0 ; // Initialisation de 3 variables à 0 au cas ou c'est nul ça vaudra 0 pour le calcul de la somme 
    if (L != NULL) {       // if imbriqués afin de ne pas essayer d'accéder au bloc suivant si L == NULL (Ce qui engendrerait une seg fault)
        v1 = L->valeur ;    
        if (L->suite != NULL) {
            v2 = L->suite->valeur ;

            if (L->suite->suite != NULL) {
                v3 = L->suite->suite->valeur ;
            }
        }
    }
    return (v1 + v2 == v3) ; 
}
   
/********************************************/
/*                                          */
/*             PlusCourte                   */
/*                                          */
/********************************************/

bool PlusCourteRec (Liste L1, Liste L2) {
    if (L1 == NULL && L2 == NULL)   // Tester si les 2 listes sont vides 
        return false; 
    if (L1 == NULL && L2 != NULL)   // Si la 1 ère est null et pas la 2 ème
        return true; 
    if (L2 == NULL && L1 != NULL)   // Le contraire 
        return false;
    return PlusCourteRec(L1->suite, L2->suite);  
}

/*******/
  
bool PlusCourteIter (Liste L1, Liste L2) {

     return true ; 
}
   
  
/********************************************/
/*                                          */
/*              Verifiek0                   */
/*                                          */
/********************************************/

bool VerifiekORec (Liste L, int k) {
    if (L==NULL && k==0)
        return true;
    if (L==NULL && k != 0)
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
    while (L_aux!=NULL && k>0) {
        if (L_aux->valeur == 0) {
            k=k-1 ;
        }
        L_aux = L_aux->suite ;
    }
    return L==NULL && k==0 ;
}
   

/********************************************/
/*                                          */
/*     NombreTermesAvantZero                */
/*                                          */
/********************************************/

int NTAZ_It (Liste L) {
    if (L==NULL)
        return 0 ;
    Liste copie=L;
    int compteur=0;
    while (copie !=NULL && copie->valeur!=0) {
        compteur+=1 ;
        copie=copie->suite ;
    }
    return compteur ;

}

/*******/

int NTAZ_Rec (Liste L)
   { return 0 ; }

/*******/

int NTAZ_RTSF (Liste L)
   { return 0 ; }

/*******/
void NTAZ_RTSP_terminal(Liste L, int *compteur) {
    if (L == NULL || L->valeur == 0)
        return;
    else {
        (*compteur)++; // compteur
        NTAZ_RTSP_terminal(L->suite, compteur);
    }
}
int NTAZ_RTSP (Liste L) {
    int compteur =0 ;
    NTAZ_RTSP_terminal(L, &compteur);
    return compteur ;
}


/********************************************/
/*                                          */
/*              TuePos                      */
/*                                          */
/********************************************/
void TuePosRec_aux(Liste *L, int i) {
    if(*L == NULL)
        return; 
    if((*L)->valeur == i) {
        depile(L); 
        TuePosRec_aux(L, i++) ; 
    }
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
        // Initialisation liste l :
        l = NULL ; 
        l = ajoute(5, l) ; 
        l = ajoute(3, l) ; 
        l = ajoute(2, l) ;
        printf("La liste l : ") ; 
        affiche_rec(l) ;
        
        // Initialisation liste m :
        Liste m = NULL; 
        m = ajoute(5, m) ; 
        m = ajoute(3, m) ; 
        m = ajoute(2, m) ; 
        m = ajoute(4, m) ; 
        printf("La liste m : ") ; 
        affiche_rec(m) ;

        // Initialisation de deux listes vides : 
        Liste n = NULL ; 
        Liste p = NULL ; 

        // Test UnPlusDeux
        if(UnPlusDeuxEgalTrois(n) == true) 
            printf("Un Plus Deux Egal Trois sur n : true\n") ;
        else
            printf("Un Plus DeuxEgal Trois sur n : false\n") ;  

        // Test plus courte 
        
        if(PlusCourteRec (m, n) == true)
            printf("La premiere liste est strictement plus petite que la deuxieme : true \n");
        else  
            printf("La premiere liste est strictement plus petite que la deuxieme : false \n"); 
    
        printf("%d",NTAZ_RTSP(m));

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

        //Liste test_NTAZ_SP = NULL ;
        //test_NTAZ_SP = ajoute(9,test_NTAZ_SP) ;
        //printf("%d\n",NTAZ_RTSP(test_NTAZ_SP));

        VideListe(&m) ; 
        VideListe(&p) ; 
        VideListe(&l) ; 
        VideListe(&n) ; 

    return 0;
}









