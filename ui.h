//
// Created by Blue Sky on 4/4/20.
//

#ifndef SURAKARTA_ZERO_UI_H
#define SURAKARTA_ZERO_UI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "chessboard.h"
class UI{
public:
    UI();
    void game();
private:
    string ttfPath = "../resource/HelveticaLt.ttf";
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
    SDL_Texture *Blackmax;
    SDL_Texture *Blackmini;
    SDL_Texture *Whitemax;
    SDL_Texture *Whitemini;
    SDL_Texture *Computermax;
    SDL_Texture *Computermini;
    SDL_Texture *Humanmax;
    SDL_Texture *Humanmini;
    SDL_Texture *dback;
    SDL_Texture *tishi;
    SDL_Texture *tishi_1;
    void display(Chessboard myBoard);
};
#endif //SURAKARTA_ZERO_UI_H
