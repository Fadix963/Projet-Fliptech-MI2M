#include <stdio.h>
#include <string.h>
#include "player.h"

// Initialise un joueur avec son pseudo
void initPlayer(Player *player, char *name) {
    strncpy(player->name, name, MAX_NAME - 1);
    player->name[MAX_NAME - 1] = '\0';
    player->score = 0;
    resetPlayerRound(player);
}

// Réinitialise les données du joueur pour une nouvelle manche
void resetPlayerRound(Player *player) {
    player->handSize = 0;
    player->roundScore = 0;
    player->hasBonus_x2 = 0;
    player->bonusPoints = 0;
    player->isEliminated = 0;
    player->hasStopped = 0;
}

// Vérifie si le joueur possède déjà une carte numéro de cette valeur
int hasCard(Player *player, Card card) {
    if (card.type == BONUS) return 0; // Les bonus ne créent pas de doublon
    for (int i = 0; i < player->handSize; i++) {
        if (player->hand[i].type == NUMBER &&
            player->hand[i].value == card.value) {
            return 1; // Doublon trouvé
        }
    }
    return 0;
}

// Ajoute une carte dans la main du joueur
void addCard(Player *player, Card card) {
    if (player->handSize < MAX_CARDS) {
        player->hand[player->handSize] = card;
        player->handSize++;
    }

    // Gestion des cartes bonus
    if (card.type == BONUS) {
        if (card.bonus == -2)
            player->hasBonus_x2 = 1; // Carte x2
        else
            player->bonusPoints += card.bonus; // Carte +2/+4/+6/+8/+10
    }
}

// Calcule le score du joueur pour la manche
int calculateRoundScore(Player *player) {
    if (player->isEliminated) return 0; // Doublon = 0 points

    int total = 0;

    // Additionne les valeurs des cartes numéros
    for (int i = 0; i < player->handSize; i++) {
        if (player->hand[i].type == NUMBER) {
            total += player->hand[i].value;
        }
    }

    // Applique les bonus additifs
    total += player->bonusPoints;

    // Applique le x2 en dernier
    if (player->hasBonus_x2) total *= 2;

    player->roundScore = total;
    return total;
}

// Affiche les cartes en main du joueur
void printPlayerHand(Player *player) {
    printf("Main de %s : ", player->name);
    for (int i = 0; i < player->handSize; i++) {
        printCard(player->hand[i]);
        printf(" ");
    }
    printf("\n");
}
