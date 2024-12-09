#ifndef HAND_H
#define HAND_H

typedef struct { int score, is_soft; } hand_t;

void hand_add(hand_t *p);

#endif