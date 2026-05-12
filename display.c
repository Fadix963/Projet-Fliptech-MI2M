#include <stdio.h>
#include "display.h"

// Efface l'écran du terminal
void clearScreen() {
    printf("\033[2J\033[H");
}

// Affiche le titre du jeu
void displayTitle() {
    clearScreen();
    printf(BOLD CYAN);
    printf("╔════════════════════════════════════╗\n");
    printf("║         FLIP TECH                  ║\n");
    printf("║     Jeu de cartes - preING1        ║\n");
    printf("╚════════════════════════════════════╝\n");
    printf(RESET);
}

// Affiche l'état complet du jeu pour le joueur actuel
void displayGameState(Game *game, int currentPlayer) {
    clearScreen();
    displayTitle();

    printf(YELLOW "\n=== MANCHE %d ===\n" RESET, game->currentRound);

    // Affiche les scores et statuts de tous les joueurs
    printf(BOLD "\n--- Scores et statuts ---\n" RESET);
    for (int i = 0; i < game->nbPlayers; i++) {
        Player *p = &game->players[i];

        // Indique le joueur actuel
        if (i == currentPlayer)
            printf(GREEN "> " RESET);
        else
            printf("  ");

        printf(BOLD "%s" RESET " | Score total : " CYAN "%d pts" RESET,
               p->name, p->score);

        // Affiche le statut du joueur
        if (p->isEliminated)
            printf(RED " [ELIMINE]" RESET);
        else if (p->hasStopped)
            printf(YELLOW " [ARRETE]" RESET);
        else
            printf(GREEN " [EN JEU]" RESET);

        // Affiche le nombre de cartes en main
        printf(" | Cartes : %d/7\n", p->handSize);
    }

    // Affiche la main du joueur actuel
    Player *current = &game->players[currentPlayer];
    printf(BOLD "\n--- Main de %s ---\n" RESET, current->name);
    if (current->handSize == 0) {
        printf("Aucune carte en main.\n");
    } else {
        for (int i = 0; i < current->handSize; i++) {
            printCard(current->hand[i]);
            printf(" ");
        }
        printf("\n");
    }

    // Affiche le score actuel de la manche
    printf(CYAN "\nScore actuel de la manche : %d pts\n" RESET,
           calculateRoundScore(current));

    // Affiche le nombre de cartes restantes dans la pioche
    printf(MAGENTA "Cartes restantes dans la pioche : %d\n" RESET,
           game->deck.top + 1);
}

// Affiche les scores de tous les joueurs
void displayScores(Game *game) {
    printf(BOLD "\n--- Scores de la partie ---\n" RESET);
    for (int i = 0; i < game->nbPlayers; i++) {
        printf(CYAN "%-15s" RESET " : " BOLD "%d pts\n" RESET,
               game->players[i].name, game->players[i].score);
    }
}

// Affiche le vainqueur de la partie
void displayWinner(Game *game) {
    int maxScore = -1;
    int winner = 0;
    for (int i = 0; i < game->nbPlayers; i++) {
        if (game->players[i].score > maxScore) {
            maxScore = game->players[i].score;
            winner = i;
        }
    }
    printf(BOLD YELLOW);
    printf("\n╔════════════════════════════════════╗\n");
    printf("║       VAINQUEUR                    ║\n");
    printf("║  %-34s║\n", game->players[winner].name);
    printf("║  Score final : %-20d║\n", maxScore);
    printf("╚════════════════════════════════════╝\n");
    printf(RESET);
}
