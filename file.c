#include <stdio.h>
#include "file.h"

// Sauvegarde les scores finaux dans un fichier texte
void saveScores(Game *game) {
    FILE *file = fopen("scores.txt", "w");

    // Vérifie si le fichier s'est bien ouvert
    if (file == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier scores.txt\n");
        return;
    }

    // Écriture du titre dans le fichier
    fprintf(file, "=== SCORES FINAUX - FLIP TECH ===\n\n");

    // Écriture des scores de tous les joueurs
    for (int i = 0; i < game->nbPlayers; i++) {
        fprintf(file, "%s : %d points\n",
                game->players[i].name,
                game->players[i].score);
    }

    // Écriture du nombre de manches jouées
    fprintf(file, "\nNombre de manches jouees : %d\n", game->currentRound - 1);

    // Fermeture du fichier
    fclose(file);

    printf("\nScores sauvegardes dans le fichier scores.txt\n");
}
