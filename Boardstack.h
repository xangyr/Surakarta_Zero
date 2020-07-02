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
    Boardstack();
    void push(Chessboard gameBoard);
    void print();
private:
    bool first;
    stackNode *head;
    stackNode *tail;
    void pop();
};

#endif