#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct bloc_image
{ bool blanc ;
    struct bloc_image * Im[4] ;
} bloc_image ;
typedef bloc_image *image ;
//etape 1
image Wht() {
    image i =  malloc(sizeof( bloc_image)) ;
    i->blanc = true ;
    for (int ind =0; ind < 4; ind++) {
        i->Im[ind]= NULL ;
    }
    return i ;
}
image Blk() {
    return NULL;
}
image Cut(image i0, image i1, image i2, image i3) {
    image img = malloc(sizeof(bloc_image));
    img->blanc = false;
    img->Im[0] = i0;
    img->Im[1] = i1;
    img->Im[2] = i2;
    img->Im[3] = i3;
    return img;
}
//etape 2

void Affiche(image img) {
    if (img==NULL) {
        putchar('Z') ;
    }
    else if (img->blanc) {
        putchar('o') ;
    }
    else {
        putchar('*') ;
        for (int ind = 0; ind < 4; ind++) {
            Affiche(img->Im[ind]) ;
        }
    }
}
// etape 3
void ProfAfficheRec(image img,int prof) {
    if (img==NULL) {
        printf("Z%d",prof);
    }
    else if (img->blanc) {
        printf("o%d",prof);
    }
    else {
        printf("*%d",prof);
        for (int ind = 0; ind < 4; ind++) {
            ProfAfficheRec(img->Im[ind],prof + 1);
        }
    }
}

void ProfAffiche(image img) {
    ProfAfficheRec(img,0);
}
// etape 4

image Lecture () {
    int c;

    do {
        c = getchar();
        if (c == EOF) return NULL;
    } while (c != 'o' && c != 'Z' && c != '*');

    if (c == 'o') return Wht();
    if (c == 'Z') return Blk();

    // cas '*'
    image i0 = Lecture();
    image i1 = Lecture();
    image i2 = Lecture();
    image i3 = Lecture();

    return Cut(i0, i1, i2, i3);

}
// etape 5

bool DessinNoir(image img) {
    return img == NULL;
}
bool DessinBlanc(image img) {
    return (img != NULL && img->blanc);
}
// etape 6
void QuotaRec(image img, double taille, double *noir, double *total) {
    if (img == NULL) {
        *noir += taille;
        *total += taille;
    }
    else if (img->blanc) {
        *total += taille;
    }
    else {
        for (int i = 0; i < 4; i++)
            QuotaRec(img->Im[i], taille / 4.0, noir, total);
    }
}

double QuotaNoir(image img) {
    double noir = 0.0, total = 0.0;
    QuotaRec(img, 1.0, &noir, &total);
    return noir / total; // retour du taux
}
// etape 7
image Copie(image img) {
    if (img==NULL) {
        return NULL;
    }
    if (img->blanc) {
        return Wht() ;
    }
    image i0 = Copie(img->Im[0]);
    image i1 = Copie(img->Im[1]);
    image i2 = Copie(img->Im[2]);
    image i3 = Copie(img->Im[3]);

    return Cut(i0, i1, i2, i3); // renvoie de la copie des images
}
// etape 8
image Diagonale(int p) {
    if (p==0) {
        return Blk() ; // Ca veut dire que c'est un pixel noir
    }
    image bd = Diagonale(p-1);
    image hg = Diagonale(p-1);
    image hd = Wht() ;
    image bg = Wht() ;
    return Cut(hg, hd, bg, bd) ;
}
// Fonction indispensable
void FreeImage(image img) {
    if (img==NULL) {
        return ; //pixel noir est considére comme
    }

    if (img->blanc) {
        free(img) ;
        return;
    }
    for (int i=0;i<4;i++) {
        FreeImage(img->Im[i]); //Libération recursives de 4 sous images et libération du noeud courant
    }
    free(img) ;
}
// etape 9
void SimplifieProfP(image *img,int p) {
    if (*img == NULL) {
        return ;
    }
    if (p==0) {
        if (DessinNoir(*img)) {
            FreeImage(*img); // Blk() retourne Null mais on libère avant pour éviter une fuite mémoire
            *img = Blk() ;
        }

        else if (DessinBlanc(*img)) {
            FreeImage(*img);
            *img = Wht() ;
        }
        return;
    }
    if ((*img)->blanc) return ;

    for (int i = 0; i < 4; i++) {
        SimplifieProfP(&(*img)->Im[i] , p - 1) ;
    }
    //Les anciens arbres doivent etre "free" les sous-arbres remplacés

}
// etape 10
bool Incluse(image i1 , image i2) {
    //i1,la première image est toute noir
    if (i1==NULL) {
        return (i2==NULL) ;
    }
    // si la premiere n'est pas noir alors blanche
    if (i1->blanc) {
        return true ;
    }
    // i1 composee
    if (i2==NULL || i2->blanc) {
        return false ;
    }
    for (int i = 0; i < 4; i++) {
        if (!Incluse(i1->Im[i], i2->Im[i])) {
            return false ;
        }
    }
    return true ;
}
// etape 11

int CompteImagesGrises(image img) {
    if (img==NULL) {
        return 0 ;//pixel noir
    }
    int count = 0;

    double q= QuotaNoir(img) ;
    if (q>= 1.0 /3.0 && q<=2.0 /3.0) {
        count++ ;
    }
    if (!img->blanc) {
        for (int i = 0; i < 4; i++) {
            count -=- CompteImagesGrises(img->Im[i]);
        }
    }
    return count ;
}
// Fonction labyrinthe (etape 12)
// Remplit la grille pixel par pixel à partir de l'arbre
void RemplirGrille(image img, int x, int y, int taille, bool **grille) {
    if (img == NULL) {
        for (int i = 0;i<taille;i++) {
            for (int j =0;j<taille;j++) {
                grille[y+i][x+j] = false;
            }
        }
        return;
    }

    if (img->blanc) {
        for (int i = 0; i < taille; i++)
            for (int j = 0; j < taille; j++)
                grille[y+i][x+j] = true; // blanc
        return;
    }
    int moitie = taille / 2; // Taille des 4 sections
    //Appel recursif sur les 4 sous-blocs
    RemplirGrille(img->Im[0], x, y, moitie, grille);              // haut-gauche
    RemplirGrille(img->Im[1], x + moitie, y, moitie, grille);       // haut-droit
    RemplirGrille(img->Im[2], x, y + moitie, moitie, grille);       // bas-gauche
    RemplirGrille(img->Im[3], x + moitie, y + moitie, moitie, grille); // bas-droit
}

// existe_chemin pour vérifier si un chemin existe
bool existe_chemin(bool **grille, int n, int x, int y, bool **visite) {
    if (x < 0 || y < 0 || x >= n || y >= n)
        return false;
    if (!grille[y][x] || visite[y][x])
        return false;
    if (x == n-1 && y == n-1)
        return true;

    visite[y][x] = true;

    return existe_chemin(grille, n, x+1, y, visite) || // droite
           existe_chemin(grille, n, x-1, y, visite) || //gauche
           existe_chemin(grille, n, x, y+1, visite) || //bas
           existe_chemin(grille, n, x, y-1, visite); //haut
}

bool Labyrinthe(image img, int p) {
    int n = 1 << p;

    // Création de la grille
    bool **grille = malloc(n * sizeof(bool*));
    bool **visite = malloc(n * sizeof(bool*));
    for (int i = 0; i < n; i++) {
        grille[i] = calloc(n, sizeof(bool));
        visite[i] = calloc(n, sizeof(bool));
    }

    RemplirGrille(img, 0, 0, n, grille);

    bool res = existe_chemin(grille, n, 0, 0, visite); // lancer recherche de chemins

    for (int i = 0; i < n; i++) {
        free(grille[i]);
        free(visite[i]);
    }
    free(grille);
    free(visite);
    // La fonction Remplir Grille errone partiellement la fonction Labyrinthe
    return res;
}
int main() {
    printf("=== TESTS DE BASE ===\n");

    // Test 1 : image blanche
    image w = Wht();
    printf("Image blanche : ");
    Affiche(w);
    printf("\n");
    ProfAffiche(w);
    printf("\n");

    // Test 2 : image noire
    image b = Blk();
    printf("Image noire : ");
    Affiche(b);
    printf("\n");
    ProfAffiche(b);
    printf("\n");

    // Test 3 : image composée simple
    image img = Cut(Wht(), Blk(), Wht(), Blk());
    printf("Image mixte : ");
    Affiche(img);
    printf("\n");
    ProfAffiche(img);
    printf("\n");

    // Test 4 : Copie
    image copie = Copie(img);
    printf("Copie de l'image : ");
    Affiche(copie);
    printf("\n");

    // Test 5 : Diagonale
    image diag = Diagonale(3);
    printf("Diagonale p=3 : ");
    Affiche(diag);
    printf("\n");

    // Test 6 : Quota noir
    image enonce = Cut(
        Blk(),
        Cut(Wht(), Blk(), Wht(), Wht()),
        Blk(),
        Cut(Blk(), Blk(), Blk(), Wht())
    );
    printf("Quota noir (image enonce) : %.2f\n", QuotaNoir(enonce));

    // Test 7 : Inclusion
    image i1 = Cut(Wht(), Wht(), Wht(), Wht());
    image i2 = Cut(Wht(), Blk(), Wht(), Wht());
    printf("i2 incluse dans i1 ? %s\n", Incluse(i2, i1) ? "vrai" : "faux");
    printf("i1 incluse dans i2 ? %s\n", Incluse(i1, i2) ? "vrai" : "faux");

    // Test 8 : Images grises
    image gris = Cut(
        Cut(Wht(), Blk(), Wht(), Wht()),
        Blk(),
        Cut(Wht(), Wht(), Blk(), Blk()),
        Wht()
    );
    printf("Nombre d'images grises : %d\n", CompteImagesGrises(gris));

    // Test 9 : Simplification profondeur 1
    image simplifie = Copie(gris);
    SimplifieProfP(&simplifie, 1);
    printf("Image simplifiée (prof=1) : ");
    Affiche(simplifie);
    printf("\n");

    // Test 10 : Simplification profondeur 2
    image simplifie2 = Copie(gris);
    SimplifieProfP(&simplifie2, 2);
    printf("Image simplifiée (prof=2) : ");
    Affiche(simplifie2);
    printf("\n");

    printf("\n=== TESTS LABYRINTHE ===\n");

    // Labyrinthe 1 : chemin simple
    image lab1 = Cut(Wht(), Blk(), Wht(), Wht());
    printf("Labyrinthe 1 (attendu: vrai) : %s\n", Labyrinthe(lab1,2) ? "vrai" : "faux");

    // Labyrinthe 2 : bloqué
    image lab2 = Cut(Wht(), Blk(), Blk(), Wht());
    printf("Labyrinthe 2 (attendu: faux) : %s\n", Labyrinthe(lab2,2) ? "vrai" : "faux");

    // Labyrinthe 3 : diagonale p=2 (chemin en diagonale)
    image lab3 = Diagonale(2);
    printf("Labyrinthe 3 (diagonale p=2) (attendu : vrai): %s\n", Labyrinthe(lab3,2) ? "vrai" : "faux");

    // Labyrinthe 4 : complet blanc p=3
    image lab4 = Wht();
    printf("Labyrinthe 4 (tout blanc p=3) : %s\n", Labyrinthe(lab4,3) ? "vrai" : "faux");

    // Labyrinthe 5 : complet noir p=3
    image lab5 = Blk();
    printf("Labyrinthe 5 (tout noir p=3) : %s\n", Labyrinthe(lab5,3) ? "vrai" : "faux");

    // Labyrinthe 6 : plus complexe
    image lab6 = Cut(
        Cut(Wht(), Blk(), Blk(), Wht()),
        Wht(),
        Blk(),
        Cut(Wht(), Wht(), Blk(), Wht())
    );
    printf("Labyrinthe 6 (complexe) : %s\n", Labyrinthe(lab6,3) ? "vrai" : "faux");

    // Labyrinthe 7 : bordure noire
    image lab7 = Cut(
        Blk(), Blk(),
        Blk(), Wht()
    );
    printf("Labyrinthe 7 (bordure noire) : %s\n", Labyrinthe(lab7,2) ? "vrai" : "faux");

    // Labyrinthe 8 : chemin étroit
    image lab8 = Cut(
        Wht(), Blk(),
        Wht(), Blk()
    );
    printf("Labyrinthe 8 (chemin étroit) : %s\n", Labyrinthe(lab8,2) ? "vrai" : "faux");

    // Labyrinthe 9 : alternance noir/blanc
    image lab9 = Cut(
        Blk(), Wht(),
        Wht(), Blk()
    );
    printf("Labyrinthe 9 (alternance) : %s\n", Labyrinthe(lab9,2) ? "vrai" : "faux");
    image lab_complexe =
    Cut(
        /* 1er quadrant */
        Cut(
            Cut(
                Wht(), Wht(), Blk(), Wht()
            ),
            Blk(),
            Cut(
                Blk(), Blk(), Wht(), Wht()
            ),
            Cut(
                Wht(), Wht(), Blk(), Blk()
            )
        ),

        /* 2e quadrant */
        Cut(
            Cut(
                Wht(), Wht(), Blk(), Blk()
            ),
            Cut(
                Wht(), Blk(), Blk(), Wht()
            ),
            Cut(
                Wht(),
                Cut(Wht(), Wht(), Blk(), Wht()),
                Blk(),
                Cut(Wht(), Wht(), Wht(), Blk())
            ),
            Cut(
                Wht(),
                Blk(),
                Cut(Wht(), Wht(), Wht(), Blk()),
                Cut(Wht(), Blk(), Wht(), Blk())
            )
        ),

        /* 3e quadrant */
        Cut(
            Blk(),
            Cut(
                Cut(Wht(), Wht(), Blk(), Wht()),
                Wht(),
                Wht(),
                Blk()
            ),
            Blk(),
            Cut(
                Wht(), Wht(), Wht(), Blk()
            )
        ),

        /* 4e quadrant */
        Cut(
            Cut(
                Wht(), Blk(), Blk(), Blk()
            ),
            Blk(),
            Cut(
                Wht(), Wht(), Wht(), Blk()
            ),
            Cut(
                Wht(),
                Blk(),
                Wht(),
                Cut(Wht(), Wht(), Blk(), Wht())
            )
        )
    );
    printf("Labyrinthe complexe (attendu: vrai) : %s\n",
       Labyrinthe(lab_complexe, 4) ? "vrai" : "faux");

    // Libération mémoire
    FreeImage(w);
    FreeImage(b);
    FreeImage(img);
    FreeImage(copie);
    FreeImage(diag);
    FreeImage(enonce);
    FreeImage(i1);
    FreeImage(i2);
    FreeImage(gris);
    FreeImage(simplifie);
    FreeImage(simplifie2);
    FreeImage(lab1);
    FreeImage(lab2);
    FreeImage(lab3);
    FreeImage(lab4);
    FreeImage(lab5);
    FreeImage(lab6);
    FreeImage(lab7);
    FreeImage(lab8);
    FreeImage(lab9);

    return 0;
}
