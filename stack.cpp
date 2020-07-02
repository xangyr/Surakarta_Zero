#include "stack.h"

stack::stack() {
    size = 0;
}

stack::stack(Chessboard &gameboard) {
    push(gameboard);
}

stack::size() {
    return size;
}

void stack::push(Chessboard &gameboard) {
    if (size == 8) {
        pop();
    }
    for(int i = 0; i<6;i++) {
        for(int j = 0; j<6;j++) {
            thd_board[7 - size][i][j] = gameboard.get(i, j);
        }
    }
    size++;
}

void stack::pop(char *out) {
    if(!isempty()) {
        if (size < 8) {
            for(int a = 0; a < (8-size); a++) {
                for(int i = 0; i<6;i++) {
                    for(int j = 0; j<6;j++) {
                        out += thd_board[size-1][i][j];
                    }
                }
            } 
        }
        for(int k = 0; k < size; k++) {
            for(int i = 0; i<6;i++) {
                for(int j = 0; j<6;j++) {
                    out += thd_board[k][i][j];
                }
            }
        }

    }
    size--;
}

bool stack::isempty() {
    return size == 0;
}