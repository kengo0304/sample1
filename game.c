#include <stdio.h>
#include "hand.h"

extern int ncoin; // 外部変数の宣言

void play_a_game(void) {
    hand_t hand_player = {0, 0};
    hand_t hand_dealer = {0, 0};
    char c;

    hand_add(&hand_dealer);
    hand_add(&hand_player);
    hand_add(&hand_player);

    while (hand_player.score < TWENTYONE) {
        printf("Player: %d(%s), Dealer: %d, H/S? > ",
               hand_player.score,
               hand_player.is_soft ? "soft" : "hard",
               hand_dealer.score);
        while (scanf(" %c%*[^\n]%*c", &c) != 1);
        if (c == 'H') {
            hand_add(&hand_player);
            if (hand_player.score > TWENTYONE) {
                printf("Player: %d(%s), Dealer: %d, LOSE, -1\n",
                       hand_player.score,
                       hand_player.is_soft ? "soft" : "hard",
                       hand_dealer.score);
                ncoin--;
                return;
            }
        } else if (c == 'S') {
            break;
        } else {
            printf("Invalid input. Please enter 'H' or 'S'.\n");
        }
    }

    do hand_add(&hand_dealer);
    while (hand_dealer.score < 17);

    printf("Player: %d(%s), Dealer: %d, ",
           hand_player.score,
           hand_player.is_soft ? "soft" : "hard",
           hand_dealer.score);

    if (TWENTYONE < hand_dealer.score) {
        printf("WIN, +1\n");
        ncoin++;
    } else if (hand_player.score < hand_dealer.score) {
        printf("LOSE, -1\n");
        ncoin--;
    } else if (hand_player.score == hand_dealer.score) {
        printf("TIE, 0\n");
    } else {
        printf("WIN, +1\n");
        ncoin++;
    }
}
