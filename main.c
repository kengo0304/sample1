#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

int ncoin = 0; // グローバル変数

int main() {
    srand((unsigned int)time(NULL)); // SFMTの代わりにsrandでシードを設定
    char play_again;

    do {
        printf("\n--- New Game ---\n");
        play_a_game();
        printf("Player's chips: %d\n", ncoin);

        printf("Play another game? (Y/N) > ");
        while (scanf(" %c%*[^\n]%*c", &play_again) != 1 || (play_again != 'Y' && play_again != 'N' && play_again != 'y' && play_again != 'n')) {
            printf("Invalid input. Please enter 'Y' or 'N'.\n");
        }

    } while (play_again == 'Y' || play_again == 'y');

    printf("Final chips: %d\n", ncoin);
    return 0;
}
