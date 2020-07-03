//
// Created by Blue Sky on 3/31/20.
//

#ifndef SURAKARTA_ZERO_BASIC_H
#define SURAKARTA_ZERO_BASIC_H
#define Hash_table_length 2048
#define HashExact 0
#define HashAlpha 1
#define HashBeta 2
#define NO_CHESS 0
#define WHITE_CHESS 1
#define BLACK_CHESS -1
#define EXIT_FLAG -1
#define HUMAN_FIRST 1
#define COMPUTER_FIRST 2
#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef struct{
    int x;
    int y;
}Position;

typedef struct{
    Position from;
    Position to;
    int value;
}Move_p;

typedef struct{
    Position from;
    Position to;
}singleMove;

typedef struct{
    Position node;
    int arc;
    int next;
    int pre;
}Orbit;

typedef  struct{
    int amount;
    int node_1;
    int node_2;
}Orbit_Index;

typedef struct{
    int chess;
    Position from;
}Rool;


typedef struct{
    int depth;
    int minimaxplayer;
}AlphaBeta_data;

typedef struct{
    uint64_t key;
    int depth;
    int type;
    int value;
}Hash_Move;

typedef struct{
    int chessboard[6][6];
    int depth;
    int alpha;
    int beta;
    int minimaxplayer;
    int value;
}Para;

typedef struct{
    int value;
    int best_move;
}Result;

typedef struct{
    int choice_1;
    int choice_2;
}choice;

typedef struct{
    Position from;
    int fromOrigin;
    Position to;
    int toOrigin;
}eachRound;

#endif //SURAKARTA_ZERO_BASIC_H
