#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HORIZ 0
#define VERT 1

// 1 - creer une fonction qui prend la variable solution, et la variable tableauJoueur (par exemple) : un tableau rempli de 0, cette fonction doit copier certaines valeurs (grace au rand() % N) 
// de solution dans tableauJoueur afin d'initialiser une grille jouable ( car solution est bel est bien la solution, donc pas jouable par définition. ).
// un parametre doit permettre de verifier la condition de victoire en un seul coup (proposer votre façon de faire :) ) 


void generer(int solution[8][8], int nb_zeros) {
    int i, j, k;
    int genere[8][8];
    for(i=0; i<8; ++i) {
        for(j=0; j<8; ++j) {
            genere[i][j] = solution[i][j]; 
        }
    }
    
    int cases_a_zero[nb_zeros][2]; 
    for(k=0; k<nb_zeros; ++k) {
        i = rand() % 8;
        j = rand() % 8;

        int deja_choisie = 0;
        for(int l=0; l<k; ++l) {
            if(i==cases_a_zero[l][0] && j==cases_a_zero[l][1]) { 
                deja_choisie = 1;
                break;
            }
        }
        if(deja_choisie) {
            k--;
        } else {
            cases_a_zero[k][0] = i;
            cases_a_zero[k][1] = j;
            genere[i][j] = 4; // on met des 4 dans la grille
        }
    }

    for(i=0; i<8; ++i) {
        for(j=0; j<8; ++j) {
            solution[i][j] = genere[i][j]; 
        }
    }
}



// 2- une fonction saisir qui demande au joueur de saisir 3 informations: i, j , et v qui permettront de placer la valeur v aux coordonnées (i,j)

int saisir(int grille[8][8]) {
    int i, j, v;
    do {
        printf("---------------------------------");
        printf("\n");
        printf("D'abord donné la valeur verticale puis horizontale (ex: 0 0 1)");
        printf("\n");
        printf("Saisir les indices i et j (de 0 a 7) et la valeur v (0 ou 1), séparation avec espaces: ");
        scanf("%d %d %d", &i, &j, &v);
        printf("\n");
        printf("---------------------------------");
        printf("\n");
        
    } while (i < 0 || i > 7 || j < 0 || j > 7 || v < 0 || v > 1); 

    if (grille[i][j] == 4) { // si la case est 4 on peut la remplir
        grille[i][j] = v;
    }

    int nbElementsNonNuls = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (grille[i][j] != 4) {
                nbElementsNonNuls++; 
            }
        }
    }
    return nbElementsNonNuls;
}





// 3- apres chaque coordonnées il faut verifier les regles du sudoku sur le tableauJoueur donc : 
//fonction qui vérife les règles du takuzu

// - la fonction verifierLigneColonne ( qui verifie les lignes et les colonnes  sur lesquelles sont la nouvelle valeur)
int verifierLigneColonne(int grille[8][8], int sens, int num) {
    
    int nb_zeros = 0;
    int nb_uns = 0;
    for(int k=0; k<8; ++k) {
        if(sens == HORIZ && grille[num][k] == 0) {
            nb_zeros++;
        } else if(sens == VERT && grille[k][num] == 1) {
            nb_uns++;
        }
    }
    if(nb_zeros > 4 || nb_uns > 4) {
        printf("Erreur: trop de 0 ou de 1 sur une ligne");
        printf("\n");
        return 0;
    }

    nb_zeros = 0;
    nb_uns = 0;
    for(int k=0; k<8; ++k) {
        if(grille[k][num] == 0) {
            nb_zeros++;
        } else if(grille[k][num] == 1) {
            nb_uns++;
        }
    }
    if(nb_zeros > 4 || nb_uns > 4) {
        printf("Erreur: trop de 0 ou de 1 sur une colonne");
        return 0;
    }
    // printf("OK");
    return 1;
}



// - la fonction verifierGrille (qui fait ceci pour toute la grille et permet de definir la condition de victoire)
int verifierGrille(int grille[8][8]) {
    for(int i=0; i<8; ++i) {
        if(!verifierLigneColonne(grille, HORIZ, i) || !verifierLigneColonne(grille, VERT, i)) {
            return 0;
        }
    }
    // printf("OK");
    return 1;
}





int main(){
    // Ne pas toucher le code entre les commentaires
    srand( time( NULL ) );


    int i, j, k;
    printf("SOLUTION");  
    printf("\n");  
    printf("---------------------------------");  
    printf("\n");  

    int solution[8][8] = {
        {1,1,0,1, 0,1,0,0},
        {0,0,1,0, 1,0,1,1},
        {0,1,0,0, 1,1,0,1},
        {1,0,1,1, 0,0,1,0},
    
        {1,0,1,0, 0,1,1,0},
        {0,1,0,1, 1,0,0,1},
        {1,1,0,0, 1,0,1,0},
        {0,0,1,1, 0,1,0,1}
    };


    for(i=0;i<8; ++i) 
    {
    for(j=0; j<8; ++j)
        printf("%d ", solution[i][j]);
    printf("\n");  
    }
    printf("---------------------------------");  
    printf("\n");  
    //toucher le code entre les commentaires 









    int grille[8][8]; 
    int nb_zeros = 1; // Défini le nombre de 4 qu'on veut dans la grille
    generer(solution, nb_zeros); 

    for(int i=0; i<8; ++i) {
        for(int j=0; j<8; ++j) {
            grille[i][j] = solution[i][j]; 
        }
    }
    printf("Grille joueur");
    printf("\n"); 
    printf("---------------------------------");
    printf("\n"); 
    for(i=0; i<8; ++i) {
        for(j=0; j<8; ++j) {
            printf("%d ", grille[i][j]); 
        }
        printf("\n");
    }

    int remplissage = 63; // nombre de coup a jouer  plus c'est près de 64, moins on a de coup.
    while (remplissage < 64) { 

        remplissage = saisir(grille); 
        for(i=0; i<8; ++i) {
            for(j=0; j<8; ++j) {
                printf("%d ", grille[i][j]); 
                
            }
            printf("\n");
        }
        printf("---------------------------------");
        printf("\n");
        if (remplissage == 64) { 
            if(verifierGrille(grille)) {
                printf("La grille est correcte !\n");
            } else {
                printf("La grille est incorrecte.\n");
            }
        }
    }







    // Ne pas toucher au code ci dessous
    system("pause");
    return 0;
}

