#include <stdio.h>
//fonction de resultats
void AfficherResutat(float TP[][10],int NbrVar,int m,int n){
    int i,j,emplacement;
    float Z;
    Z=TP[0][n-1];
    printf(" \n                            vos resultats optimales :\n");
    printf("\n Z=%.1f\n",Z);
for(j=1;j<NbrVar+1;j++){
    for(i=1;i<m;i++){
       if(TP[i][j]==1){
        emplacement=i;
       }

    }
    printf("x%d=%f\n",j,TP[j][n-1]);
}
}
//Fonction de gauss
void gauss(float TP[][10], int m, int n, int pivotLigne, int pivotColonne) {
     // Etape1: Lp=Lp/pivot
    float pivotElement = TP[pivotLigne][pivotColonne];
    for (int j = 0; j < n; j++) {
        TP[pivotLigne][j] /= pivotElement;
    }

    // Etape2: Lx=Lx-Va.Lp
    for (int i = 0; i < m; i++) {
        if (i != pivotLigne) {
            float Va = TP[i][pivotColonne];
            for (int j = 0; j < n; j++) {
                TP[i][j] -= Va * TP[pivotLigne][j];
            }
        }
    }
}
//Colonne pivot
int trouverColonnePivot(float TP[][10], int m, int n) {
    int colonnePivot = -1;
    float plusNegatif = 0;
    //Comparer tous les elements a plusNegatif
    for (int j = 1; j < n - 1; j++) {
        if (TP[0][j] < plusNegatif) {
            plusNegatif = TP[0][j];
            colonnePivot = j;
        }
    }
    return colonnePivot;
}
//ligne pivot
int trouverLignePivot(float TP[][10], int colonnePivot, int m, int n) {
    int lignePivot = -1;
    float rapportMin = -1;

    for (int i = 1; i < m; i++) {
        if (TP[i][colonnePivot] > 0) {
       //diviser les cst avec lintersection avec colonne pivot
      //et on compare avec le minimum
            float rapport = TP[i][n - 1] / TP[i][colonnePivot];
            if ((rapportMin == -1 || rapport < rapportMin) && TP[i][colonnePivot] != 0) {
                rapportMin = rapport;
                lignePivot = i;
            }
        }
    }
    return lignePivot;
}
//Fonction Vb
/*void VariableBase(float TP[][10],int NbrCont,int n ,int m){
   int un=0,emplacement,c=1,i,j,zero=0;
    for(j=1;j<n-1;j++){
        for(i=1;i<m;i++){//calculer si il ya un 1 et des 0
            if(TP[i][j]==1){
                    un++;
                    emplacement=i;
            }
            if(TP[i][j]==0){
                    zero++;
            }}
        if(un+zero==NbrCont && un=1){
            printf("VB%d=TP[emplacement][n-1]",c);
            c++;
        }

   } }*/

//Fonction VHb
/*void VariableHorsBase(float TP[][10],int NbrCont,int n ,int m){
   int un=0,emplacement,c=1,i,j,zero=0;
    for(j=1;j<n-1;j++){//voir si il contient un 1 et des zeros
        for(i=1;i<m;i++){
            if(TP[i][j]==1){
                    un++;
                    emplacement=i;
            }
            if(TP[i][j]==0){
                    zero++;
            }

        }
        if(un+zero!=NbrCont ){
            printf("VHB%d=0",c);
            c++;
        }

    }
}*/

//creer un tableau dont le diagonal est 1 et les autres0
//pour remplir notre premier tableau d itteration (VB)
void creerDiagonal(float TD[][10], int NbrCont) {
    for (int i = 0; i < NbrCont; i++) {
        for (int j = 0; j < NbrCont; j++) {
            if (i == j) {
                TD[i][j] = 1;
            } else {
                TD[i][j] = 0;
            }
        }
    }
}
//Affichage des tableaux d itterations
void AfficherTableau(float T[10][10], int NbrVar, int NbrCont, int m, int n) {
    int i, j;
    printf("Z\t ");
    for (i = 0; i < NbrVar; i++) {
        printf("x%d      ", i + 1);
    }
    for (i = 0; i < NbrCont; i++) {
        printf("e%d     ", i + 1);
    }
    printf("|");
    printf("=\n");
    for (i = 0; i < n; i++) {
        printf("%.1f\t", T[0][i]);
    }
    printf("\n");
    for (i = 0; i < n; i++) {
        printf("---------");
    }
    printf("\n");
    for (i = 1; i < m; i++) {
        for (j = 0; j < n - 1; j++) {
            printf("%.1f\t", T[i][j]);
        }
        printf("|%.1f\n", T[i][n - 1]);
    }
}
//creer un tableau dont on stock les coefficients du fctn Objectif
void CoeffObjectif(float TO[10], int NbrVar) {
    int i;
    //input des coefficients
    printf("                       Objectif:\n\n");
    printf("Entrer les coefficients :\n\n");
    for (i = 0; i < NbrVar; i++) {
        printf("Coefficient de la variable %d: ", i + 1);
        scanf("%f", &TO[i]);
    }
     //ecrire l equation complete
    printf("Z = ");
    for (i = 0; i < NbrVar; i++) {
        printf("%.1fx%d", TO[i], i + 1);
        if (i < NbrVar - 1) {
            printf(" + ");
        }
    }
    printf("\n");
}
//creer un tableau de coefficients des contraintes
void Contraintes(float TC[][10], int NbrVar, int NbrCont) {
    int i, j;
    //input coefficients
    printf("-----------------------------------------------------------\n");
    printf("                       Contraintes:\n\n");
    for (i = 0; i < NbrCont; i++) {
        printf("Contrainte %d: \n", i + 1);
        for (j = 0; j < NbrVar; j++) {
            printf("Coefficient de x%d : ", j + 1);
            scanf("%f", &TC[i][j]);
        }
         //input resultat
        printf("Entrer la constante de la contrainte %d : ", i + 1);
        scanf("%f", &TC[i][NbrVar]);
    }
     //affichage des contraintes
    printf("\nContraintes:\n");
    for (i = 0; i < NbrCont; i++) {
        printf("\nContrainte %d:\n", i + 1);
        for (j = 0; j < NbrVar; j++) {
            printf("%.1fx%d", TC[i][j], j + 1);
            if (j < NbrVar - 1) {
                printf(" + ");
            }
        }
        printf(" <= %.1f\n", TC[i][NbrVar]);
    }
}
//creer le premier tableau d itteration
void PremierTaleau(float TP[][10], float TO[10], float TC[][10], float TD[][10], int NbrVar, int NbrCont, int m, int n) {
    int i, j, c, d;
    //Premier ligne (ligne Objectif):
    TP[0][0] = 1;
    for (i = 1; i < NbrVar + 1; i++) {
        TP[0][i] = -TO[i - 1];
    }
    for (i = NbrVar + 1; i < n; i++) {
        TP[0][i] = 0;
    }
    //les autres lignes(lignes contraintes):
    for (i = 1, d = 0; i < m, d < NbrCont; i++, d++) {
        TP[i][0] = 0;
        for (j = 1, c = 0; j < NbrVar + 1, c < NbrVar; j++, c++) {
            TP[i][j] = TC[d][c];
        }
        for (j = NbrVar + 1, c = 0; j < NbrVar + 1 + NbrCont, c < NbrCont; j++, c++) {
            TP[i][j] = TD[d][c];
        }
        TP[i][n - 1] = TC[d][NbrVar];
    }
}
//affichage du processus simplexe en utilisant les fctns precedent
void simplexe(float TP[][10], float TO[10], float TC[][10], float TD[][10], int NbrVar, int NbrCont, int m, int n) {
    int iteration = 1;
    while (1) {
        printf("\nIteration %d:\n", iteration);
        AfficherTableau(TP, NbrVar, NbrCont, m, n);
        int colonnePivot = trouverColonnePivot(TP, m, n);
        if (colonnePivot == -1) {
                AfficherResutat(TP,NbrVar,m,n);
            printf("\nLe simplexe est termine.\n");
            break;
        }
        int lignePivot = trouverLignePivot(TP, colonnePivot, m, n);
        if (lignePivot == -1) {
            printf("\nPas de solution optimale (probleme non borne).\n");
            break;
        }
        printf("Ve: %d\n", colonnePivot);
        printf("Vs: %d\n", lignePivot);
        //afficherVariablesBase(TP, NbrVar, NbrCont);
        //afficherVariablesHorsBase(TP, m, n, NbrVar);
        gauss(TP, m, n, lignePivot, colonnePivot);
        iteration++;
    }
}

int main() {
    int NbrVar, NbrCont;
     printf("                             *****Simplexe******\n\n");
    //limiter la saisie des utilisateurs
    do {
        printf("Combien de variables ? : ");
        if (scanf("%d", &NbrVar) != 1) {
            printf("Veuillez entrer un nombre entier.\n");
            scanf("%*s"); // tampon effacee
        }
    } while (NbrVar <= 0);
    do {
        printf("Combien de contraintes ? : ");
        if (scanf("%d", &NbrCont) != 1) {
            printf("Veuillez entrer un nombre entier.\n");
            scanf("%*s"); // tampon effacee
        }
    } while (NbrCont <= 0);
printf("\n");
    //des tableaux statiques dont on stock nos inputs en fcts
    float TO[10]; // tableau objectif
    float TC[10][10];  //tableau contraintes
    float TP[10][10];  //tableau premier
    float TD[10][10];  //tableau diagonal
    //les dimensions des tables d itteration
    int m = NbrCont + 1;// nbr des contraintes + Objectif
    int n = NbrCont + NbrVar + 2; // Objectif+ Nbr Contraintes+Nbr Vars+Cstn
    //utilisation des fonctions:
    creerDiagonal(TD, NbrCont);
    CoeffObjectif(TO, NbrVar);
    Contraintes(TC, NbrVar, NbrCont);
    PremierTaleau(TP, TO, TC, TD, NbrVar, NbrCont, m, n);
    printf("----------------------------------------------------------\n");
    simplexe(TP, TO, TC, TD, NbrVar, NbrCont, m, n);

    return 0;
}
