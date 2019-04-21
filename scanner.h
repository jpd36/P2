//Jonathan Pham
//CS4280 P2
//04/21/19

#ifndef SCANNER_H
#define SCANNER_H
#include <stdio.h>
#include "token.h"
#include "character.h"

void setLookaheadChar(FILE *);
token scanner(FILE *);
token fsaDriver(FILE *);
character filter(FILE *);
int getTableColNum(char);
void printToken(token t);

#endif
