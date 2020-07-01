//
// Created by Blue Sky on 4/3/20.
//

#ifndef SURAKARTA_ZERO_CHESSBOARD_H
#define SURAKARTA_ZERO_CHESSBOARD_H
using namespace std;

#include <stack>
#include <fstream>
#include "basic.h"
#include "ArrayList.h"
//产生的走法序列查重问题


class Chessboard{
public:
    int board[6][6];
    int black;
    int white;
    int side;
    Chessboard();
    Chessboard(int who);
    Chessboard(int who,int board[6][6]);
    void operator=(const Chessboard &otherBoard );
    void print();
    int judge();
    void Move_Generate(ArrayList &move_array, int who);
    int makeMove(singleMove x,int minimaxPlayer);
    int unMakeMove(singleMove x,int minimaxPlayer,int origin);
    int Evaluate(int who_test);
    int alphaBeta(int depth, int alpha, int beta, int minimaxPlayer);
    singleMove alphaBetaMove(int depth, int alpha, int beta, int minimaxPlayer);
    bool isLegal(int from_x,int from_y,int to_x,int to_y);
    void AI(stack <eachRound>&round,int depth);
    void store();
    void check();
    void updateNum();
private:
    void Attack_Orbit(ArrayList &move_array,Rool rool[][6],int *flag_index,int who);
    void Generate_Move_Attack(ArrayList &move_array,int who);
    int extract_outside_rool_1(Rool *rool_1);
    int extract_outside_rool_2(Rool *rool);
    int extract_outside_rool_3(Rool *rool);
    int extract_outside_rool_4(Rool *rool_4);
    int extract_inside_rool_1(Rool *rool_1);
    int extract_inside_rool_2(Rool *rool);
    int extract_inside_rool_3(Rool *rool);
    int extract_inside_rool_4(Rool *rool_4);
    int count();
    int position_value();
    int greenpotential();
    int arc_count();
    int anotherMark();
    int Evaluate_test(int who_test);
    bool restore();

};

#endif //SURAKARTA_ZERO_CHESSBOARD_H
