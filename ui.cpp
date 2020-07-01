//
// Created by Blue Sky on 4/4/20.
//

#include "ui.h"

UI::UI() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Window *win = SDL_CreateWindow("Surakarta", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    back= IMG_LoadTexture(ren, "resource/board.jpg");
    dback = IMG_LoadTexture(ren, "resource/dboard.jpeg");
    chess= IMG_Load("resource/Chess.jpg");
    whitechess= IMG_Load("resource/WhiteChess.png");
    color = {0, 0, 0, 0};
    color1={191,191,191,191};
    color2 = {255,255,255,255};
    Uint32 color3 = SDL_MapRGB(chess->format, 255, 255, 255);
    SDL_SetColorKey(chess, SDL_TRUE, color3);
    Uint32 color4 = SDL_MapRGB(whitechess->format, 0, 0, 0);
    SDL_SetColorKey(whitechess, SDL_TRUE, color4);
    Chess=SDL_CreateTextureFromSurface(ren, chess);
    WhiteChess=SDL_CreateTextureFromSurface(ren, whitechess);
    blackS = renderText("Black Chess", color, 40);
    blackL = renderText("Black Chess",  color, 50);
    whiteS = renderText("White Chess",  color2, 40);
    whiteL = renderText("White Chess",  color2, 50);
    humanL= renderText("Human",  color2, 50);
    humanS = renderText("Human",  color2, 40);
    computerL = renderText("Computer",  color, 50);
    computerS = renderText("Computer",  color, 40);
    remind = renderText("Choose the chess for computer", color1, 35);
    remind1 = renderText("Choose the first side play",  color1, 35);
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
    for(int a=0;a<6;a++){
        for(int b=0;b<6;b++){
            position[a][b].x=250+b*60;
            position[a][b].y=150+a*60;
        }
    }
}

SDL_Texture *UI::renderText(string s, SDL_Color color,int fontSize)
{
    TTF_Font *font = TTF_OpenFont(ttfPath, fontSize);
    SDL_Surface *surf = TTF_RenderText_Blended(font, s.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, surf);
    SDL_FreeSurface(surf);
    TTF_CloseFont(font);
    return texture;
}

void UI::startGame(){
    choice Choice;
    Choice=chooseSide();
    int who=Choice.choice_1;
    int board[6][6] = {
        {0,0,0,0,0,-1},
        {1,0,-1,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,1,0,0},
        {1,1,0,0,0,1},
        {1,1,1,0,0,1}
    };

    Chessboard gameBoard(who);
    int who_turn=who;
    do{
        if(Choice.choice_2==HUMAN_FIRST){
            if(who_turn==who){
                if(placeMove(gameBoard)) {
                    who_turn = -who_turn;
                    gameBoard.store();
                }
            }
            else{
                if(!gameBoard.judge())
                    gameBoard.AI(round,7);
                cout<<endl;
                who_turn=-who_turn;
            }
        }
        else{
            if(who_turn==who){
                if(!gameBoard.judge())
                    gameBoard.AI(round,7);
                cout<<endl;
                who_turn=-who_turn;
            }
            else{
                if(placeMove(gameBoard)) {
                    who_turn = -who_turn;
                    gameBoard.store();
                }
            }
        }
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, back, NULL, NULL);
        display(gameBoard);
        SDL_RenderPresent(ren);
        if(game!=EXIT_FLAG)
            game=gameBoard.judge();
    }while(game!=1&&game!=2&&game!=EXIT_FLAG);
    if(game!=EXIT_FLAG)
    {
        ofstream storeFile("../resource/store.txt",ios::out);
        storeFile.close();
    }
    SDL_Quit();
}

choice UI::chooseSide(){
    int flag_1=1,flag_2=1;
    SDL_Rect whiteLRect,whiteSRect,blackLRect,blackSRect,humanLRect,humanSRect,computerLRect,computerSRect,remindRect,remindRect1;
    whiteLRect.x=380;whiteLRect.y=220;
    SDL_QueryTexture(whiteL, NULL, 0, &whiteLRect.w, &whiteLRect.h);
    whiteSRect.x=435;whiteSRect.y=220;
    SDL_QueryTexture(whiteS, NULL, 0, &whiteSRect.w, &whiteSRect.h);
    blackLRect.x=150;blackLRect.y=220;
    SDL_QueryTexture(blackL, NULL, 0, &blackLRect.w, &blackLRect.h);
    blackSRect.x=150;blackSRect.y=220;
    SDL_QueryTexture(blackS, NULL, 0, &blackSRect.w, &blackSRect.h);
    remindRect.x=165;remindRect.y=160;
    SDL_QueryTexture(remind, NULL, 0, &remindRect.w, &remindRect.h);

    humanLRect.x=405; humanLRect.y=350;
    SDL_QueryTexture(humanL, NULL, 0, & humanLRect.w, & humanLRect.h);
    humanSRect.x=425;humanSRect.y=350;
    SDL_QueryTexture(humanS, NULL, 0, &humanSRect.w, &humanSRect.h);
    computerLRect.x=160;computerLRect.y=350;
    SDL_QueryTexture(computerL, NULL, 0, &computerLRect.w, &computerLRect.h);
    computerSRect.x=170;computerSRect.y=350;
    SDL_QueryTexture(computerS, NULL, 0, &computerSRect.w, &computerSRect.h);
    remindRect1.x=180;remindRect1.y=300;
    SDL_QueryTexture(remind1, NULL, 0, &remindRect1.w, &remindRect1.h);

    choice Choice;
    Choice.choice_1=1;
    Choice.choice_2=1;
    SDL_RenderCopy(ren, dback, NULL, NULL);
    SDL_Rect blanket;
    blanket.x=140;blanket.y=150;blanket.w=525;blanket.h=300;
    SDL_SetRenderDrawColor(ren, 47, 54, 56, 255);
    SDL_RenderFillRects(ren, &blanket, 1);

    SDL_Event e;
    while(SDL_PollEvent(&e)!=3){
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, dback, NULL, NULL);
        SDL_RenderDrawRect(ren, &blanket);
        SDL_RenderFillRects(ren, &blanket, 1);
        SDL_RenderCopy(ren, remind, NULL, &remindRect);
        SDL_RenderCopy(ren, remind1, NULL, &remindRect1);
        if(flag_1)
        {
            if(e.type==SDL_KEYDOWN){
                if(e.key.keysym.sym==SDLK_RIGHT)
                    Choice.choice_1=WHITE_CHESS;
                else if(e.key.keysym.sym==SDLK_LEFT)
                    Choice.choice_1=BLACK_CHESS;
                else if(e.key.keysym.sym==SDLK_RETURN)
                {
                    flag_1=0;
                    SDL_Delay(500);
                }
            }
        }
        else if(flag_2){
            if(e.type==SDL_KEYDOWN){
                if(e.key.keysym.sym==SDLK_RIGHT)
                    Choice.choice_2=HUMAN_FIRST;
                else if(e.key.keysym.sym==SDLK_LEFT)
                    Choice.choice_2=COMPUTER_FIRST;
                else if(e.key.keysym.sym==SDLK_RETURN)
                    flag_2=0;
            }
        }
        else{
            return Choice;
        }
        if(Choice.choice_1==WHITE_CHESS)
        {
            SDL_RenderCopy(ren, blackS, NULL, &blackSRect);
            SDL_RenderCopy(ren, whiteL, NULL, &whiteLRect);
        }
        else if(Choice.choice_1==BLACK_CHESS)
        {
            SDL_RenderCopy(ren, blackL, NULL, &blackLRect);
            SDL_RenderCopy(ren, whiteS, NULL, &whiteSRect);
        }
        if(Choice.choice_2==HUMAN_FIRST)
        {
            SDL_RenderCopy(ren, humanL, NULL, &humanLRect);
            SDL_RenderCopy(ren, computerS, NULL, &computerSRect);
        }
        else if(Choice.choice_2==COMPUTER_FIRST)
        {
            SDL_RenderCopy(ren, humanS, NULL, &humanSRect);
            SDL_RenderCopy(ren, computerL, NULL, &computerLRect);
        }

        SDL_RenderPresent(ren);
    }
    return Choice;
}

int UI::placeMove(Chessboard &gameBoard){
    SDL_Event e;
    int x,y,mouse_x,mouse_y;
    static eachRound r;
    static int mode;
    while(SDL_PollEvent(&e)){
        switch (e.type){
            case SDL_KEYDOWN:
                switch(e.key.keysym.sym){
                     case SDLK_b:{
                         if(!round.empty()){
                             r = round.top();
                             round.pop();
                             gameBoard.board[r.from.x][r.from.y] = r.fromOrigin;
                             gameBoard.board[r.to.x][r.to.y] = r.toOrigin;
                         }
                         mode = 1;
                     }
                     case SDLK_e:{
                         ofstream storeFile("../resource/store.txt",ios::out);
                         storeFile.close();
                         game = EXIT_FLAG;
                     }
                }
                break;
            case SDL_MOUSEBUTTONDOWN: {
                mouse_x = e.button.x;
                mouse_y = e.button.y;
                x = Locate_x(mouse_y);
                y = Locate_y(mouse_x);
                if (Play_H(gameBoard, x, y))
                    return 1;
            }
        }
    }
    return 0;
}

int UI::Play_H(Chessboard &gameboard,int x,int y){//用于人类回合下子
    static int a=-1,b=-1;
    int origin=-gameboard.side,target;
    if(gameboard.board[x][y]==-gameboard.side){
        a=x;b=y;
    }
    else {
        if(a!=-1&&b!=-1){
            if(gameboard.isLegal(a,b,x,y))
            {
                target = gameboard.board[x][y];
                gameboard.board[a][b]=0;
                gameboard.board[x][y]=-gameboard.side;
                eachRound r{a,b,origin,x,y,target};
                round.push(r);
                a=-1;b=-1;
                gameboard.updateNum();
                return 1;
            }
        }
    }
    return 0;
}

void UI::display(Chessboard gameBoard){//用于打印所有的棋子

    SDL_Rect chessw,chessb;
    chessw.x=0;chessw.y=0;
    chessw.w=225;chessw.h=225;
    chessb.x=42;chessb.y=553;
    chessb.w=428;chessb.h=428;
    for(int a=0;a<6;a++){
        for(int b=0;b<6;b++){
            if(gameBoard.board[a][b]==BLACK_CHESS){
                SDL_RenderCopy(ren, Chess, &chessb, &display_position[a][b]);
            }
            else if(gameBoard.board[a][b]==WHITE_CHESS){
                SDL_RenderCopy(ren, WhiteChess, &chessw, &display_position[a][b]);
            }
        }
    }
}

int UI::Locate_x(int mouse_y){ //用于根据鼠标的点击坐标确定二维数组的x
    int result=0,flag=600;
    for(int a=0;a<6;a++){
        if(abs(mouse_y-position[a][0].y)<flag){
            flag=abs(mouse_y-position[a][0].y);
            result=a;
        }
    }
    return result;
}

int UI::Locate_y(int mouse_x){ //用于根据鼠标的点击坐标确定二维数组的y
    int result=0,flag=800;
    for(int a=0;a<6;a++){
        if(abs(mouse_x-position[0][a].x)<flag){
            flag=abs(mouse_x-position[0][a].x);
            result=a;
        }
    }
    return result;
}
