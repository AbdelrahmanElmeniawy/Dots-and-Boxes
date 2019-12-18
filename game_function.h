#include "printgame.h"
#include "checkbox.h"
#include "AI_function.h"
#include "Undo_function.h"

void game_function(int n, int mode, int size, char game[size][size],int totallines, int movesplayed[totallines][7], int noofmoves, int player,int score1,int score2, int moves1, int moves2)
{
    time_t savedtime;
    int t0 = time(&savedtime);
    //initializing the arrays of the play
    int j, i;
    char h = 205, v = 186, dot = 254;//205 186 254
    char compgame[size][size];
    for(j=0; j < size; j++){
            compgame[0][j] = j;
            compgame[j][0] = j;
            if(j%2 != 0) {
                for(i=1; i < size; i=i+2){
                    compgame[i][j] = dot;
                    compgame[i+1][j] =v;
                }
            }
             else if(j%2 == 0){
                for(i=1; i < size; i = i+2){
                    compgame[i][j] = h;
                    compgame[i+1][j] =' ';
                }
            }
        }

    int row,col,gameon=1,availablemove=1,check = 0, AI, noundo = 0;
    printgame(size,game, score1, score2, totallines, noofmoves, moves1, moves2, t0);
    while(gameon){
        if(player==1){
            setTextColor(stdout,TC_BLUE);
        }
        else{
            setTextColor(stdout,TC_RED);
        }
        printf("\tplayer %d's turn\n\n",player);
        setTextColor(stdout,TC_LIGHTGRAY);
        if(player==2 && mode == 1){
            AI_function(&row , &col,size,game,compgame,player,totallines, noofmoves, movesplayed, v, h, dot);
        }
        else{
            if(player==1){
                setTextColor(stdout,TC_BLUE);
            }
            else{
                setTextColor(stdout,TC_RED);
            }
            printf("\tENTER ROW: ");
            scanf("%x",&row);
            printf(("\tENTER COL: "));
            scanf("%x",&col);
        }
        setTextColor(stdout,TC_LIGHTGRAY);
        system("cls");
        AI = 0;
        //undo
        if (row == 0 && col == 0)
        {
            if (noofmoves == 0)
                printf("\nno moves to undo\n\n");
            else if(movesplayed[noofmoves-1][0] != 0)
            {
                undo_function(mode,&noundo, &moves1, &moves2, &score1, &score1, &row,&col,size,game,compgame,&player,totallines, &noofmoves, movesplayed);
            }else
                printf("\nno moves to undo\n\n");
        }
        else if((((col%2 == 0 && row%2 != 0) || (col%2 != 0 && row%2 == 0)) && col > 0 && col < size && row > 0 && row < size) || (row == 1 && col == 1)){

                //redo
                if (row == 1 && col == 1){
                    if (noundo != 0){
                        row = movesplayed[noofmoves][0];
                        col = movesplayed[noofmoves][1];
                        player = movesplayed[noofmoves][2];
                        noundo--;
                    }else{
                        printf("\nno moves to redo\n\n");
                        printgame(size,game, score1, score2, totallines, noofmoves, moves1, moves2, t0);
                        continue;
                    }
                }else
                    if(mode == 2){
                        noundo = 0;
                    }else{
                        if(player == 1)
                            noundo = 0;
                    }
                    for(i=0; i < noofmoves; i++){
                        if(row == movesplayed[i][0] && col == movesplayed[i][1]){
                            availablemove = 0;
                            printf("\nnot available move\n\n");break;
                        }
                    }
                if(availablemove){
                    game[row][col]=compgame[row][col];
                    movesplayed[noofmoves][0]=row;
                    movesplayed[noofmoves][1]=col;
                    movesplayed[noofmoves][2]=player;
                    if(player == 1)
                        moves1++;
                    else
                        moves2++;
                    noofmoves++;
                    check = checkbox(row,col,size,game,compgame,player,totallines, noofmoves, movesplayed, AI);
                    if(check){
                        if(player == 1) score1+=check;
                        else score2+=check;
                        check = 0;
                    }
                    else{
                        if(player==1)player=2;
                        else player=1;
                    }
                }
                else availablemove = 1;
            }
        else printf("\nnot available move\n\n");

        printgame(size,game, score1, score2, totallines, noofmoves, moves1, moves2, t0);

        //endgame
        if(noofmoves == totallines){
            gameon = 0;
            printf("GAME ENDED\n");
            if(score1 > score2){
                setTextColor(stdout,TC_BLUE);
                printf("Player 1 win");
                setTextColor(stdout,TC_LIGHTGRAY);
            }
            else if(score2 > score1){
                setTextColor(stdout,TC_RED);
                printf("Player 2 win");
                setTextColor(stdout,TC_LIGHTGRAY);
            }
            else{
                printf("Tie");
            }
        }
    }
}
