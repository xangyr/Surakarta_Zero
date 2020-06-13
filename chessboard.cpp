//
// Created by Blue Sky on 4/3/20.
//

#include "chessboard.h"

Chessboard::Chessboard(int who) {  //初始化棋盘，上12黑，下12白
    //if(!restore()) {
        this->side = who;
        for (int a = 0; a < 6; a++) {
            for (int b = 0; b < 6; b++) {
                if (a < 2)
                    board[a][b] = BLACK_CHESS;
                else if (a >= 4)
                    board[a][b] = WHITE_CHESS;
                else
                    board[a][b] = NO_CHESS;
            }
        }
   // }
    updateNum();
}

Chessboard::Chessboard(int who,int board[6][6]) {   //根据二维数组初始化棋盘
    this->side = who;
    for(int a=0;a<6;a++){
        for(int b=0;b<6;b++){
            this->board[a][b] = board[a][b];
        }
    }
    updateNum();
}

void Chessboard::updateNum(){
    black=0;white=0;
    for(int a=0;a<6;a++){
        for(int b=0;b<6;b++){
            this->board[a][b] = board[a][b];
            if(board[a][b]==BLACK_CHESS)
                black++;
            else if(board[a][b]==WHITE_CHESS)
                white++;
        }
    }
}


void Chessboard::print() {
    for(int  a=0;a<6;a++){
        for(int b=0;b<6;b++)
            if(board[a][b]==BLACK_CHESS)
                printf("2 ");
            else
                printf("%d ",board[a][b]);
        printf("\n");
    }
}

int Chessboard::judge(){//返回1代表自己输了，返回2代表对方输了，返回0代表未分出胜负
    if(side==BLACK_CHESS) {
        if (black == 0)
            return 1;
        else if (white == 0)
            return 2;
        else
            return 0;
}
    else{
        if (black == 0)
            return 2;
        else if (white == 0)
            return 1;
        else
            return 0;
    }
}

int Chessboard::makeMove(singleMove x,int minimaxPlayer){
    int origin = board[x.to.x][x.to.y];
    board[x.from.x][x.from.y] = 0;
    board[x.to.x][x.to.y] = minimaxPlayer;
    if(origin==BLACK_CHESS)
        black--;
    else if(origin==WHITE_CHESS)
        white--;
    return origin;
}

int Chessboard::unMakeMove(singleMove x,int minimaxPlayer,int origin){
    board[x.to.x][x.to.y] = origin;
    board[x.from.x][x.from.y] = minimaxPlayer;
    if(origin==BLACK_CHESS)
        black++;
    else if(origin==WHITE_CHESS)
        white++;
}

bool Chessboard::isLegal(int from_x,int from_y,int to_x,int to_y){
    ArrayList move_array;
    Move_Generate(move_array,board[from_x][from_y]);
    singleMove x;
    if(move_array.find(from_x,from_y,to_x,to_y))
        return true;
    return false;
}

void Chessboard::store(){
    ofstream storeFile("../resource/store.txt",ios::out);
    for(int a=0;a<6;a++){
        for(int b=0;b<6;b++){
            storeFile<<board[a][b]<<" ";
        }
        storeFile<<endl;
    }
    storeFile<<side;
    storeFile.close();
}

bool Chessboard::restore(){
    ifstream restoreFile("../resource/store.txt",ios::in);
    for(int a=0;a<6;a++){
        for(int b=0;b<6;b++) {
            restoreFile >> board[a][b];
            if(restoreFile.eof())
                return false;
        }
    }
    restoreFile >> side;
    return true;
}