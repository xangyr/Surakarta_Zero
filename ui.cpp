//
// Created by Blue Sky on 4/4/20.
//

#include "ui.h"

UI::UI() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Window *win = SDL_CreateWindow("Surakarta", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    back= IMG_LoadTexture(ren, "../resource/board.jpg");
    dback = IMG_LoadTexture(ren, "../resource/dboard.jpeg");
    chess= IMG_Load("../resource/Chess.jpg");
    whitechess= IMG_Load("../resource/WhiteChess.png");
    color = {0, 0, 0, 0};
    color1={191,191,191,191};
    color2 = {255,255,255,255};
    Uint32 color3 = SDL_MapRGB(chess->format, 255, 255, 255);
    SDL_SetColorKey(chess, SDL_TRUE, color3);
    Uint32 color4 = SDL_MapRGB(whitechess->format, 0, 0, 0);
    SDL_SetColorKey(whitechess, SDL_TRUE, color4);
    Chess=SDL_CreateTextureFromSurface(ren, chess);
    WhiteChess=SDL_CreateTextureFromSurface(ren, whitechess);
    Blackmini = renderText("Black Chess", color, 40);
    Blackmax = renderText("Black Chess",  color, 50);
    Whitemini = renderText("White Chess",  color2, 40);
    Whitemax = renderText("White Chess",  color2, 50);
    Humanmax= renderText("Human",  color2, 50);
    Humanmini = renderText("Human",  color2, 40);
    Computermax = renderText("Computer",  color, 50);
    Computermini = renderText("Computer",  color, 40);
    tishi = renderText("Choose the chess for computer", color1, 35);
    tishi_1 = renderText("Choose the first side play",  color1, 35);
    SDL_Texture *win1 = renderText("Black Chess WIN!", color2, 40);
    SDL_Texture *win2 = renderText("White Chess WIN!",  color2, 40);
    for(int a=0;a<6;a++){
        for(int b=0;b<6;b++){
            display_position[a][b].x=250+b*60-20;
            display_position[a][b].y=150+a*60-20;
            display_position[a][b].w=40;
            display_position[a][b].h=40;
        }
    }
}

SDL_Texture *UI::renderText(string s, SDL_Color color,int fontSize)
{
    TTF_Font *font = TTF_OpenFont( ttfPath.c_str(), fontSize);
    if (font == NULL)
    {
        printf("TTF_OpenFont");
        return NULL;
    }
    SDL_Surface *surf = TTF_RenderText_Blended(font, s.c_str(), color);
    if (surf == NULL)
    {
        TTF_CloseFont(font);
        printf("TTF_RenderText");
        return NULL;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, surf);
    if (texture == NULL)
    {
        printf("TTF_CreateTexture");
    }
    SDL_FreeSurface(surf);
    TTF_CloseFont(font);
    return texture;
}

void UI::display(Chessboard myBoard){//用于打印所有的棋子
    SDL_Rect chessw,chessb;
    chessw.x=0;chessw.y=0;
    chessw.w=225;chessw.h=225;
    chessb.x=42;chessb.y=553;
    chessb.w=428;chessb.h=428;
    for(int a=0;a<6;a++){
        for(int b=0;b<6;b++){
            if(myBoard.board[a][b]==BLACK_CHESS){
                SDL_RenderCopy(ren, Chess, &chessb, &display_position[a][b]);
            }
            else if(myBoard.board[a][b]==WHITE_CHESS){
                SDL_RenderCopy(ren, WhiteChess, &chessw, &display_position[a][b]);
            }
        }
    }
}

void UI::game(){
    SDL_Event e;
    SDL_PollEvent(&e);
    Chessboard board(1);
    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, back, NULL, NULL);
    display(board);
    SDL_RenderPresent(ren);
    SDL_Delay(10000);
}