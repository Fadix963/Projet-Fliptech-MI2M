#include <stdio.h>
#include <string.h>
#include "game.h"
#include "display.h"

// Initialise la partie
void initGame(Game *game) {
    game->nbPlayers = 0;
    game->currentRound = 1;
    game->gameOver = 0;
    initDeck(&game->deck);
    shuffleDeck(&game->deck);
}

// Demande le nombre de joueurs et leurs pseudos
void setupPlayers(Game *game) {
    int nb;
    printf("=== BIENVENUE DANS FLIPTECH ===\n");
    printf("Entrez le nombre de joueurs : ");

    while (scanf("%d", &nb) != 1 || nb < 2 || nb > MAX_PLAYERS) {
        // Vide le buffer en cas de saisie invalide
        while (getchar() != '\n');
        printf("Nombre invalide ! Entrez un nombre entre 2 et %d : ", MAX_PLAYERS);
    }
    // Vide le buffer après la saisie valide
    while (getchar() != '\n');
    game->nbPlayers = nb;

    // Saisie des pseudos
    char name[MAX_NAME];
    for (int i = 0; i < game->nbPlayers; i++) {
        printf("Pseudo du joueur %d : ", i + 1);
        scanf("%49s", name);
        while (getchar() != '\n');
        initPlayer(&game->players[i], name);
    }
}

// Joue une manche complète
void playRound(Game *game) {
    // Réinitialise les joueurs pour la nouvelle manche
    for (int i = 0; i < game->nbPlayers; i++) {
        resetPlayerRound(&game->players[i]);
    }



    printf("\n=== MANCHE %d ===\n", game->currentRound);

    int roundOver = 0;
    int winner7Cards = -1; // Index du joueur qui a obtenu 7 cartes différentes

    while (!roundOver) {
        for (int i = 0; i < game->nbPlayers && !roundOver; i++) {
            Player *p = &game->players[i];

            // Passe le tour si le joueur est éliminé ou s'est arrêté
            if (p->isEliminated || p->hasStopped) continue;

            // Joue le tour du joueur
            playTurn(game, i);

            // Vérifie si le joueur a 7 cartes différentes
            if (p->handSize == MAX_CARDS && !p->isEliminated) {
                winner7Cards = i;
                roundOver = 1;
                break;
            }

            // Vérifie si la pioche est vide
            if (isDeckEmpty(&game->deck)) {
                roundOver = 1;
                break;
            }

            // Vérifie si tous les joueurs ont terminé
            roundOver = checkRoundEnd(game);
        }
    }

    // Bonus de 15 points pour le joueur avec 7 cartes différentes
    if (winner7Cards != -1) {
        game->players[winner7Cards].roundScore += BONUS_7_CARDS;
        printf("\n%s a obtenu 7 cartes differentes et gagne %d points bonus !\n",
               game->players[winner7Cards].name, BONUS_7_CARDS);
    }
    
    // Vérifie si tous les joueurs restants sont éliminés
    int allEliminated = 1;
    for (int i = 0; i < game->nbPlayers; i++) 
    {
    	if (!game->players[i].isEliminated) 
    	{
        	allEliminated = 0;
        	break;
    	}
    }
if (allEliminated) {
    printf("\nTous les joueurs sont elimines ! Fin de la manche.\n");
    // Petite pause pour que le joueur puisse lire
    printf("Appuyez sur Entree pour continuer...\n");
    getchar();
}

    // Fin de manche
    endRound(game);
    game->currentRound++;
}

// Joue le tour d'un joueur
void playTurn(Game *game, int playerIndex) {
    Player *p = &game->players[playerIndex];
    int choice;

    displayGameState(game, playerIndex);

    printf("\n>>> Tour de %s <<<\n", p->name);
    printf("1. Piocher une carte\n");
    printf("2. S'arreter\n");
    printf("Votre choix : ");
    scanf("%d", &choice);
    while (getchar() != '\n');

    if (choice == 2) {
        p->hasStopped = 1;
        printf("%s decide de s'arreter.\n", p->name);
        return;
    }

    // Pioche une carte
    Card drawn = drawCard(&game->deck);
    printf("%s pioche : ", p->name);
    printCard(drawn);
    printf("\n");

    if (drawn.type == BONUS) {
        // Carte bonus : toujours ajoutée
        addCard(p, drawn);
        printf("Carte bonus obtenue !\n");
    } else {
        // Vérifie le doublon
        if (hasCard(p, drawn)) {
            printf("Doublon ! %s a tire un [ %d ] qu'il possede deja, il perd la manche.\n", p->name, drawn.value);
            p->isEliminated = 1;
        } else {
            addCard(p, drawn);
            printf("Carte ajoutee a la main.\n");
        }
    }
}

// Vérifie si tous les joueurs ont terminé la manche
int checkRoundEnd(Game *game) {
    for (int i = 0; i < game->nbPlayers; i++) {
        Player *p = &game->players[i];
        if (!p->isEliminated && !p->hasStopped) {
            return 0; // Il reste des joueurs actifs
        }
    }
    return 1; // Tous les joueurs ont terminé
}

// Calcule et affiche les scores de fin de manche
void endRound(Game *game) {
    printf("\n=== FIN DE LA MANCHE %d ===\n", game->currentRound);
    for (int i = 0; i < game->nbPlayers; i++) {
        Player *p = &game->players[i];
        int roundScore = calculateRoundScore(p);
        p->score += roundScore;
        printf("%s : +%d points (total : %d)\n", p->name, roundScore, p->score);
    }
}

// Vérifie si la partie est terminée
int checkGameOver(Game *game) {
    for (int i = 0; i < game->nbPlayers; i++) {
        if (game->players[i].score >= MAX_SCORE) {
            return 1;
        }
    }
    if (isDeckEmpty(&game->deck)) return 1;
    return 0;
}

// Affiche le vainqueur
void endGame(Game *game) {
    printf("\n=== FIN DE LA PARTIE ===\n");
    int maxScore = -1;
    int winner = 0;
    for (int i = 0; i < game->nbPlayers; i++) {
        printf("%s : %d points\n", game->players[i].name, game->players[i].score);
        if (game->players[i].score > maxScore) {
            maxScore = game->players[i].score;
            winner = i;
        }
    }
    printf("\n%s remporte la partie avec %d points !\n",
           game->players[winner].name, maxScore);
}
