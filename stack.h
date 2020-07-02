#ifndef SURAKARTA_ZERO_STACK_H
#define SURAKARTA_ZERO_STACK_H
using namespace std;
#include <iostream>
#include <cstdlib>
#include "basic.h"
#include "chessboard.h"

class stack{
public:
    void push();
    void pop(char *out);
    int size();
    bool isempty();
private:
    int size;
    char *thd_board[8][6][6];
}