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
//Création d'une nouvelle structure de données
typedef struct BlocListeDeListes {
    Liste sous_liste ;
    struct  BlocListeDeListes * suite;
}BlocListeDeListes;

typedef BlocListeDeListes *ListeDeListes ;

// Initialisation de notre Liste de Liste vides
// Structure pour stocker nos données
ListeDeListes LdVide() {
    return NULL ;
}

// Fonction inspirer des méthodes nous ayant été fournis
// Pour ajouter nos variables sucessivement
ListeDeListes ajoute_liste(Liste l,ListeDeListes ld) {
    ListeDeListes nouveau = (ListeDeListes)malloc(sizeof(BlocListeDeListes)); // On réalloue un BlocListeDeListes
    nouveau->sous_liste = l ;
    nouveau->suite= ld ;
    return nouveau ;
}

// Fonction de concaténation deux listes de listes
//utiliser en prévision pour les variables avec des "débuts" différents des listes
ListeDeListes concat_ld(ListeDeListes ld1,ListeDeListes ld2) {
    if (ld1==NULL) {
        return ld2 ;
    }
    if (ld2==NULL) {
        return ld1 ;
    }
    ListeDeListes courant = ld1 ;
    while (courant->suite != NULL) {
        courant = courant->suite ;
    }
    courant->suite = ld2 ;
    return ld1 ; //ld1 est maintenant = ld1+ld2
}

// Fonction classique de copie parcourant et écrivant tous les éléments de la liste d'ordre de grandeur n
Liste copie_liste(Liste l) {
    if (l==NULL) {
        return NULL ;
    }
    return ajoute(l->valeur, copie_liste(l->suite)) ;
}
// Fonctions réalisant clairement la partie PPQ
void affiche_liste_de_listes(ListeDeListes ld) {
    printf("[");
    int premier = 1 ;
    while (ld != NULL) {
        if (!premier) {
            printf(", ") ;
        }
        affiche_liste(ld->sous_liste) ;
        premier = 0 ;
        ld=ld->suite ;
    }
    printf("]\n");
}
//Fonction libération d'une liste
void libere_liste(Liste liste) {
    while (liste != NULL) {
        Liste tmp = liste ;
        liste = liste->suite ;
        free(tmp) ;
    }
}
// Fonction influant sur la gestion de mémoire liste de liste
void libere_liste_de_listes(ListeDeListes ld) {
    while (ld != NULL) {
        libere_liste(ld->sous_liste) ; // Typedef struct bloc nous facilite le jonglage de mémoire
        ListeDeListes tmp =ld;
        ld=ld->suite ;
        free(tmp) ;
    }
}

// Fonction de création de liste avec élément trouve
Liste creer_liste_avec_element(int x,Liste sous_liste) {
    return ajoute(x,copie_liste(sous_liste)) ;
}




// Gestion des cas de base
ListeDeListes cas_base(int p1,int p2, int q) {
    // Cas de base q==0
    if (q==0 ||p2<p1 ) {
        return ajoute_liste(NULL,LdVide()) ;
    }
    if (q<p1) {
        return LdVide() ;
    }

    return NULL ;
}

// FONCTION PPQ PRINCIPALE
ListeDeListes PPQ(int p1, int p2, int q) {
    //Verification cas de base
    ListeDeListes c_b = cas_base(p1,p2,q) ;
    if (c_b!=NULL) {
        return c_b ;
    }

    // Itération sur toutes les valeurs possibles
    ListeDeListes resultat = LdVide() ;

    for (int i=p1; i<=p2;i++) {
        if (i<=q) {
            //Obtention des solutions pour q-i
            ListeDeListes solution_restantes = PPQ(p1,p2,q-i) ;
            //Pour chaque solution restante on lui ajoute i au début
            ListeDeListes courant = solution_restantes;
            while (courant!=NULL) {
                // Création d'une new liste avec i au début de la solution courante
                Liste nouvelle_solution = ajoute(i,copie_liste(courant->sous_liste)) ;

                // ajout au résultat
                resultat = concat_ld(resultat, ajoute_liste(nouvelle_solution, LdVide()));
                courant=courant->suite ;
            }
            // Liberer
            libere_liste_de_listes(solution_restantes) ;
        }
    }
    return resultat ;
}


int main() {
    printf("\nTest PPQ(2, 4, 9):\n");
    ListeDeListes test1 = PPQ(2, 4, 9);
    if (test1 == NULL) {
        printf("Aucune solution trouvee\n");
    } else {
        affiche_liste_de_listes(test1);
        libere_liste_de_listes(test1);
    }
    if (true){
        printf("=== TESTS AVEC CAS LIMITES ===\n");


        // Test 2: Cas où p = q (doit retourner une seule liste avec juste p)
        printf("\nTest PPQ(3, 3, 3):\n");
        ListeDeListes test2 = PPQ(3, 3, 3);
        if (test2 == NULL) {
            printf("Aucune solution trouvée\n");
        } else {
            affiche_liste_de_listes(test2);
            libere_liste_de_listes(test2);
        }
        // Test 3: Cas avec de grands nombres
        printf("\nTest PPQ(10, 15, 100):\n");
        ListeDeListes test3 = PPQ(10, 15, 78); // Cas tester avec comme p2=14 mais prend beaucoup plus de temps et de mémoire
        if (test3 == NULL) {
            printf("Aucune solution trouvée\n");
        } else {
            affiche_liste_de_listes(test3);
            libere_liste_de_listes(test3);
        }


        // Test 4: Cas où n est très petit
        printf("\nTest PPQ(1, 2, 1):\n");
        ListeDeListes test4 = PPQ(1, 2, 1);
        if (test4 == NULL) {
            printf("Aucune solution trouvee\n");
        } else {
            affiche_liste_de_listes(test4);
            libere_liste_de_listes(test4);
        }

        // Test 5: Cas où p > q
        printf("\nTest PPQ(4, 2, 6):\n");
        ListeDeListes test5 = PPQ(4, 2, 6);
        if (test5 == NULL) {
            printf("Aucune solution trouvee (p > q)\n");
        } else {
            affiche_liste_de_listes(test5);
            libere_liste_de_listes(test5);
        }

        // Test 6: Cas avec n = 0 (doit retourner liste vide)
        printf("\nTest PPQ(1, 3, 0):\n");
        ListeDeListes test6 = PPQ(1, 3, 0);
        if (test6 == NULL) {
            printf("Aucune solution trouve\n");
        } else {
            affiche_liste_de_listes(test6);
            libere_liste_de_listes(test6);
        }

        // Test 7: Cas où n est négatif
        printf("\nTest PPQ(1, 3, -5):\n");
        ListeDeListes test7 = PPQ(1, 3, -5);
        if (test7 == NULL) {
            printf("Aucune solution trouvee (n negatif)\n");
        } else {
            affiche_liste_de_listes(test7);
            libere_liste_de_listes(test7);
        }

        // Test 8: Cas avec p = 1 (tous les nombres sont possibles)
        printf("\nTest PPQ(1, 5, 7):\n");
        ListeDeListes test8 = PPQ(1, 5, 7);
        if (test8 == NULL) {
            printf("Aucune solution trouvée\n");
        } else {
            affiche_liste_de_listes(test8);
            libere_liste_de_listes(test8);
        }

        // Test 9: Cas où la seule solution est une liste à un élément
        printf("\nTest PPQ(7, 7, 7):\n");
        ListeDeListes test9 = PPQ(7, 7, 7);
        if (test9 == NULL) {
            printf("Aucune solution trouvee\n");
        } else {
            affiche_liste_de_listes(test9);
            libere_liste_de_listes(test9);
        }

        // Test 10: Cas avec plusieurs solutions possibles
        printf("\nTest PPQ(2, 4, 5):\n");
        ListeDeListes test10 = PPQ(2, 4, 5);
        if (test10 == NULL) {
            printf("Aucune solution trouvee\n");
        } else {
            affiche_liste_de_listes(test10);
            libere_liste_de_listes(test10);
        }

        return 0;
    }
}