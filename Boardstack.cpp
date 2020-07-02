#include "Boardstack.h"

Boardstack::Boardstack(){
    first = true;
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
    n->next = NULL:
    tail->next = n;
    tail = tail -> next;
}

void Boardstack::pop(Chessboard gameBoard){
    //对于head的操作
    stackNode *d = head;
    head = head->next;
    free(d)
}
