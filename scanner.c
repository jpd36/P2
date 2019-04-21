//Jonathan Pham
//CS4280 P2
//04/21/19

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "character.h"
#include "token.h"
#include "testTree.h"
#include "scanner.h"
#define SIZE 9 // LENGTH + 1


typedef enum {
        ERROR = -1,
        s1 = 0, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, s16, s17, s18, s19, s20, s21,
        FINAL = 100
} state;

int fsaTable[21][23] = {

// a-z    A-Z    0-9     WS      =      <      >      :      +      -      *      /      %      .      (      )      ,      {      }      :      [      ]    EOF   //
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
{  ERROR,   s2,    s3,    s1,    s4,    s5,    s6,    s7,    s8,    s9,   s10,   s11,   s12,   s13,   s14,   s15,   s16,   s17,   s18,   s19,   s20,   s21, FINAL}, // s1
{s2,    s2,    s2, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL}, // s2
{FINAL, FINAL,    s3, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL}, // s3
{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL}, // s4
{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL}, // s5
{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL}, // s6
{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL}, // s7
{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL}, // s8
{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL}, // s9
{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL}, // s10
{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL}, // s11
{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL}, // s12
{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL}, // s13
{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL}, // s14
{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL}, // s15
{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL}, // s16
{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL}, // s17
{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL}, // s18
{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL}, // s19
{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL}, // s20
{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL}  // s21
};

char *keywords[] = {
                "Begin", "End", "Loop", "Void", "INT", "Return", "Read", "Output", "Program", "IFF", "Then", "Let"
};

const int NUM_KEYWORDS = 12;
const int LENGTH = 8; // Maximum length of ID token instance
int lineNum = 1;
character nextChar;



void setLookaheadChar(FILE *inputFile) {
        nextChar = filter(inputFile);
}

token scanner(FILE *inputFile) {
        return fsaDriver(inputFile);
}

token fsaDriver(FILE *inputFile) {
        state currentState = s1;
        state nextState;
        token newToken;
        char word[9] = "";

        while (currentState != FINAL) {
                nextState = fsaTable[currentState][nextChar.tableColNum];

                if (nextState == ERROR) {
                        printf("\nScanner Error: No token begins with '%c' (line %d)", nextChar.value, nextChar.lineNum);
                        exit(ERROR);
                }
                if (nextState == FINAL) {
newToken.type = currentState + NUM_KEYWORDS;
                        strcpy(newToken.instance, word);
                        newToken.lineNum = nextChar.lineNum;

if (currentState == s2) {
                                int i;
                                for (i = 0; i < NUM_KEYWORDS; i++) {
                                        if (strcmp(keywords[i], newToken.instance) == 0) {
                                                newToken.type = i;
                                        }
                                }
                        }
                        return newToken;
                }
                else {

if (nextChar.tableColNum != WS) {
                                word[strlen(word)] = nextChar.value;
                                word[strlen(word)+1] = '\0';
                        }

                        currentState = nextState;
                        nextChar = filter(inputFile);

if (strlen(word) == LENGTH) {
                                newToken.type = currentState + NUM_KEYWORDS;
                                strcpy(newToken.instance, word);
                                newToken.lineNum = nextChar.lineNum;
                                return newToken;
                        }
                }
        }
        return newToken;
}

character filter(FILE *inputFile) {
        character input;
        char x = fgetc(inputFile);
        int colNum = getTableColNum(x);

        while (colNum == COMMENT) {
            do {
                x = fgetc(inputFile);
                if (x == '\n') {
                    lineNum++;
                }
            } while (x != '#');
            x = fgetc(inputFile);
            colNum = getTableColNum(x);
        }

        if (colNum >= LOWER && colNum <= ENDOFFILE) {
                input.value = x;
                input.tableColNum = colNum;
                input.lineNum = lineNum;
                if (x == '\n') {
                        lineNum++;
                }
                return input;
        }
        else {
                printf("\nScanner Error: Character '%c' not in alphabet (line %d)", x, lineNum);
                exit(colNum);
        }
}

int getTableColNum(char x) {
        if (islower(x)) {
                return LOWER;
        }
        if (isupper(x)) {
                return UPPER;
        }
        if (isdigit(x)) {
                return INT;
        }
        if (isspace(x)) {
                return WS;
        }
        if (x == '=') {
                return EQ;
        }
        if (x == '<') {
                return LESS;
        }
        if (x == '>') {
                return GREATER;
        }
        if (x == ':') {
                return COL;
        }
        if (x == '+') {
                return PLUS;
        }
        if (x == '-') {
                return MINUS;
        }
        if (x == '*') {
                return MULT;
        }
        if (x == '/') {
                return DIV;
        }
        if (x == '%') {
                return MOD;
        }
        if (x == '.') {
                return DOT;
        }
        if (x == '(') {
                return LPAREN;
        }
        if (x == ')') {
                return RPAREN;
        }
        if (x == ',') {
                return COMMA;
        }
        if (x == '{') {
                return LBRACE;
        }
        if (x == '}') {
                return RBRACE;
        }
        if (x == ';') {
                return SEMICOL;
        }
        if (x == '[') {
                return LBRACK;
        }
        if (x == ']') {
                return RBRACK;
        }
        if (x == EOF) { // for EOFtk token
                return ENDOFFILE;
        }
        if (x == '#') {
                return COMMENT;
        }
        return ERROR;
}

void printToken(token t) {
    if (t.type == EOFtk) {
        printf("%s\n", tokenNames[t.type]);
    }
    else {
        printf("%s %s %d\n", tokenNames[t.type], t.instance, t.lineNum);
    }
}
