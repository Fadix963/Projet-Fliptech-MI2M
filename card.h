#ifndef CARD_H
#define CARD_H

// Types de cartes
typedef enum {
    NUMBER, // Carte numéro (0 à 12)
    BONUS   // Carte bonus (+2, +4, +6, +8, +10, x2)
} CardType;

// Structure d'une carte
typedef struct {
    CardType type;
    int value;  // Valeur de la carte (0 à 12 pour les numéros)
    int bonus;  // Valeur du bonus (-2 pour x2, sinon +2/+4/+6/+8/+10)
} Card;

// Structure de la pioche
typedef struct {
    Card cards[85]; // Les 85 cartes du jeu
    int top;        // Index du sommet de la pioche
} Deck;

// Fonctions de gestion de la pioche
void initDeck(Deck *deck);      // Initialise la pioche avec les 85 cartes
void shuffleDeck(Deck *deck);   // Mélange la pioche
Card drawCard(Deck *deck);      // Pioche une carte
int isDeckEmpty(Deck *deck);    // Vérifie si la pioche est vide
void printCard(Card card);      // Affiche une carte

#endif
