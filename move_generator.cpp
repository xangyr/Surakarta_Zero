//
// Created by Blue Sky on 4/5/20.
//
#include "chessboard.h"
void Chessboard::Move_Generate(ArrayList &move_array, int who)
{
    Generate_Move_Attack(move_array,who);
    for (int a=0;a<6; a++){
        for (int b=0;b<6;b++){
            if (board[a][b] == who){
                for (int c = a - 1; c <= a + 1; c++)
                    for (int d = b - 1; d <= b + 1; d++){
                        if (c< 0)
                            break;
                        if (d < 0)
                            d = 0;
                        if (c > 5)
                            break;
                        if (d > 5)
                            break;
                        if (board[c][d] == 0){

                            move_array.push(a,b,c,d);

                        }
                    }
            }
        }
    }

}

void Chessboard::Generate_Move_Attack(ArrayList &move_array,int who){

    Rool rool[4][6];
    int  flag_index[4];
    flag_index[0]=extract_outside_rool_1(rool[0]);
    flag_index[1]=extract_outside_rool_2(rool[1]);
    flag_index[2]=extract_outside_rool_3(rool[2]);
    flag_index[3]=extract_outside_rool_4(rool[3]);

    Attack_Orbit(move_array,rool,flag_index,who);

    flag_index[0]=extract_inside_rool_1(rool[0]);
    flag_index[1]=extract_inside_rool_2(rool[1]);
    flag_index[2]=extract_inside_rool_3(rool[2]);
    flag_index[3]=extract_inside_rool_4(rool[3]);

    Attack_Orbit(move_array,rool,flag_index,who);
}

void Chessboard::Attack_Orbit(ArrayList &move_array,Rool rool[][6],int *flag_index,int who){
    for(int a=0;a<4;a++){
        if(flag_index[a]!=0){
            if(board[rool[a][flag_index[a]-1].from.x][rool[a][flag_index[a]-1].from.y]==who){
                int find_unnull=a+1;
                if(find_unnull>=4)
                    find_unnull=0;
                while(!flag_index[find_unnull]){
                    find_unnull++;
                    if(find_unnull>=4)
                        find_unnull=0;
                }
                if(rool[a][flag_index[a]-1].chess==rool[find_unnull][0].chess)
                {
                    if(rool[a][flag_index[a]-1].from.x==rool[find_unnull][0].from.x&&rool[a][flag_index[a]-1].from.y==rool[find_unnull][0].from.y)
                    {
                        int index=find_unnull;
                        if(flag_index[find_unnull]>=2)
                        {
                            if(rool[find_unnull][1].chess==-who){
                                move_array.push_unrepeat(rool[find_unnull][0].from.x,rool[find_unnull][0].from.y,rool[find_unnull][1].from.x,rool[find_unnull][1].from.y);
                            }
                        }

                        index=a;
                        if(flag_index[a]>=2)
                        {
                            if(rool[a][flag_index[a]-2].chess==-who)
                            {
                                move_array.push_unrepeat(rool[a][flag_index[a]-1].from.x,rool[a][flag_index[a]-1].from.y,rool[a][flag_index[a]-2].from.x,rool[a][flag_index[a]-2].from.y);
                            }
                        }
                    }

                }

                else
                    move_array.push_unrepeat(rool[a][flag_index[a]-1].from.x,rool[a][flag_index[a]-1].from.y,rool[find_unnull][0].from.x,rool[find_unnull][0].from.y);
            }
            if(board[rool[a][0].from.x][rool[a][0].from.y]==who)
            {
                int find_unnull=a-1;
                if(find_unnull<0)
                    find_unnull=3;
                while(!flag_index[find_unnull]){
                    find_unnull--;
                    if(find_unnull<0)
                        find_unnull=3;
                }
                if(rool[a][0].chess==rool[find_unnull][flag_index[find_unnull]-1].chess)
                {
                }

                else{
                    move_array.push_unrepeat(rool[a][0].from.x,rool[a][0].from.y,rool[find_unnull][flag_index[find_unnull]-1].from.x,rool[find_unnull][flag_index[find_unnull]-1].from.y);
                }
            }
        }
    }


}


int Chessboard::extract_outside_rool_1(Rool *rool_1){

    int index=0;
    for(int a=5;a>=0;a--){
        if(board[2][a]!=0){
            rool_1[index].chess=board[2][a];
            rool_1[index].from.x=2;
            rool_1[index].from.y=a;
            index++;
        }
    }
    return index;
}
int Chessboard::extract_outside_rool_2(Rool *rool){

    int index=0;
    for(int a=0;a<6;a++){
        if(board[a][2]!=0){
            rool[index].chess=board[a][2];
            rool[index].from.x=a;
            rool[index].from.y=2;
            index++;
        }
    }
    return index;
}
int Chessboard::extract_outside_rool_3(Rool *rool){

    int index=0;
    for(int a=0;a<6;a++){
        if(board[3][a]!=0){
            rool[index].chess=board[3][a];
            rool[index].from.x=3;
            rool[index].from.y=a;
            index++;
        }
    }
    return index;
}
int Chessboard::extract_outside_rool_4(Rool *rool_4){

    int index=0;
    for(int a=5;a>=0;a--){
        if(board[a][3]!=0){
            rool_4[index].chess=board[a][3];
            rool_4[index].from.x=a;
            rool_4[index].from.y=3;
            index++;
        }
    }
    return index;
}
int Chessboard::extract_inside_rool_1(Rool *rool_1){

    int index=0;
    for(int a=5;a>=0;a--){
        if(board[1][a]!=0){
            rool_1[index].chess=board[1][a];
            rool_1[index].from.x=1;
            rool_1[index].from.y=a;
            index++;
        }
    }
    return index;
}
int Chessboard::extract_inside_rool_2(Rool *rool){

    int index=0;
    for(int a=0;a<6;a++){
        if(board[a][1]!=0){
            rool[index].chess=board[a][1];
            rool[index].from.x=a;
            rool[index].from.y=1;
            index++;
        }
    }
    return index;
}
int Chessboard::extract_inside_rool_3(Rool *rool){

    int index=0;
    for(int a=0;a<6;a++){
        if(board[4][a]!=0){
            rool[index].chess=board[4][a];
            rool[index].from.x=4;
            rool[index].from.y=a;
            index++;
        }
    }
    return index;
}
int Chessboard::extract_inside_rool_4(Rool *rool_4){

    int index=0;
    for(int a=5;a>=0;a--){
        if(board[a][4]!=0){
            rool_4[index].chess=board[a][4];
            rool_4[index].from.x=a;
            rool_4[index].from.y=4;
            index++;
        }
    }
    return index;
}
