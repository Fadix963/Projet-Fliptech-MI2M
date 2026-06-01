#include <stdio.h>
#include "game.h"
#include "display.h"
#include "file.h"
 
int main() {
    Game game;
    displayTitle();
    initGame(&game);
    setupPlayers(&game);
    while (!checkGameOver(&game)) {
        playRound(&game);
        displayScores(&game);
    }
    endGame(&game);
    saveScores(&game);
    return 0;
}
