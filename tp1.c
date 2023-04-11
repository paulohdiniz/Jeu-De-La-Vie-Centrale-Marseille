/***************************************************************/
/**                                                           **/
/**   Paulo Henrique DINIZ FERNANDES                          **/
/**   TP1                                                     **/
/**   11 avril 2023                                           **/
/**                                                           **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <stdbool.h>
#define MMAX 90
#define NMAX 90

int nbAleatoireUnouDeux(){ /*il return 1 ou 0 aleatoirement */
    return (rand() % 10 + 1)%2;
}
int counterVivantsAutour(char **matrice, int i, int j, int N, int M) {
    int count = 0;
    for (int x = i-1; x <= i+1; x++) {
        for (int y = j-1; y <= j+1; y++) {
            if (x >= 0 && x < N && y >= 0 && y < M && (x != i || y != j)) {
                if (matrice[x][y] == 'o') {
                    count++;
                }
            }
        }
    }
    return count;
}

bool deviantVivant(char **matrice, int i, int j, int N, int M){
    if (matrice[i][j] == ' '){
        if(counterVivantsAutour(matrice,i,j,N,M) == 3){
            return true;
        }else{
            return false;
        }
    }else if(matrice[i][j] == 'o'){
        if(counterVivantsAutour(matrice,i,j,N,M) == 3 || counterVivantsAutour(matrice,i,j,N,M) == 2){
            return true;
        }else{
            return false;
        }
    }
    return true;
}
/*fonction juste pour prendre les nouvelles valeurs sans changer la matrice original */
void attribuitionNouvelleMatrice(char **matrice,char **nouvelleMatrice, int N, int M){
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if(deviantVivant(matrice, i, j, N,M) == true){
                nouvelleMatrice[i][j] = 'o';
            }else{
                nouvelleMatrice[i][j] = ' ';
            }
        }
    }
}
void copierMatrice(char **matriceSource, char **matriceDestination, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            matriceDestination[i][j] = matriceSource[i][j];
        }
    }
}
void liberationMemoireChar(char **matrice, int N){
    for( int i = 0 ; i <  N; i++ ){
        free(matrice[i]);
    }
    free(matrice);
}

void affichage (char **MATRI, int N, int M)
{
    int i, j;
    /* prèmiere ligne */
    i = 1;
    printf ("      %d", i);
    for (i = 2; i < M; i++)
    {
        printf ("%3d", i);
    }
    i = M;
    printf ("%3d\n", i);
    /* 2eme linha */
    i = 1;
    printf ("   +");
    for (i = 1; i <= M; i++)
    {
        printf ("---");
    }
    i = M + 1;
    printf ("-+\n");
    /* 1ere linha du tableau*/
    i = 1;
    printf ("%-3d|", i);
    for (j = 0; j < M-1; j++)
    {
        printf ("%3c", MATRI[0][j]);
    }
    printf ("%3c |  1\n", MATRI[0][M-1]);
    /* 2eme ligne jusqu'a (m -1) */
    for (i = 2; i < N; i++)
    {
        printf ("%-3d|", i);
        for (j = 0; j < M-1; j++)
        {
            printf ("%3c", MATRI[i-1][j]);
        }
        printf ("%3c |  %d\n", MATRI[i-1][M-1], i);
    }
    /* N-ésima ligne */
    i = N;
    printf ("%-3d|", i);
    for (j = 0; j < M; j++)
    {
        printf ("%3c", MATRI[i-1][j]);
    }
    printf ("%1c |  %d\n", MATRI[i-1][j], i);
    /* tiret au dessous du tableau */
    i = 1;
    printf ("   +");
    for (i = 1; i <= M; i++)
    {
        printf ("---");
    }
    i = M + 1;
    printf ("-+\n");
    /* derniere ligne avec les nb de la partie inferieur */
    i = 1;
    printf ("      %d", i);
    for (i = 2; i < M; i++)
    {
        printf ("%3d", i);
    }
    i = M;
    printf ("%3d\n", i);
}


/* NxMcases */
char** initMatrixChar(int N, int M){
 
    char** tab = (char**) malloc(sizeof(char*)*N);
 
    for(int i=0; i<N; i++){
 
        tab[i] = (char*) malloc(sizeof(char)*M);
 
        for(int j=0; j<M; j++){
            if (nbAleatoireUnouDeux() == 0){
                tab[i][j]='o'; /* assignation . pour le tableau de caractères */
            }else{
                tab[i][j]=' '; /* assignation space pour le tableau de caractères */
            }
        }
    }
 
   return tab; 
}

int main(int argc, char **argv) {
    int N, M, K;
    if (argc >= 3){
        N = atoi (argv[1]);                 /* nb de lignes */
        M = atoi (argv[2]);                 /* nb de colonnes */
        K = atoi (argv[3]);                 /* nb de interactions */

    }else{
        printf("Il faut au moins 3 arguments pour designer le nb de ligner et de colonnes.");
        return 0;
    }
    
    char **MATRICE = initMatrixChar(N,M);
    char **nouvelleMatrice = initMatrixChar(N,M);

    for (int i = 0; i < K; i++){
        affichage(MATRICE, N, M);
        printf ("\n\n");
        attribuitionNouvelleMatrice(MATRICE, nouvelleMatrice, N, M);
        copierMatrice(nouvelleMatrice,MATRICE, N, M); /*matrice va recevoir la nouvelle matrice que c'est la nouvelle composition */
        usleep(1000000);
    }
    liberationMemoireChar(MATRICE,N);
    liberationMemoireChar(nouvelleMatrice,N);
    return 0;

}
