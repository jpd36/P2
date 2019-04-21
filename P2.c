//Jonathan Pham
//CS4280 P2
//04/21/19

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "parser.h"
#include "testTree.h"

int main ( int argc, char *argv [] ) {
    if (argc > 2) {
        printf("Main Error: Expected 1 or no arguments!\n");
        return ( 1 );
    }

    FILE *inputFilePtr = NULL;
    char *fileName = NULL;

    if (argc == 2) {
        const char fileExt[] = ".input1";

        fileName = (char *) malloc(sizeof(argv[1]));
        strcpy(fileName, argv[1]);

        char inFile[strlen(fileName) + strlen(fileExt)];
        strcpy(inFile, fileName);
        strcat(inFile, fileExt);

        inputFilePtr = fopen(inFile, "r");

        if (!inputFilePtr) {
            printf("Main Error: File '%s' could not be opened!\n", inFile);
            return ( 1 );
        }
    }
    else {
        inputFilePtr = stdin;
    }

    node *root = parser(inputFilePtr);
    traversePreorder(root, 0);

    fclose(inputFilePtr);
    free(fileName);
    return ( 0 );
}
