#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <colors.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>

#include "Struct.h"
#include "game_function.h"

#define Maxlen 10

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
    if(menu==1){
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
        /*char name1[Maxlen], name2[Maxlen];
        char garbage;
        scanf("%c", &garbage);
        printf("player one name:");
        fgets(name1, Maxlen, stdin);
        for(int s = 0, l = strlen(name1); s < l; s++)
        {
            if(name1[s] == ' ' || name1[s] == '\n')
                name1[s] = '\0';
            name1[s] = tolower(name1[s]);
        }
        strcpy(&one.name, name1);
        printf("%s", &one.name);
        if(mode == 2){
            printf("player two name:");
            fgets(name2, Maxlen, stdin);
            for(int s = 0, l = strlen(name2); s < l; s++)
            {
                if(name2[s] == ' ' || name2[s] == '\n')
                    name2[s] = '\0';
                name2[s] = tolower(name2[s]);
            }
        }else strcpy(name2,"computer");
        strcpy(&two.name, name2);
        printf("%s", &two.name);
        //system("cls");*/
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
        game_function(n, mode, size, game, totallines, movesplayed, noofmoves, player, one.score, two.score, one.moves, two.moves);
    }
    return 0;
}
