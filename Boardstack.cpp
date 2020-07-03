#include "Boardstack.h"


Boardstack::Boardstack(int side){
    first = true;
    this->side = side;
    Chessboard initBoard(side);
    for(int i=0;i<8;i++)
        this->push(initBoard, side);
}

void Boardstack::push(Chessboard gameBoard, int chessColor){
    if(first){
        head = (stacknode *)malloc(sizeof(stackNode));
        for(int i=0;i<6;i++){
            for(int j=0;j<6;j++){
                if(gameBoard.board[i][j] == chessColor)
                    head->board.board[i][j] = 1;
                else
                    head->board.board[i][j] = 0;
            }
        }
        head->next = NULL;
        first = false;
        tail = head;
        return;
    }
    stackNode *n = (stacknode *)malloc(sizeof(stackNode));
    for(int i=0;i<6;i++){
            for(int j=0;j<6;j++){
                if(gameBoard.board[i][j] == chessColor)
                    n->board.board[i][j] = 1;
                else
                    n->board.board[i][j] = 0;
            }
        }
    n->next = NULL;
    tail->next = n;
    tail = tail -> next;
}

void Boardstack::pop(){
    stackNode *temp = head;
    head = head->next;
    free(temp);
}

void Boardstack::fwrite(bool indexFlag){
    ofstream file;
    file.open("MCTSData.txt",ios::out | ios::app);
    stackNode *temp = head;
    if(temp == NULL)
        cout<<"Error";
    for(int a=0;a<8;a++){
        temp->board.fwrite(&file);
        temp = temp->next;
    }
    if(indexFlag){
        for(int i=0;i<6;i++){
            for(int j=0;j<6;j++)
                file<<this->side<<" ";
            file<<endl;
    }
    file<<endl;
    }
    file.close();
}