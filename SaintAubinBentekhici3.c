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
void QuotaRec(image img, int taille, int *noir, int *total) {
    if (img == NULL) {
        *noir += taille;
        *total += taille;
    }
    else if (img->blanc) {
        *total += taille;
    }
    else {
        for (int i = 0; i < 4; i++)
            QuotaRec(img->Im[i], taille / 4, noir, total);
    }
}

double QuotaNoir(image img) {
    int noir = 0, total = 0;
    QuotaRec(img, 1, &noir, &total);
    return (double)noir / total; // retour du taux
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
    return Cut(bd, hg, hd, hd) ;
}
int main() {
    // Test 1 : image blanche
    image w = Wht();
    printf("Image blanche : ");
    Affiche(w);
    printf("\n");

    // Test 2 : image noire
    image b = Blk();
    printf("Image noire : ");
    Affiche(b);
    printf("\n");

    // Test 3 : image composée
    image img = Cut(Wht(), Blk(), Wht(), Blk());
    printf("Image mixte : ");
    Affiche(img);
    printf("\n");

    // Test 4 : affichage avec profondeur
    printf("Affichage avec profondeur : ");
    ProfAffiche(img);
    printf("\n");

    // Test 5 : quota noir
    printf("Quota noir : %.2f\n", QuotaNoir(img));

    // Test 6 : copie
    image copie = Copie(img);
    printf("Copie image : ");
    Affiche(copie);
    printf("\n");

    // Test 7 : diagonale
    image d = Diagonale(2);
    printf("Diagonale p=2 : ");
    Affiche(d);
    printf("\n");

    return 0;
}