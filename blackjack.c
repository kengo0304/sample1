#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TWENTYONE 21

typedef struct { int score, is_soft; } hand_t;

int ncoin = 0;

static void hand_add(hand_t *p) {
    int score_new, card_new;

    card_new = rand() % 13 + 1; // 1から13の範囲の乱数生成
    if (10 < card_new) card_new = 10;
    if (card_new != 1) score_new = p->score + card_new;
    else if (p->is_soft) score_new = p->score + 1;
    else {
        p->is_soft = 1;
        score_new = p->score + 11;
    }
    if (TWENTYONE < score_new && p->is_soft) {
        p->is_soft = 0;
        score_new -= 10;
    }
    p->score = score_new;
}

static void play_a_game(void) {
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
