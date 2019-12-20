#include "printgame.h"
#include "checkbox.h"
#include "AI_function.h"
#include "Undo_function.h"
#include "scanint.h"

void sortusers ( users list[MAXSIZE]) { // sort the user according to score used in displaying top 10
int i, j; users temp;
for(i = 0; i < MAXSIZE-1; i++){
    for(j = 0; j < MAXSIZE-1-i; j++)
        if(list[j].score < list[j+1].score){ //descending way
            temp = list[j];
            list[j] = list[j+1];
            list[j+1] = temp;
        }
    }
}

//this function return the player number to determine which player we will  save him name
int game_function(int n, int mode, int size, char game[size][size],int totallines, int movesplayed[totallines][7], int noofmoves, int player,int *score1,int *score2, int moves1, int moves2, int lenname1, char name1[lenname1], int lenname2, char name2[lenname2])
{
    time_t savedtime;
    int t0 = time(&savedtime);
    //initializing the arrays of complete game
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

    int row,col,gameon=1,availablemove=1,check = 0, AI, noundo = 0; //check ----- check the box
    printgame(size,game, *score1, *score2, totallines, noofmoves, moves1, moves2, t0, name1, name2, movesplayed);
    while(gameon){
        printf("\tenter number of row and column by hexadecimal digits\nenter 0, 0 for undo\t1, 1 for redo\t 2, 2 for save\t 3, 3 for main menu\n");
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
            row = scanint();
            printf(("\tENTER COL: "));
            col = scanint();
        }
        setTextColor(stdout,TC_LIGHTGRAY);
        system("cls");

        AI = 0;
        //undo
        if (row == 0 && col == 0)//undo
        {
            if (noofmoves == 0)
                printf("\nno moves to undo\n\n");
            else if(movesplayed[noofmoves-1][0] != 0)
            {
                undo_function(mode,&noundo, &moves1, &moves2, score1, score2, &row,&col,size,game,compgame,&player,totallines, &noofmoves, movesplayed);
            }else
                printf("\nno moves to undo\n\n");
        }

        else if (row == 3 && col == 3){//if user want to return to main menu
            player =0;
            return player;
        }

        else if (row == 2 && col == 2)//save game
        {
            int savenum;
            printf("Enter the file number( 1 or 2 or 3):");
            while(1){
                savenum = scanint();
                if (savenum == 1 || savenum == 2 || savenum == 3){
                    char fname[5];
                    sprintf(fname, "%d.txt", savenum);
                    FILE *save = fopen(fname, "w");
                    fwrite(&n, sizeof(int), 1, save);
                    fwrite(&mode, sizeof(int), 1, save);
                    fwrite(&noofmoves, sizeof(int), 1, save);
                    fwrite(&moves1, sizeof(int), 1, save);
                    fwrite(&moves2, sizeof(int), 1, save);
                    fwrite(score1, sizeof(int), 1, save);
                    fwrite(score2, sizeof(int), 1, save);
                    fwrite(&player, sizeof(int), 1, save);
                    fwrite(movesplayed, sizeof(int), totallines * 7, save);
                    fwrite(game, sizeof(char), size * size, save);
                    fwrite(&lenname1, sizeof(int), 1, save);
                    fwrite(name1, sizeof(char), lenname1, save);
                    if(mode == 2)
                        fwrite(&lenname2, sizeof(int), 1, save);
                        fwrite(name2, sizeof(char), lenname2, save);
                    fclose(save);
                    printf("saved to %d.txt\n", savenum);
                    printgame(size,game, *score1, *score2, totallines, noofmoves, moves1, moves2, t0, name1, name2, movesplayed);
                    break;
                } else {    //if user choose to save in a wrong number return to game
                printf("is not existing file\n");}
            }
            continue;
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
                        printgame(size,game, *score1, *score2, totallines, noofmoves, moves1, moves2, t0, name1, name2, movesplayed);
                        continue;
                    }
                }else
                    if(mode == 2){
                        noundo = 0;
                    }else{
                        if(player == 1)
                            noundo = 0;
                    }

                    //check if we played this move before
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
                        if(player == 1) *score1 += check;
                        else *score2 += check;
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

        printgame(size,game, *score1, *score2, totallines, noofmoves, moves1, moves2, t0, name1, name2, movesplayed);

        //endgame
        if(noofmoves == totallines){
            gameon = 0;
            printf("GAME ENDED\n");
            if(*score1 > *score2){
                setTextColor(stdout,TC_BLUE);
                printf("%s win", name1);
                setTextColor(stdout,TC_LIGHTGRAY);
                player = 1;
            }
            else if(*score2 > *score1){
                setTextColor(stdout,TC_RED);
                printf("%s win", name2);
                setTextColor(stdout,TC_LIGHTGRAY);
                player = 2;
            }
            else{
                printf("Tie");
                player = 0;
            }
            return player;
        }
    }
}
