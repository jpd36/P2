//Jonathan Pham
//CS4280 P2
//04/21/19

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "node.h"
#include "scanner.h"
#include "testTree.h"
#include "parser.h"

static FILE *inputFilePtr;
static token tk;
extern char *tokenNames[];

node * parser(FILE *inputFile) {
    inputFilePtr = inputFile;
    node *root;

    setLookaheadChar(inputFilePtr);

    tk = scanner(inputFilePtr);
    root = Program();

    if (tk.type != EOFtk) {
        error2();
    }
    printf("Parser Success\n");    // TEST
    return root;
}

node * Program() {
    node *node = createNode(PROGRAMnd);

        node->child1 = Vars();
        node->child2 = Block();
        return node;
}

node * Block() {
 
   if (tk.type == BEGINtk) {
        node *node = createNode(BLOCKnd);
        tk = scanner(inputFilePtr);

        node->child1 = Vars();
        node->child2 = Stats();

        if (tk.type == ENDtk) {
            tk = scanner(inputFilePtr);
            return node;
        }
        error();
    }
    error();
    return NULL;
}

node * Vars() {
    node *node = createNode(VARSnd);
    
        if (tk.type == INTtk) {
            tk = scanner(inputFilePtr);

            if (tk.type == IDtk) {
		node->token1 = tk;
                tk = scanner(inputFilePtr);

                if (tk.type == INTEGERtk) {
                    node->token2 = tk;
                    tk = scanner(inputFilePtr);

                    node->child1 = Vars();
                    return node;
                }
                error();
            }
            error();
    }
    return node;
}




node * Expr() {
    node *node = createNode(EXPRnd);

    node->child1 = A();

    if (tk.type == PLUStk || tk.type == MINUStk) {
        node->token1 = tk;
        tk = scanner(inputFilePtr);

        node->child2 = Expr();
    }
    
    return node;
}

node * A() {
    node *node = createNode(And);

    node->child1 = N();

    if (tk.type == MULTtk) {
        node->token1 = tk;
        tk = scanner(inputFilePtr);

        node->child2 = A();
    }
    return node;
}

node * N() {
    node *node = createNode(Nnd);

    node->child1 = M();

    if (tk.type == DIVtk) {
        node->token1 = tk;
        tk = scanner(inputFilePtr);

        node->child2 = N();
    }
        return node;
}


node * M() {
    node *node = createNode(Mnd);

    if (tk.type == MINUStk) {
        node->token1 = tk;
        tk = scanner(inputFilePtr);

        node->child1 = M();
        return node;
    }
    else {
        node->child1 = R();
        return node;
    }
}

node * R() {
    node *node = createNode(Rnd);

    if (tk.type == LBRACKtk) {
        tk = scanner(inputFilePtr);

        node->child1 = Expr();

        if (tk.type == RBRACKtk) {
            tk = scanner(inputFilePtr);
            return node;
        }
        error();
    }

    else if (tk.type == IDtk) {
        node->token1 = tk;
        tk = scanner(inputFilePtr);
        return node;
    }
    else if (tk.type == INTEGERtk) {
        node->token1 = tk;
        tk = scanner(inputFilePtr);
        return node;
    }
    error();
    return NULL;
}

node * Stats() {
    node *node = createNode(STATSnd);
    node->child1 = Stat();

    if (tk.type == COLtk) {
        tk = scanner(inputFilePtr);
    	node->child2 = MStat();
 	return node;
    }
    error();
    return NULL;
}


node * MStat() {
    node *node = createNode(MSTATnd);

    if (tk.type == READtk || tk.type == OUTPUTtk || tk.type == BEGINtk || tk.type == IFFtk || tk.type == LOOPtk || tk.type == IDtk) {    // do not consume token
           
           node->child1 = Stat();
           	if (tk.type == COLtk) {
               		tk = scanner(inputFilePtr);
	      	        node->child2 = MStat();
	      	        return node;
           	}       
        error();
    return NULL;
    }
    return node;
}


node * Stat() {
    node *node = createNode(STATnd);

    if (tk.type == READtk) {    // do not consume token
        node->child1 = In();
        return node;
    }
    else if (tk.type == OUTPUTtk) {    // do not consume token
        node->child1 = Out();
        return node;
    }
    else if (tk.type == BEGINtk) {    // do not consume token
        node->child1 = Block();
        return node;
    }
    else if (tk.type == IFFtk) {    // do not consume token
        node->child1 = If();
        return node;
    }
    else if (tk.type == LOOPtk) {    // do not consume token
        node->child1 = Loop();
        return node;
    }
    else if (tk.type == IDtk) {    // do not consume token
        node->child1 = Assign();
        return node;
    }
    error();
    return NULL;
}


node * In() {
    node *node = createNode(INnd);

    if (tk.type == READtk) {
        tk = scanner(inputFilePtr);

            if (tk.type == LBRACKtk) {
                tk = scanner(inputFilePtr);

		if (tk.type == IDtk) {
		        node->token1=tk;
                	tk = scanner(inputFilePtr);

                    if (tk.type == RBRACKtk) {
                        tk = scanner(inputFilePtr);
                        return node;
                    }
                    error();                
                }
                error();        
            }
            error();
    }
    error();
    return NULL;
}


node * Out() {
    node *node = createNode(OUTnd);

    if (tk.type == OUTPUTtk) {
        tk = scanner(inputFilePtr);

        if (tk.type == LBRACKtk) {
            tk = scanner(inputFilePtr);

            node->child1 = Expr();

            if (tk.type == RBRACKtk) {
                tk = scanner(inputFilePtr);
                return node;               
            }
            error();
        }
        error();
    }
    error();
    return NULL;
}

node * If() {
    node *node = createNode(IFnd);

    if (tk.type == IFFtk) {
        tk = scanner(inputFilePtr);

        if (tk.type == LBRACKtk) {
            tk = scanner(inputFilePtr);

            node->child1 = Expr();
            node->child2 = RO();
            node->child3 = Expr();

            if (tk.type == RBRACKtk) {
                tk = scanner(inputFilePtr);

                node->child4 = Stat();
                return node;
            }
            error();
        }
        error();
    }
    error();
    return NULL;
}

node * Loop() {
    node *node = createNode(LOOPnd);

    if (tk.type == LOOPtk) {
        tk = scanner(inputFilePtr);

        if (tk.type == LBRACKtk) {
            tk = scanner(inputFilePtr);

            node->child1 = Expr();
            node->child2 = RO();
            node->child3 = Expr();

            if (tk.type == RBRACKtk) {
                tk = scanner(inputFilePtr);

                node->child4 = Stat();
                return node;
            }
            error();
        }
        error();
    }
    error();
    return NULL;
}

node * Assign() {
    node *node = createNode(ASSIGNnd);

    if (tk.type == IDtk) {
        node->token1 = tk;
        tk = scanner(inputFilePtr);

        if (tk.type == EQtk) {
            tk = scanner(inputFilePtr);

            node->child1 = Expr();
        }
        error();
    }
    error();
    return NULL;
}


node * RO() {
    node *node = createNode(ROnd);

    if (tk.type == LESStk || tk.type == GREATERtk ||  tk.type == EQtk) {
        node->token1 = tk;
        tk = scanner(inputFilePtr);

        if (tk.type == LESStk) {
            node->token2 = tk;
            tk = scanner(inputFilePtr);
            return node;
        }
	else if (tk.type == GREATERtk) {
            node->token2 = tk;
            tk = scanner(inputFilePtr);
            return node;
        }
	else if (tk.type == EQtk) {
            node->token2 = tk;
            tk = scanner(inputFilePtr);
            return node;
        }
        return node;
    }
    error();
    return NULL;
}

void error() {
    printf("Parser Error: Unexpected token '%s' received (line %d)\n", tokenNames[tk.type], tk.lineNum);
    exit(tk.type);
}

void error2() {
    printf("Parser Error: Extra token '%s' received after end of program (line %d)\n", tokenNames[tk.type], tk.lineNum);
    exit(tk.type);
}

