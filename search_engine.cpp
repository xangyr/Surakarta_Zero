//
// Created by Blue Sky on 4/5/20.
//

#include "chessboard.h"

int Chessboard::Alpha_Beta(int depth, int alpha, int beta, int minimaxplayer)
{

    int hashf=HashAlpha;
    if (depth <= 0 || judge())
    {

        int value = Evaluate_test(minimaxplayer);
        return value;
    }
    int flag, val,origin;
    ArrayList move_array ;
    Move_Generate(move_array,minimaxplayer);
    singleMove x;
    while(move_array.size())
    {
        move_array.pop(x);
        origin = board[x.to.x][x.to.y];
        board[x.from.x][x.from.y] = 0;
        board[x.to.x][x.to.y] = minimaxplayer;
        val = -Alpha_Beta(depth - 1, -beta, -alpha, -minimaxplayer);
        board[x.to.x][x.to.y] = origin;
        board[x.from.x][x.from.y] = minimaxplayer;
        if(val>=beta){
            return beta;
        }
        if(val>alpha){
            hashf=HashExact;
            alpha=val;
        }
    }
    return alpha;
}