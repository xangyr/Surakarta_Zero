#include "Boardstack.h"


Boardstack::Boardstack(){
    first = true;
    Chessboard initBoard(side);
    for(int i=0;i<8;i++)
        this->push(initBoard);
}

void Boardstack::writeSide(int side){
    this->side = side;
}

void Boardstack::push(Chessboard gameBoard){
    if(first){
        head = (stacknode *)malloc(sizeof(stackNode));
        head->board = gameBoard;
        head->next = NULL;
        first = false;
        tail = head;
        return;
    }
    stackNode *n = (stacknode *)malloc(sizeof(stackNode));
    n -> board = gameBoard;
    n->next = NULL;
    tail->next = n;
    tail = tail -> next;
}

void Boardstack::pop(){
    //对于head的操作
    stackNode *d = head;
    head = head->next;
    free(d);
}

void Boardstack::fwrite(bool indexFlag){
    ofstream file;
    file.open("MCTSData.txt",ios::out | ios::app);
    stackNode *temp = head;
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
    pop();
}