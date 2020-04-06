//
// Created by Blue Sky on 3/31/20.
//

#include "basic.h"
extern int chessboard[6][6];
extern int who;

Move::Move(int from_x,int from_y,int to_x,int to_y){
    move.from.x = from_x;
    move.from.y = from_y;
    move.to.x = to_x;
    move.to.y = to_y;
}

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}
int mini(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}
