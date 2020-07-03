//
// Created by Blue Sky on 4/4/20.
//

#ifndef SURAKARTA_ZERO_UI_H
#define SURAKARTA_ZERO_UI_H

#include <stack>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "chessboard.h"
#include "Boardstack.h"

class UI{
public:
    UI();
    void startGame();
private:
    int game;
    const char ttfPath[30] = "resource/HelveticaLt.ttf";
    SDL_Texture *back;
    SDL_Surface *chess;
    SDL_Surface *whitechess;
    SDL_Color color;
    SDL_Color color1;
    SDL_Color color2;
    SDL_Texture *renderText(string s, SDL_Color color,int fontSize);
    SDL_Renderer *ren;
    SDL_Texture *Chess;
    SDL_Texture *WhiteChess;
    SDL_Rect position[6][6];
    SDL_Rect display_position[6][6];
    SDL_Texture *blackL;
    SDL_Texture *blackS;
    SDL_Texture *whiteL;
    SDL_Texture *whiteS;
    SDL_Texture *computerL;
    SDL_Texture *computerS;
    SDL_Texture *humanL;
    SDL_Texture *humanS;
    SDL_Texture *dback;
    SDL_Texture *remind;
    SDL_Texture *remind1;
    stack <eachRound> round;
    void display(Chessboard gameBoard);
    int placeMove(Chessboard &gameBoard);
    int Play_H(Chessboard &gameboard,int x,int y);
    int Locate_x(int mouse_y);
    int Locate_y(int mouse_x);
    choice chooseSide();
};
#endif //SURAKARTA_ZERO_UI_H
