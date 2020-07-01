//
// Created by Blue Sky on 4/5/20.
//

#include "search_engine.h"
extern FILE *xp;


int get_index(){
    static int index;
    return index++;
}

int Chessboard::alphaBeta(int depth, int alpha, int beta, int minimaxPlayer)
{
    if (depth <= 0 || judge())
    {
        int value = Evaluate_test(minimaxPlayer);
        return value;
    }
    int val,origin;
    ArrayList move_array;
    Move_Generate(move_array,minimaxPlayer);
    singleMove x;
    ArrayList store;
    int index_temp;
    while(move_array.size())
    {
        move_array.pop(x);
        origin = makeMove(x,minimaxPlayer);
        val = -alphaBeta(depth - 1, -beta, -alpha, -minimaxPlayer);
        unMakeMove(x,minimaxPlayer,origin);
        if(val>=beta){
            return beta;
        }
        if(val>alpha){
            alpha=val;
        }
    }
    return alpha;
}

singleMove Chessboard::alphaBetaMove(int depth, int alpha, int beta, int minimaxPlayer)
{
    singleMove best_move;
    int flag, val,origin;
    ArrayList move_array ;
    Move_Generate(move_array,minimaxPlayer);
    singleMove x;
    move_array.pop(x);
    best_move = x;
    while(move_array.size())
    {
        origin = makeMove(x,minimaxPlayer);
        val = -alphaBeta(depth - 1, -beta, -alpha, -minimaxPlayer);
        unMakeMove(x,minimaxPlayer,origin);
        move_array.pop(x);
        cout<<val<<endl;
        if(val>alpha){
            alpha=val;
            best_move=x;
        }
    }
    cout<<-alpha<<endl;
    return best_move;
}

void Chessboard::AI(stack <eachRound>&round,int depth){
    //singleMove bestMove=alphaBetaMove(depth,-INT_MAX,INT_MAX,side);
    MCTS mcts(*this);
    singleMove bestMove = mcts.search(side);
    eachRound r{bestMove.from.x,bestMove.from.y,board[bestMove.from.x][bestMove.from.y],bestMove.to.x,bestMove.to.y,board[bestMove.to.x][bestMove.to.y]};
    round.push(r);
    makeMove(bestMove,side);
}



MCTSNode::MCTSNode(){
    value = 0;
    travelNum = 0;
    subNum = 0;
    ArrayList moveList;
    subMCTS = NULL;
    parent = NULL;
}

MCTS::MCTS(Chessboard gameBoard){
    this->oriBoard = gameBoard;
    this->oriBoard.print();
}

MCTS::~MCTS(){
    destory(&root);
}

singleMove MCTS::search(int side){
    bool expandFlag;
    int maxIndex,currentPlayer = side;
    double currentUCT,maxUCT;
    MCTSNode *currentNode;
    singleMove move;
    gameBoard = oriBoard;
    expand(&root,currentPlayer);
    gameBoard.updateNum();
    gameBoard.check();
    for(int i = 0; i<128000; i++){
        expandFlag = true;
        currentNode = &root;
        gameBoard = oriBoard;
        currentPlayer = side;
        while(currentNode->subNum != 0){
            maxUCT = currentNode->subMCTS[0].value/currentNode->subMCTS[0].travelNum + sqrt(2 * log(currentNode->travelNum)/currentNode->subMCTS[0].travelNum);
            maxIndex = 0;
            for(int j = 0; j < currentNode->subNum; j++){
                if(currentNode->subMCTS[j].travelNum == 0){
                    maxIndex = j;
                    break;
                }
                currentUCT = currentNode->subMCTS[j].value/currentNode->subMCTS[j].travelNum + sqrt(2 * log(currentNode->travelNum)/currentNode->subMCTS[j].travelNum);
                if(currentUCT > maxUCT) {
                    maxUCT = currentUCT;
                    maxIndex = j;
                }
            }
            currentNode->moveList.pull(move,maxIndex);
            gameBoard.makeMove(move,currentPlayer);
            currentPlayer = -currentPlayer;
            currentNode = &currentNode->subMCTS[maxIndex];
        }
        gameBoard.check();
        if(currentNode -> travelNum == 1) {
            expandFlag = expand(currentNode,currentPlayer);
            if(expandFlag){
                currentNode->moveList.pull(move,0);
                gameBoard.makeMove(move,currentPlayer);
                currentPlayer = -currentPlayer;
                currentNode = &currentNode->subMCTS[0];
            }
        }
        if(expandFlag)
            Backpropagation(currentNode,rollout(currentNode,currentPlayer));
    }
            currentNode = &root;
            maxUCT = currentNode->subMCTS[0].value/currentNode->subMCTS[0].travelNum;
            maxIndex = 0;
            for(int j = 0; j < currentNode->subNum; j++){
                currentUCT = currentNode->subMCTS[j].value/currentNode->subMCTS[j].travelNum;
                cout<<currentNode->subMCTS[j].value<<" "<<currentNode->subMCTS[j].travelNum<<" "<<currentUCT<<endl;
                if(currentUCT > maxUCT) {
                    maxUCT = currentUCT;
                    maxIndex = j;
                }
            }
    root.moveList.pull(move, maxIndex);
    cout<<"maxIndex = "<<maxIndex<<endl;
    return move; // need to return single for current root of mcts
}

bool MCTS::expand(MCTSNode *currentNode,int currentPlayer){
    if(!gameBoard.judge()){
        gameBoard.Move_Generate(currentNode->moveList,currentPlayer);
        currentNode->subNum = currentNode->moveList.size();
        if(currentNode->subNum == 0)
            cout<<currentNode->subNum<<endl;
        currentNode->subMCTS = new MCTSNode[currentNode->subNum];
        for(int i=0;i<currentNode->subNum;i++)
            currentNode->subMCTS[i].parent = currentNode;
        return true;
    }
    else
        return false;
}


int MCTS::rollout(MCTSNode *currentNode,int currentPlayer){
    /*
    check simulate in while true
    if currentplayer win,                   return reward 1
    if opposite win -> currentplayer lost,  return reward 0
    if draw,                                 return reward 0
    */
    while (true) {
        if (gameBoard.judge() == 1)
            return 0;
        if (gameBoard.judge() == 2)
            return 1;;
        ArrayList temp;
        gameBoard.Move_Generate(temp,currentPlayer);
        singleMove move;
        if(!temp.size()){
            if(gameBoard.side == BLACK_CHESS && gameBoard.black > gameBoard.white)
                return 1;
            else if(gameBoard.side == WHITE_CHESS && gameBoard.white > gameBoard.black)
                return 1;
            return 0;
        }
        temp.pull(move,rand()%temp.size());
        gameBoard.makeMove(move,currentPlayer);
        currentPlayer = -currentPlayer;   
    }
}

void MCTS::Backpropagation(MCTSNode *currentNode,int rolloutValue){
    while(currentNode != NULL){
        currentNode->value += rolloutValue;
        currentNode -> travelNum++;
        currentNode = currentNode->parent;
    }
}

void MCTS::destory(MCTSNode *node) {
    if(node->subNum)
        {
            for(int i=0;i<node->subNum;i++)
                destory(&(node->subMCTS[i]));
            delete []node->subMCTS;
        }
}