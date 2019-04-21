//Jonathan Pham
//CS4280 P2
//04/21/19

#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include "node.h"

node * parser(FILE *);
node * Program();
node * Block();
node * Vars();
node * Expr();
node * A();
node * N();
node * M();
node * R();
node * Stats();
node * MStat();
node * Stat();
node * In();
node * Out();
node * If();
node * Loop();
node * Assign();
node * RO();
void error();
void error2();

#endif

