//
// Created by Blue Sky on 4/5/20.
//

#ifndef SURAKARTA_ZERO_TEST_H
#define SURAKARTA_ZERO_TEST_H
#define MG 1
#define AB 2
#include <stdio.h>
#include <ctime>
class test{
public:
    void run_test(int command,int times);
private:
    int chessboard[6][6];
    void testMoveGenerator();
    void testAlphaBeta();
};
;
#endif //SURAKARTA_ZERO_TEST_H
