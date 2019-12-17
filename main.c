#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <colors.h>
#include <windows.h>

int checkbox(int row,int col,int size,char game[size][size],char compgame[size][size],int player,int totallines, int noofmoves, int movesplayed[totallines][7], int ai);
void printgame(int sizea, char game[sizea][sizea], int score1, int score2, int totallines, int noofmoves, int noOfMoves1, int noOfMoves2, int time0);



int main()
{
    int n ;
    //////////////////////////////////////////////////////////////////// interfacee
    int i,mode;
    setTextColor(stdout,TC_GREEN);
    printf("\n \t \t\t\t\twelcome to our project:\n\n \t \t\t\t\tDOTS and BOXES:\n\n");
    setTextColor(stdout,TC_CYAN);
    printf("\t new game(enter:1):\n\n\t load(enter:2):\n\n\t top ten(enter:3):\n\n\t exit(enter:4);\n\n\t enter the choose:");
    setTextColor(stdout,TC_LIGHTGRAY);
    scanf("%d",&i);
    system("cls");
    if(i==1){
    setTextColor(stdout,TC_CYAN);
    printf("\n\nenter the size of the boxes:");
    scanf("%d",&n);
    setTextColor(stdout,TC_LIGHTGRAY);
    //system("cls");
    setTextColor(stdout,TC_BLUE);
    printf("\n\tone player (enter:1):\n\n");
    setTextColor(stdout,TC_RED);
    printf("\ttwo player (enter:2):\n");
    setTextColor(stdout,TC_LIGHTGRAY);
    scanf("%d",&mode);
    system("cls");
    time_t savedtime;
    int t0 = time(&savedtime);
    //initializing the arrays of the play
    int j, i, size = 2*n+2;
    char h = 205, v = 186, dot = 254;//205 186 254
    char compgame[size][size];
    char game[size][size];
    for(j=0; j < size; j++){
        compgame[0][j] = j;
        game[0][j] = j;
        compgame[j][0] = j;
        game[j][0] = j;
        if(j%2 != 0) {
            for(i=1; i < size; i=i+2){
                compgame[i][j] = dot;
                game[i][j] = dot;
                compgame[i+1][j] =v;
                game[i+1][j] =' ';
            }
        }
         else if(j%2 == 0){
            for(i=1; i < size; i = i+2){
                compgame[i][j] = h;
                compgame[i+1][j] =' ';
                game[i][j] =' ';
                game[i+1][j] =' ';
            }
        }
        }

    //array 0f moves and make it = 0
    int totallines = 2*n*(n+1),noofmoves=0, noundo = 0;
    int movesplayed[totallines][7];//movesplayed[no of move][player played it,row,column]
    for(i=0;i<totallines;i++){
        for(j=0; j < 7; j++)
            movesplayed[i][j]=0;
    }
    int row,col,gameon=1,availablemove=1,player=1,score1=0,score2=0,check = 0, moves1 = 0, moves2 = 0, AI;
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
            int s=0, AI = 1, i1,j1,u=0,notuserwin;
            ////////
            for(i=1;i<size;i++){
                for(j=1;j<size;j++){
                    if(game[i][j]==' '&&(compgame[i][j]== v ||compgame[i][j]==h)){
                        game[i][j]=compgame[i][j];
                        check=checkbox(i,j,size,game,compgame,player,totallines, noofmoves, movesplayed, AI);
                        if(check==1||check==2){
                            s=1;
                            break;
                        }
                        else{
                            game[i][j]=' ';
                        }
                    }
                }
                if(s)
                    break;
            }
            if(s==0){
                for(i=1; i<size;i++){
                    for(j=1; j<size ; j++){
                        if(game[i][j]==' '&&(compgame[i][j]== v ||compgame[i][j]==h)){
                            game[i][j]=compgame[i][j];
                            notuserwin=1;u=0;
                            for(i1=1;i1<size;i1++){
                                for(j1=1;j1<size;j1++){
                                    if(game[i1][j1]==' '&&(compgame[i1][j1]== v ||compgame[i1][j1]==h)){
                                        game[i1][j1]=compgame[i1][j1];
                                        check=checkbox(i1,j1,size,game,compgame,player,totallines, noofmoves, movesplayed, AI);
                                        if(check==1||check==2){
                                            game[i][j]=' ';
                                            game[i1][j1]=' ';
                                            u=1;
                                            notuserwin=0;
                                            break;
                                        }
                                        else game[i1][j1]=' ';
                                    }
                                }
                                if(u) break;
                            }
                            if(notuserwin){s=1; break;}
                        }
                    }
                    if(s) break;
                }
            }
            if(s == 0){
                for(i = 1; i < size; i++){
                    int bug = 0;
                    for(j = 1; j < size; j++){
                        if(game[i][j] == ' ' && (compgame[i][j] == v || compgame[i][j]== h)){
                            bug = 1;
                            break;
                        }
                    }
                    if (bug){
                        break;
                    }
                }
            }
            row = i; col = j;
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
                if(mode == 2)
                {
                    game[movesplayed[noofmoves-1][0]][movesplayed[noofmoves-1][1]] = ' ';
                    if(movesplayed[noofmoves-1][2] == 1){
                        moves1--;
                    }else moves2--;
                    player = movesplayed[noofmoves-1][2];
                    if(movesplayed[noofmoves-1][3] != 0){
                        game[movesplayed[noofmoves-1][3]][movesplayed[noofmoves-1][4]] = ' ';
                        player == 1? score1-- : score2--;
                    }
                    if(movesplayed[noofmoves-1][5] != 0){
                        game[movesplayed[noofmoves-1][5]][movesplayed[noofmoves-1][6]] = ' ';
                        player == 1? score1-- : score2--;
                    }
                    noundo++;
                    noofmoves--;
                }
                else
                {
                    while(1)
                    {
                        if(movesplayed[noofmoves-1][2] == 1)
                        {
                            game[movesplayed[noofmoves-1][0]][movesplayed[noofmoves-1][1]] = ' ';
                            if(movesplayed[noofmoves-1][3] != 0){
                                game[movesplayed[noofmoves-1][3]][movesplayed[noofmoves-1][4]] = ' ';
                                score1--;
                            }
                            if(movesplayed[noofmoves-1][5] != 0){
                                game[movesplayed[noofmoves-1][5]][movesplayed[noofmoves-1][6]] = ' ';
                                score1--;
                            }
                            moves1--;
                            noundo++;
                            noofmoves--;
                            player = 1;
                            break;
                        }
                        else
                        {
                            game[movesplayed[noofmoves-1][0]][movesplayed[noofmoves-1][1]] = ' ';
                            if(movesplayed[noofmoves-1][3] != 0){
                                game[movesplayed[noofmoves-1][3]][movesplayed[noofmoves-1][4]] = ' ';
                                score2--;
                            }
                            if(movesplayed[noofmoves-1][5] != 0){
                                game[movesplayed[noofmoves-1][5]][movesplayed[noofmoves-1][6]] = ' ';
                                score2--;
                            }
                            moves2--;
                            noofmoves--;
                        }
                    }
                }
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
    return 0;
}

int checkbox(int row,int col,int size,char game[size][size],char compgame[size][size],int player,int totallines, int noofmoves, int movesplayed[totallines][7], int ai)
{
    int check =0;
    if(row%2==0){
        if(col+2<size){
        if(game[row+1][col+1]==compgame[row+1][col+1]){
            if(game[row][col+2]==compgame[row][col+2]){
                if(game[row-1][col+1]==compgame[row-1][col+1]){
                   if(ai == 0){
                   if(player==1){
                    game[row][col+1]='A';
                   }
                   else if(player==2){
                    game[row][col+1]='B';
                   }
                   movesplayed[noofmoves-1][3] = row;
                   movesplayed[noofmoves-1][4] = col+1;
                   }
                   check++;
                }
            }
        }
        }
        if(col-2>0){
        if(game[row+1][col-1]==compgame[row+1][col-1]){
            if(game[row][col-2]==compgame[row][col-2]){
                if(game[row-1][col-1]==compgame[row-1][col-1]){
                   if(ai == 0){
                   if(player==1){
                    game[row][col-1]='A';
                   }
                   else if(player==2){
                    game[row][col-1]='B';
                   }
                   movesplayed[noofmoves-1][5] = row;
                   movesplayed[noofmoves-1][6] = col-1;
                   }check++;
                }
            }
        }
        }
    }
    else if(col%2==0){
        if(row+2<size){
        if(game[row+1][col+1]==compgame[row+1][col+1]){
            if(game[row+2][col]==compgame[row+2][col]){
                if(game[row+1][col-1]==compgame[row+1][col-1]){
                   if(ai == 0){
                   if(player==1){
                    game[row+1][col]='A';
                   }
                   else if(player==2){
                    game[row+1][col]='B';
                   }
                movesplayed[noofmoves-1][3] = row+1;
                movesplayed[noofmoves-1][4] = col;
                   }check++;
                }
            }
        }
        }
        if(row-2>0){
        if(game[row-1][col+1]==compgame[row-1][col+1]){
            if(game[row-2][col]==compgame[row-2][col]){
                if(game[row-1][col-1]==compgame[row-1][col-1]){
                   if(ai == 0){
                   if(player==1){
                    game[row-1][col]='A';
                   }
                   else if(player==2){
                    game[row-1][col]='B';
                   }
                   movesplayed[noofmoves-1][5] = row-1;
                   movesplayed[noofmoves-1][6] = col;
                   }check++;
                }
            }
        }
        }
    }
    return check;
}

void printgame(int sizea, char game[sizea][sizea], int score1, int score2, int totallines, int noofmoves, int noOfMoves1, int noOfMoves2, int time0)
{
    setTextColor(stdout,TC_WHITE);
    time_t currenttime;
    int current = time(&currenttime);
    int seconds = (current - time0) % 60, minutes = (current - time0) / 60;
    int i, j;
    printf("  ");
    for(i=1;i<sizea;i++){
        printf("%x",game[0][i]);
        if(i < 16)
            printf(" ");
    }
    printf("\n");
    for(i=1;i<sizea;i++){
        if(i < 16)
            printf(" ");
        printf("%x",game[i][0]);
        for(j=1;j<sizea;j++)
            if(game[i][j] == 'A'){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_BLUE);
                printf("   ");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED| FOREGROUND_INTENSITY);
            }
            else if(game[i][j] == 'B'){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_RED);
                printf("   ");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED| FOREGROUND_INTENSITY );
            }
            else if (j%2 == 0)
                printf("%c%c%c",game[i][j],game[i][j],game[i][j]);
            else printf("%c", game[i][j]);
        printf("\n");
    }printf("\n");
    setTextColor(stdout,TC_BLUE);
    printf("    Number of moves for player 1: %d",noOfMoves1);
    setTextColor(stdout,TC_RED);
    printf("\t\t\t Number of moves for player 2: %d\n\n", noOfMoves2);
    setTextColor(stdout,TC_BLUE);
    printf("    player 1's score = %d",score1);
    setTextColor(stdout,TC_RED);
    printf("\t\t\t\t player 2's score = %d\n\n",score2);
    setTextColor(stdout,TC_YELLOW);
    printf("    Number of remaining lines: %d\t\t\t time passed: %.2d:%.2d\n\n", totallines - noofmoves, minutes, seconds);
    setTextColor(stdout,TC_LIGHTGRAY);
}
