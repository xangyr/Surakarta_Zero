#include <iostream>
#include "ui.h"
#include "test.h"
#include "search_engine.h"
#include "chessboard.h"
#include "Boardstack.h"

int main() {
    /*
    test exam;
    exam.run_test(AB,1000);*/
     /*
    cout<<log10(10)<<endl;
    UI interface;
    interface.startGame();*/
    /*
   Chessboard gameBoard(BLACK_CHESS);
   MCTS MCTSTest(gameBoard);
   MCTSTest.search(BLACK_CHESS);*/
   Chessboard gameBoard(BLACK_CHESS);
   Boardstack s;
   s.push(gameBoard);
   s.push(gameBoard);
    return 0;
}
