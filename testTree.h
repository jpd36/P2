//Jonathan Pham
//CS4280 P2
//04/21/19

#ifndef TESTTREE_H
#define TESTTREE_H
#include "node.h"

node * createNode(nodeType);
void traversePreorder(node *, int);
void visitNode(node *, int);
extern char *tokenNames[];

#endif

