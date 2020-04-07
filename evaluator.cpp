//
// Created by Blue Sky on 4/5/20.
//

#include "chessboard.h"
int chessboard_value[6][6]={
        {5,20,20,20,20,5},
        {20,30,50,50,30,20},
        {20,50,40,40,50,20},
        {20,50,40,40,50,20},
        {20,30,50,50,30,20},

        {5,20,20,20,20,5}
};
int greenPotential[16]={84,91,35,35,-20,25,-25,45,-45,-45,-84,20,-91,-35,-35};

int look_for[16][2]={
        {0,2},{2,0},{0,3},{2,5},{3,0},{5,2},{5,3},{3,5},
        {1,0},{0,1},{0,4},{1,5},{4,0},{5,1},{4,5},{5,4},
};
int look_for_intersection[8][2]={
        {2,2},{2,3},{3,2},{3,3},
        {1,1},{1,4},{4,1},{4,4},
};
int look_for_arc[20][2]={
        {0,0},{0,1},{0,2},{0,3},{0,4},{0,5},
        {1,5},{2,5},{3,5},{4,5},{5,5},
        {5,4},{5,3},{5,2},{5,1},{5,0},
        {4,0},{3,0},{2,0},{1,0}
};
int look_for_anotherMark[12][2]={
        {2,2},{1,2},{2,1},
        {2,3},{1,3},{2,4},
        {3,2},{3,1},{4,2},
        {3,3},{3,4},{4,3}
};

int arcPara;
int k1=1,k2=1,k3=1,k4=1;
int Chessboard::Evaluate(int who_test){
    int test=Evaluate_test(who_test);
    if(test==9999||test==-9999)
        return test;
    int value;
    int extendVal;
    int positionVal;
    int dynamicVal;
    int potentialVal;

    extendVal=count();
    positionVal=position_value()+arc_count()*arcPara;
    dynamicVal=anotherMark();
    potentialVal=greenpotential();
    value=extendVal*k1+positionVal*k2+dynamicVal*k3+potentialVal*k3;
    if(who_test==side)
        return value;
    else
        return -value;

}

int Chessboard::count(){

    int count=0;
    for(int a=0;a<6;a++){
        for(int b=0;b<6;b++){
            if(board[a][b]==side)
                count++;
            else if(board[a][b]==-side)
                count--;
        }
    }
    return count;
}
int Chessboard::position_value()
{
    int value = 0;
    for (int a = 0; a < 6; a++)
    {
        for (int b = 0; b < 6; b++)
        {
            if (board[a][b] == side)
                value += chessboard_value[a][b];
            else if (board[a][b] == -side)
                value -= chessboard_value[a][b];
        }
    }
    return value;
}
int Chessboard::greenpotential(){
    int value=0;
    for(int a=0;a<=15;a+=2){
        if(board[look_for_intersection[a/2][0]][look_for_intersection[a/2][1]]==side){
            if(board[look_for[a][0]][look_for[a][1]]==0&&board[look_for[a+1][0]][look_for[a+1][1]]==0)
            {value+=greenPotential[0];}
            else if(board[look_for[a][0]][look_for[a][1]]==-side&&board[look_for[a+1][0]][look_for[a+1][1]]==-side)
            {value+=greenPotential[1];}
            else if((board[look_for[a][0]][look_for[a][1]]==side||board[look_for[a+1][0]][look_for[a+1][1]]==side)&&(board[look_for[a][0]][look_for[a][1]]==0||board[look_for[a+1][0]][look_for[a+1][1]]==0))
            {value+=greenPotential[2];}
            else if(board[look_for[a][0]][look_for[a][1]]==side&&board[look_for[a+1][0]][look_for[a+1][1]]==side)
            {value+=greenPotential[4];}
        }
        else if(board[look_for_intersection[a/2][0]][look_for_intersection[a/2][1]]==0)
        {  if(board[look_for[a][0]][look_for[a][1]]==side&&board[look_for[a+1][0]][look_for[a+1][1]]==side)
            {value+=greenPotential[5];}
            else if(board[look_for[a][0]][look_for[a][1]]==-side&&board[look_for[a+1][0]][look_for[a+1][1]]==-side)
            {value+=greenPotential[6];}
            else if((board[look_for[a][0]][look_for[a][1]]==side||board[look_for[a+1][0]][look_for[a+1][1]]==side)&&(board[look_for[a][0]][look_for[a][1]]==0||board[look_for[a+1][0]][look_for[a+1][1]]==0))
            { value+=greenPotential[7];}
            else if((board[look_for[a][0]][look_for[a][1]]==-side||board[look_for[a+1][0]][look_for[a+1][1]]==-side)&&(board[look_for[a][0]][look_for[a][1]]==0||board[look_for[a+1][0]][look_for[a+1][1]]==0))
            {value+=greenPotential[9];}
        }
        else if(board[look_for_intersection[a/2][0]][look_for_intersection[a/2][1]]==-side){
            if(board[look_for[a][0]][look_for[a][1]]==0&&board[look_for[a+1][0]][look_for[a+1][1]]==0 )
            {value+=greenPotential[11];}
            else if(board[look_for[a][0]][look_for[a][1]]==-side&&board[look_for[a+1][0]][look_for[a+1][1]]==-side)
            {value+=greenPotential[12];}
            else if(board[look_for[a][0]][look_for[a][1]]==side&&board[look_for[a+1][0]][look_for[a+1][1]]==side)
            {value+=greenPotential[13];}
            else if((board[look_for[a][0]][look_for[a][1]]==side||board[look_for[a+1][0]][look_for[a+1][1]]==side)&&(board[look_for[a][0]][look_for[a][1]]==0||board[look_for[a+1][0]][look_for[a+1][1]]==0))
            {value+=greenPotential[14];}
        }
    }
    return value;
}
int Chessboard::arc_count(){
    int count=0;
    for(int a=0;a<20;a++)
    {
        if(board[look_for_arc[a][0]][look_for_arc[a][1]]==side)
            count++;
        else if(board[look_for_arc[a][0]][look_for_arc[a][1]]==-side)
            count--;
    }
    return count;
}
int Chessboard::anotherMark(){
    int count=0;
    for(int a=0;a<=9;a+=3){
        if(board[look_for_anotherMark[a][0]][look_for_anotherMark[a][1]]==side)
        {
            if(board[look_for_anotherMark[a+1][0]][look_for_anotherMark[a+1][1]]==-side&&board[look_for_anotherMark[a+1][0]][look_for_anotherMark[a+1][1]]==-side)
                count++;
        }
        else if(board[look_for_anotherMark[a][0]][look_for_anotherMark[a][1]]==-side){
            if(board[look_for_anotherMark[a+1][0]][look_for_anotherMark[a+1][1]]==side&&board[look_for_anotherMark[a+1][0]][look_for_anotherMark[a+1][1]]==side)
                count--;
        }
    }
    return count;
}

int Chessboard::Evaluate_test(int who_test){
    if(who_test==BLACK_CHESS) {
        if (black == 0)
            return -9999;
        if (white == 0)
            return 9999;
        else
            return black - white;
    }
    else{
        if (black == 0)
            return 9999;
        if (white == 0)
            return -9999;
        else
            return white-black;
    }
}