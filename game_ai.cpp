//
// Created by Blue Sky on 3/31/20.
//
#include "game_ai.h"
extern int who;
extern int chessboard[6][6];
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
SDL_Texture  *tishi_1;

void game_AI(int depth){

    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Window *win = SDL_CreateWindow("Suratarka", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture *back= IMG_LoadTexture(ren, "../resource/Data/board.jpg");
    dback= IMG_LoadTexture(ren, "../resource/Data/dboard.jpeg");
    SDL_Surface *chess= IMG_Load("../resource/Data/Chess.jpg");
    SDL_Surface *whitechess= IMG_Load("../resource/Data/WhiteChess.png");
    SDL_Color color = {0, 0, 0, 0};
    SDL_Color color1={191,191,191,191};
    SDL_Color color2 = {255,255,255,255};
    Uint32 color3 = SDL_MapRGB(chess->format, 255, 255, 255);
    SDL_SetColorKey(chess, SDL_TRUE, color3);
    Uint32 color4 = SDL_MapRGB(whitechess->format, 0, 0, 0);
    SDL_SetColorKey(whitechess, SDL_TRUE, color4);
    Chess=SDL_CreateTextureFromSurface(ren, chess);
    WhiteChess=SDL_CreateTextureFromSurface(ren, whitechess);
    Blackmini = renderText("Black Chess", "../resource/Data/HelveticaLt.ttf", color, 40);
    Blackmax = renderText("Black Chess", "../resource/Data/HelveticaLt.ttf", color, 50);
    Whitemini = renderText("White Chess", "../resource/Data/HelveticaLt.ttf", color2, 40);
    Whitemax = renderText("White Chess", "../resource/Data/HelveticaLt.ttf", color2, 50);
    Humanmax= renderText("Human", "../resource/Data/HelveticaLt.ttf", color2, 50);
    Humanmini = renderText("Human", "../resource/Data/HelveticaLt.ttf", color2, 40);
    Computermax = renderText("Computer", "../resource/Data/HelveticaLt.ttf", color, 50);
    Computermini = renderText("Computer", "../resource/Data/HelveticaLt.ttf", color, 40);
    tishi = renderText("Choose the chess for computer", "../resource/Data/HelveticaLt.ttf", color1, 35);
    tishi_1 = renderText("Choose the first side play", "../resource/Data/HelveticaLt.ttf", color1, 35);
    SDL_Texture *win1 = renderText("Black Chess WIN!", "../resource/Data/HelveticaLt.ttf", color2, 40);
    SDL_Texture *win2 = renderText("White Chess WIN!", "../resource/Data/HelveticaLt.ttf", color2, 40);

    Chessboard_Init(chessboard);
    Init_Position();
    Init_Display_Position();
    
    choice Choice;
    Choice=begin();
    who=-Choice.choice_1;
    int *who_test=&who;

    SDL_Event e;

    int game=1,x,y,mouse_x,mouse_y;
    int *game_test=&game;
    printf("Choice_1=%d,Choice_2=%d\n",Choice.choice_1,Choice.choice_2);
    int who_turn=who;
    do{
        if(Choice.choice_2==1){
            if(who_turn==who){
                if(Place_Move(game_test,position))
                    who_turn=-who_turn;
            }
            else{
                AI(7);
                who_turn=-who_turn;
            }
        }
        else{
            if(who_turn==who){
                AI(7);
                who_turn=-who_turn;
            }
            else{

                if(Place_Move(game_test,position))
                    who_turn=-who_turn;
            }
        }
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, back, NULL, NULL);
        Display();
        SDL_RenderPresent(ren);
        game=judge(chessboard);
    }while(game!=1&&game!=2);
}


