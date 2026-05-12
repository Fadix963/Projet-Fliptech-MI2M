#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"

#define MAX_PLAYERS 10  // Nombre maximum de joueurs
#define MAX_NAME 50     // Longueur maximale du pseudo
#define MAX_CARDS 7     // Maximum de cartes différentes en main

// Structure d'un joueur
typedef struct {
    char name[MAX_NAME];    // Pseudo du joueur
    Card hand[MAX_CARDS];   // Cartes en main (max 7 différentes)
    int handSize;           // Nombre de cartes en main
    int score;              // Score total de la partie
    int roundScore;         // Score de la manche en cours
    int hasBonus_x2;        // 1 si le joueur a la carte x2
    int bonusPoints;        // Points bonus accumulés (+2, +4, etc.)
    int isEliminated;       // 1 si le joueur a perdu la manche (doublon)
    int hasStopped;         // 1 si le joueur a décidé de s'arrêter
} Player;

// Fonctions de gestion des joueurs
void initPlayer(Player *player, char *name);  // Initialise un joueur
void resetPlayerRound(Player *player);        // Réinitialise pour une nouvelle manche
int hasCard(Player *player, Card card);       // Vérifie si le joueur a déjà la carte
void addCard(Player *player, Card card);      // Ajoute une carte en main
int calculateRoundScore(Player *player);      // Calcule le score de la manche
void printPlayerHand(Player *player);         // Affiche la main du joueur

#endif
