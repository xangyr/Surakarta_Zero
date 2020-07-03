#ifndef SURAKARTA_ZERO_BOARDSTACK_H
#define SURAKARTA_ZERO_BOARDSTACK_H
#include "chessboard.h"
#include <fstream>

typedef struct stacknode{
    Chessboard board;
    struct stacknode *next;
}stackNode;

class Boardstack{
public:
    Boardstack(int side);
    void push(Chessboard gameBoard, int chessColor);
    void fwrite(bool indexFlag);
    void writeSide(int side);
    void pop();
private:
    int side;
    bool first;
    stackNode *head;
    stackNode *tail;
};

#endif