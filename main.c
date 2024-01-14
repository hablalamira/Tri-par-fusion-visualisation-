#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include <unistd.h>


int *arr;
int taille;

// Fonction pour fusionner deux sous-tableaux de arr[]
void fusion(int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Création de sous-tableaux temporaires
    int L[n1], R[n2];

    // Copie des données dans les sous-tableaux temporaires L[] et R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Fusion des sous-tableaux temporaires dans arr[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
        // Mettre à jour la visualisation après chaque étape

        Render();
        //délai entre chaque étape
        usleep(2000000);
    }

    // Copie des éléments restants de L[], s'il y en a
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;


        Render();
        usleep(2000000);
    }

    // Copie des éléments restants de R[], s'il y en a
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;


        Render();
        usleep(2000000);
    }
}

// Fonction principale qui trie arr[l..r] en utilisant le tri par fusion
void triFusion(int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        triFusion(l, m);
        triFusion(m + 1, r);
        fusion(l, m, r);
    }
}

// Fonction de rendu Raylib
void Render() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Dessiner des barres pour chaque élément du tableau
    for (int i = 0; i < taille; i++) {
      //  Générer une couleur aléatoire pour chaque rectangle
        Color rectangleColor = (Color){GetRandomValue(0, 250), GetRandomValue(0, 250), GetRandomValue(0, 250), 250};

        DrawRectangle(i * (GetScreenWidth() / taille), GetScreenHeight() - (arr[i] * 40), GetScreenWidth() / taille, (arr[i] * 40), rectangleColor);

        // Dessiner les valeurs de chaque cases au-dessus du rectangle approprié
        DrawText(TextFormat("%d", arr[i]), i * (GetScreenWidth() / taille) + 40, GetScreenHeight() - (arr[i] * 40) - 40, 40, BLACK);
    }

    EndDrawing();
}

// Fonction pour afficher un tableau
void afficherTableau(int arr[], int taille) {
    int i;

    for (i = 0; i < taille; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    // Initialisation de Raylib
    InitWindow(800, 600, "Tri Fusion Animation");

    printf("Donnez la taille du tableau : ");
    scanf("%d", &taille);

    arr = (int *)malloc(taille * sizeof(int));

    for (int i = 0; i < taille; i++) {
        printf("Élément %d : ", i + 1);
        scanf("%d", &arr[i]);
    }

    printf("Tableau original :\n");
    afficherTableau(arr, taille);


    triFusion(0, taille - 1);

    // Boucle principale
    while (!WindowShouldClose()) {
        // Rendu pour afficher le tableau trié
        Render();
    }

    CloseWindow();
    free(arr);

    return 0;
}
