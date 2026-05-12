#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "card.h"

// Initialise la pioche avec les 85 cartes
void initDeck(Deck *deck) {
    int index = 0;

    // Cartes numéros : la valeur i apparaît i fois (sauf 0 et 1 -> 1 fois)
    for (int i = 0; i <= 12; i++) {
        int count = (i == 0 || i == 1) ? 1 : i;
        for (int j = 0; j < count; j++) {
            deck->cards[index].type = NUMBER;
            deck->cards[index].value = i;
            deck->cards[index].bonus = 0;
            index++;
        }
    }

    // Cartes bonus : +2, +4, +6, +8, +10, x2
    int bonusValues[] = {2, 4, 6, 8, 10, -2}; // -2 représente x2
    for (int i = 0; i < 6; i++) {
        deck->cards[index].type = BONUS;
        deck->cards[index].value = 0;
        deck->cards[index].bonus = bonusValues[i];
        index++;
    }

    deck->top = 84; // 85 cartes, indices 0 à 84
}

// Mélange la pioche avec l'algorithme Fisher-Yates
void shuffleDeck(Deck *deck) {
    srand(time(NULL));
    for (int i = 84; i > 0; i--) {
        int j = rand() % (i + 1);
        Card temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp;
    }
}

// Pioche une carte au sommet de la pioche
Card drawCard(Deck *deck) {
    return deck->cards[deck->top--];
}

// Vérifie si la pioche est vide
int isDeckEmpty(Deck *deck) {
    return deck->top < 0;
}

// Affiche une carte
void printCard(Card card) {
    if (card.type == NUMBER) {
        printf("[%2d]", card.value);
    } else {
        if (card.bonus == -2)
            printf("[x2]");
        else
            printf("[+%d]", card.bonus);
    }
}
