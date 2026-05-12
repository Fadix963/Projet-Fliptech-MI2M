#ifndef DISPLAY_H
#define DISPLAY_H

#include "game.h"

// Codes couleurs pour le terminal
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

// Fonctions d'affichage
void clearScreen();                                   // Efface l'écran
void displayTitle();                                  // Affiche le titre du jeu
void displayGameState(Game *game, int currentPlayer); // Affiche l'état du jeu
void displayScores(Game *game);                       // Affiche les scores de tous les joueurs
void displayWinner(Game *game);                       // Affiche le vainqueur

#endif
