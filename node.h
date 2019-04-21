//Jonathan Pham
//CS4280 P2
//04/21/19

#ifndef NODE_H
#define NODE_H
#include "token.h"

typedef enum {
    PROGRAMnd, BLOCKnd, VARSnd, EXPRnd, And, Nnd, Mnd, Rnd, STATSnd, MSTATnd, STATnd,
 INnd, OUTnd, IFnd, LOOPnd, ASSIGNnd, ROnd
} nodeType;

typedef struct node {
    nodeType label;
    token token1;
    token token2;
    struct node *child1;
    struct node *child2;
    struct node *child3;
    struct node *child4;
} node;

#endif
