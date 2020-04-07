//
// Created by Blue Sky on 4/5/20.
//

#include "chessboard.h"
#include <stdio.h>
extern FILE *xp;
int Chessboard::Alpha_Beta(int depth, int alpha, int beta, int minimaxplayer)
{
    if (depth <= 0 || judge())
    {
        int value = Evaluate_test(minimaxplayer);
        return value;
    }
    int val,origin;
    ArrayList move_array ;
    Move_Generate(move_array,minimaxplayer);
    singleMove x;
    while(move_array.size())
    {
        move_array.pop(x);
        origin = makeMove(x,minimaxplayer);
        val = -Alpha_Beta(depth - 1, -beta, -alpha, -minimaxplayer);
        unMakeMove(x,minimaxplayer,origin);
        if(val>=beta){
            return beta;
        }
        if(val>alpha){
            alpha=val;
        }
    }
    return alpha;
}