#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <colors.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>

#include "Struct.h"
#include "game_function.h"

int main()
{
    int menu;
    setTextColor(stdout,TC_GREEN);
    printf("\n \t \t\t\t\twelcome to our project:\n\n \t \t\t\t\tDOTS and BOXES:\n\n");
    setTextColor(stdout,TC_CYAN);
    printf("\t new game(enter:1):\n\n\t load(enter:2):\n\n\t top ten(enter:3):\n\n\t exit(enter:4);\n\n\t enter the choose:");
    setTextColor(stdout,TC_LIGHTGRAY);
    scanf("%d",&menu);
    system("cls");
    if(menu == 1){
            int n, mode;
            setTextColor(stdout,TC_CYAN);
            printf("\n\nenter the size of the boxes:");
            scanf("%d",&n);
            setTextColor(stdout,TC_LIGHTGRAY);
            setTextColor(stdout,TC_BLUE);
            printf("\none player (enter:1):\n\n");
            setTextColor(stdout,TC_RED);
            printf("two player (enter:2):\n");
            setTextColor(stdout,TC_LIGHTGRAY);
            scanf("%d",&mode);
            system("cls");
            gamer one, two;
            setTextColor(stdout,TC_BLUE);
            printf(" enter your name: ");
            fflush(stdin);
            gets(&one.name);
            strlwr(&one.name);
            one.lenname = strlen(&one.name);
            setTextColor(stdout,TC_LIGHTGRAY);
            if(mode == 2){
                setTextColor(stdout,TC_RED);
                printf("enter the secand name: ");
                fflush(stdin);
                gets(&two.name);
                strlwr(&two.name);
                setTextColor(stdout,TC_LIGHTGRAY);
            }else strcpy(&two.name, "computer");
            two.lenname = strlen(&two.name);
            system("cls");
            printf("%d", one.lenname);
            int size = 2*n + 2;
            char game[size][size];
            for(int j=0; j < size; j++){
                game[0][j] = j;
                game[j][0] = j;
                if(j%2 != 0) {
                    for(int i=1; i < size; i=i+2){
                        game[i][j] = 254;
                        game[i+1][j] =' ';
                    }
                }
                 else if(j%2 == 0){
                    for(int i=1; i < size; i = i+2){
                        game[i][j] =' ';
                        game[i+1][j] =' ';
                    }
                }
            }
            int totallines = 2*n*(n+1),noofmoves=0;
            int movesplayed[totallines][7];//movesplayed[no of move][player played it,row,column]
            for(int i=0;i<totallines;i++){
                for(int j=0; j < 7; j++)
                    movesplayed[i][j]=0;
            }
            one.score=0; two.score=0; one.moves= 0; two.moves = 0;
            int player=1;
            game_function(n, mode, size, game, totallines, movesplayed, noofmoves, player, one.score, two.score, one.moves, two.moves,one.lenname, one.name, two.lenname, two.name);
        }
        else if(menu == 2){
            int savenum;
            printf("Enter the file number( 1 or 2 or 3):");
            scanf("%d", &savenum);
            if (savenum == 1 || savenum == 2 || savenum == 3){
                char fname[5];
                sprintf(fname, "%d.txt", savenum);
                FILE *load = fopen(fname, "r");

                int n, mode;

                fread(&n, sizeof(int), 1, load);
                fread(&mode, sizeof(int), 1, load);

                int size = 2 * n +2, totallines = 2*n*(n+1), noofmoves, player;
                fread(&noofmoves, sizeof(int), 1, load);

                gamer one, two;
                fread(&one.moves, sizeof(int), 1, load);
                fread(&two.moves, sizeof(int), 1, load);
                fread(&one.score, sizeof(int), 1, load);
                fread(&two.score, sizeof(int), 1, load);
                fread(&player, sizeof(int), 1, load);

                int movesplayed[totallines][7];
                fread(movesplayed, sizeof(int), totallines * 7, load);

                char game[size][size];
                fread(game, sizeof(char), size * size, load);

                fread(&one.lenname, sizeof(int), 1, load);
                fread(one.name, sizeof(char), one.lenname, load);
                if(mode == 2)
                    fread(&two.lenname, sizeof(int), 1, load);
                    fread(two.name, sizeof(char), two.lenname, load);
                fclose(load);
                if (mode == 1)
                {
                    strcpy(&two.name, "computer");
                }
                two.lenname = strlen(&two.name);
                game_function(n, mode, size, game, totallines, movesplayed, noofmoves, player, one.score, two.score, one.moves, two.moves,one.lenname, one.name, two.lenname, two.name);
            } else printf("is not existing file\n");
        }
        else
            printf("Wrong choose\n");
    return 0;
}
