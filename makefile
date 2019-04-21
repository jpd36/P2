CC = gcc
CFLAGS = -g -Wall
TARGET = frontEnd
OBJ = P2.o parser.o scanner.o testTree.o

%.o: %.c
	$(CC) $(CFLAGS) -c $<

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

P2.o: P2.c node.h parser.h testTree.h
parser.o: parser.c token.h node.h scanner.h testTree.h parser.h
scanner.o: scanner.c character.h token.h testTree.h scanner.h
testTree.o: testTree.c token.h node.h testTree.h

clean:
	rm -f $(TARGET) $(OBJ)
