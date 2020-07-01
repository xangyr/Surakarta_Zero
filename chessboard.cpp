//
// Created by Blue Sky on 4/3/20.
//

#include "chessboard.h"

Chessboard::Chessboard() {                   //Initialize the chessboard with 12 black chess on the top and 12 white chess on the bottom
}

Chessboard::Chessboard(int who) {                   //Initialize the chessboard with 12 black chess on the top and 12 white chess on the bottom
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

Chessboard::Chessboard(int who,int board[6][6]) {   //Initialize the chessboard with a 2-deminsion matrix
    this->side = who;
    for(int a=0;a<6;a++){
        for(int b=0;b<6;b++){
            this->board[a][b] = board[a][b];
        }
    }
    updateNum();
}

void Chessboard::operator=(const Chessboard &otherBoard ){
    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++)
            board[i][j] = otherBoard.board[i][j];
    }
    black = otherBoard.black;
    white = otherBoard.white;
    side = otherBoard.side;
}
void Chessboard::updateNum(){                       //Update the number of black and white chess according to the chessboard
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


void Chessboard::print() {                          //print the chessboard
    for(int  a=0;a<6;a++){
        for(int b=0;b<6;b++)
            if(board[a][b]==BLACK_CHESS)
                printf("2 ");
            else
                printf("%d ",board[a][b]);
        printf("\n");
    }
    cout<<"black="<<black<<"  white="<<white<<endl;
}

int Chessboard::judge(){                            //determind whether there is a side to win, 1 means oppsite win, 2 means myself win, 0 means there is no side winning
    if(side==BLACK_CHESS) {
        if (black == 0)
            return 1;
        else if (white == 0)
            return 2;
        else
            return 0;
}
    else{
        if (white == 0)
            return 1;
        else if (black == 0)
            return 2;
        else
            return 0;
    }
}

int Chessboard::makeMove(singleMove x,int minimaxPlayer){   //make the move with minimaxPlayer on the chessboard
    int origin = board[x.to.x][x.to.y];
    if(board[x.from.x][x.from.y] == board[x.to.x][x.to.y])
        cout<<"what!!!"<<endl;
    board[x.from.x][x.from.y] = 0;
    board[x.to.x][x.to.y] = minimaxPlayer;
    if(origin==BLACK_CHESS)
        black--;
    else if(origin==WHITE_CHESS)
        white--;
    return origin;
}

int Chessboard::unMakeMove(singleMove x,int minimaxPlayer,int origin){  //restore the chessboard with move, the moving chess and the original chess color of the place begin placed 
    board[x.to.x][x.to.y] = origin;
    board[x.from.x][x.from.y] = minimaxPlayer;
    if(origin==BLACK_CHESS)
        black++;
    else if(origin==WHITE_CHESS)
        white++;
}

bool Chessboard::isLegal(int from_x,int from_y,int to_x,int to_y){      //judge whether the move being made is legal.
    ArrayList move_array;
    Move_Generate(move_array,board[from_x][from_y]);
    singleMove x;
    if(move_array.find(from_x,from_y,to_x,to_y))
        return true;
    return false;
}

void Chessboard::store(){
    ofstream storeFile("../resource/store.txt",ios::out);               //store the chessboard to the FILE
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
    ifstream restoreFile("../resource/store.txt",ios::in);             //restore the chessboard according to FILE
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

void Chessboard::check(){
    int wN=0,bN=0;
    for(int a=0;a<6;a++){
        for(int b=0;b<6;b++){
            if(board[a][b]==BLACK_CHESS)
                bN++;
            else if(board[a][b]==WHITE_CHESS)
                wN++;
        }
    }
    if(wN != white || bN != black)
        cout<<"NONONONO";
}