#ifndef GAME_H
#define GAME_H

#include "card.h"
#include "player.h"

#define MAX_SCORE 200    // Score maximum pour gagner la partie
#define BONUS_7_CARDS 15 // Bonus pour avoir 7 cartes différentes

// Structure de la partie
typedef struct {
    Player players[MAX_PLAYERS]; // Tableau des joueurs
    int nbPlayers;               // Nombre de joueurs
    Deck deck;                   // La pioche
    int currentRound;            // Numéro de la manche actuelle
    int gameOver;                // 1 si la partie est terminée
} Game;

// Fonctions de gestion de la partie
void initGame(Game *game);                  // Initialise la partie
void setupPlayers(Game *game);              // Demande les pseudos des joueurs
void playRound(Game *game);                 // Joue une manche complète
void playTurn(Game *game, int playerIndex); // Joue le tour d'un joueur
int checkRoundEnd(Game *game);              // Vérifie si la manche est terminée
void endRound(Game *game);                  // Calcule et affiche les scores de fin de manche
int checkGameOver(Game *game);              // Vérifie si la partie est terminée
void endGame(Game *game);                   // Affiche le vainqueur

#endif
