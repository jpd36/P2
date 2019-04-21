//Jonathan Pham
//CS4280 P2
//04/21/19

#ifndef CHARACTER_H
#define CHARACTER_H

typedef enum {
    LOWER, UPPER, INT, WS, EQ, LESS, GREATER, COL, PLUS, MINUS, MULT, DIV, MOD, DOT, LPAREN,
    RPAREN, COMMA, LBRACE, RBRACE, SEMICOL, LBRACK, RBRACK, ENDOFFILE, COMMENT
} characterType;

typedef struct {
    char value;
    int tableColNum;
    int lineNum;
} character;

#endif


