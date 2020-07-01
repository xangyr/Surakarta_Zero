//
// Created by Blue Sky on 4/5/20.
//

#include "test.h"
#include "chessboard.h"
FILE *xp;
void test::run_test(int command,int times){
    clock_t start,end;
    start = clock();
    if(command==1){
        for(int a=0;a<times;a++)
            testMoveGenerator();
    }
    else if(command==2){
        for(int a=0;a<times;a++)
            testAlphaBeta();
    }
    end = clock();
    cout<<"time:"<<(double)((end-start)/CLOCKS_PER_SEC)<<"s"<<endl;
}

void test::testMoveGenerator(){
    FILE *fp = fopen("resource/Data/testMoveGenerate.txt","r");
    int count=0,ta;

    int index_1,index_2,index_3,index_4;
    while(count<=5715){

        count++;

        for(int a=0;a<6;a++){
            for(int b=0;b<6;b++){
                fscanf(fp,"%d",&ta);
                if(ta==2)
                    chessboard[a][b]=-1;
                else
                    chessboard[a][b]=ta;
            }
        }
        Chessboard myBoard(1,chessboard);
        fscanf(fp,"%d %d %d %d",&index_1,&index_2,&index_3,&index_4);
        int save;
        ArrayList move_array;
        myBoard.Move_Generate(move_array,-1);
        save = move_array.size();
        if(move_array.size()!=index_3){

            printf("chess=1 \n%d %d\n",move_array.size(),index_3);
            for(int a=0;a<6;a++){
                for(int b=0;b<6;b++){
                    printf("%d ",chessboard[a][b]);
                }
                printf("\n");
            }
          //  visualize(h);

        }
        myBoard.Move_Generate(move_array,1);
        if(move_array.size()-save!=index_4){

            printf("chess=-1 \n%d %d\n",move_array.size()-save,index_4);
            for(int a=0;a<6;a++){
                for(int b=0;b<6;b++){
                    printf("%d ",chessboard[a][b]);
                }
                printf("\n");
            }
           // visualize(h);

        }


        count++;

    }
}

void test::testAlphaBeta(){
    double sum=0;
    FILE *fp = fopen("resource/Data/testAlphaBeta.txt","r");
    int count=0;
    xp = fopen("resource/Data/test.dot","w");
    for(int a=0;a<100;a++){
        int flag;
        for(int b=0;b<6;b++){
            for(int c=0;c<6;c++){
                fscanf(fp,"%d ",&flag);
                if(flag==2)
                    chessboard[b][c]=-1;
                else
                    chessboard[b][c]=flag;

            }
        }
        int index[7];
        int data[7];
        for(int a=0;a<7;a++){
            fscanf(fp,"%d",&index[a]);
        }

        Chessboard myboard(1,chessboard);

        int alpha=-INT_MAX,beta=INT_MAX;
        for(int a=1;a<=7;a++){
            int vl= myboard.alphaBeta(a,alpha,beta,-1);
            data[a-1]=-vl;
        }
        for(int e=0;e<7;e++){
            if(data[e]!=index[e]){
                count++;
                for(int c=0;c<6;c++){
                    for(int b=0;b<6;b++){
                        if(chessboard[c][b]==-1)
                            printf("2 ");
                        else
                            printf("%d ",chessboard[c][b]);
                    }
                    printf("\n");
                }
                for(int d=0;d<7;d++){
                    printf("depth=%d index=%d my=%d\n",d+1,index[d],data[d]);
                }
                break;
            }
        }
    }
    printf("Error_number=%d\n",count);
}