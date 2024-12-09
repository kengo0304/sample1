#include <stdio.h>
#include <stdlib.h>
#include "hand.h"

#define TWENTYONE 21

void hand_add(hand_t *p) {
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
