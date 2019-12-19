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
    menu = scanint();
    system("cls");
    users usersarray[MAXSIZE] = {0};
    FILE *userread = fopen("s.txt", "r");
    if(userread == NULL) {
        printf("users file does not exist\n");
        return(-1);
    }
    int counter = 0;
    while(!feof(userread))
    {
        fread(&usersarray[counter].namelen, sizeof(int), 1, userread);
        fread(&usersarray[counter].name,sizeof(char), usersarray[counter].namelen, userread);
        usersarray[counter].name[usersarray[counter].namelen] = '\0';
        fread(&usersarray[counter].score, sizeof(int), 1, userread);
        counter++;
    }
    fclose(userread);
    int n, mode;
    gamer one, two;
    int player;

    if(menu == 1){

            setTextColor(stdout,TC_CYAN);
            printf("\n\nenter the size of the boxes:");
            n = scanint();
            if(n == -1) return -1;
            setTextColor(stdout,TC_LIGHTGRAY);
            setTextColor(stdout,TC_BLUE);
            printf("\none player (enter:1):\n\n");
            setTextColor(stdout,TC_RED);
            printf("two player (enter:2):\n");
            setTextColor(stdout,TC_LIGHTGRAY);
            mode= scanint();
            if(mode == -1) return -1;
            system("cls");

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
            int size = 2*n + 2;
            char game[size][size];
            for(int j=0; j < size; j++){
                game[0][j] = j;
                game[j][0] = j;
                if(j%2 != 0) {
                    for(int i=1; i < size; i=i+2){
                        game[i][j] = 254; // dot
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
            player=1;
            player = game_function(n, mode, size, game, totallines, movesplayed, noofmoves, player, &one.score, &two.score, one.moves, two.moves,one.lenname, one.name, two.lenname, two.name);
        }
        if(menu == 2){
            int savenum;
            printf("Enter the file number( 1 or 2 or 3):");
            savenum= scanint();
            if(savenum == -1) return -1;
            if (savenum == 1 || savenum == 2 || savenum == 3){
                char fname[5];
                sprintf(fname, "%d.txt", savenum);
                FILE *load = fopen(fname, "r");
                if(load == NULL) {
                    printf("file does not exist\n");
                    return -1;
                }
                int n, mode;

                fread(&n, sizeof(int), 1, load);
                fread(&mode, sizeof(int), 1, load);

                int size = 2 * n +2, totallines = 2*n*(n+1), noofmoves;
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
                one.name[one.lenname] = '\0';
                if(mode == 2){
                    fread(&two.lenname, sizeof(int), 1, load);
                    fread(two.name, sizeof(char), two.lenname, load);
                    two.name[two.lenname] = '\0';
                }
                fclose(load);
                if (mode == 1)
                {
                    strcpy(&two.name, "computer");
                }
                two.lenname = strlen(&two.name);
                player = game_function(n, mode, size, game, totallines, movesplayed, noofmoves, player, &one.score, &two.score, one.moves, two.moves,one.lenname, one.name, two.lenname, two.name);
            } else printf("is not existing file\n");
        }
        if(menu == 1 || menu == 2)
        {
            if (player == 1){
                int i = 0, m = 0;
                while(usersarray[i].namelen != 0)
                    if(strcmp(one.name,usersarray[i].name) == 0){
                        m = 1;
                        break;
                    }else{
                        i++;
                        if(i == MAXSIZE)
                        {
                            for(int j = 0; j < MAXSIZE; j++)
                            {
                                usersarray[j].namelen = 0;
                            }
                            i = 0;
                        }
                    }
                if (m){
                    if(usersarray[i].score < one.score){
                        usersarray[i].score = one.score;
                    }
                }else{
                    usersarray[i].namelen = one.lenname;
                    strcpy(&usersarray[i].name,&one.name);
                    usersarray[i].score = one.score;
                }
            }else if (player == 2 && mode == 2){
                int i = 0, m = 0;
                while(usersarray[i].namelen != 0){
                    if(strcmp(two.name,usersarray[i].name) == 0){
                        m = 1;
                        break;
                    }else{
                        i++;
                    }
                }
                if (m){
                    usersarray[i].score = two.score;
                }else{
                    usersarray[i].namelen = two.lenname;
                    strcpy(&usersarray[i].name,&two.name);
                    usersarray[i].score = two.score;
                }
            }
            FILE *userwrite = fopen("s.txt", "w");
            counter = 0;
            while(counter < MAXSIZE && usersarray[counter].namelen != 0){
                fwrite(&usersarray[counter].namelen, sizeof(int), 1, userwrite);
                fwrite(&usersarray[counter].name,sizeof(char), usersarray[counter].namelen, userwrite);
                fwrite(&usersarray[counter].score, sizeof(int), 1, userwrite);
                counter++;
            }
            fclose(userwrite);
        }
        else if(menu == 3){
            sortusers(usersarray);int i,j;
            for(i=0;i<10;i++){
                printf("%d.",i+1);
                for(j=0;usersarray[i].name[j]!='\0';j++)
                    printf("%c",usersarray[i].name[j]);
                printf("\n");
            }
        }
        else
            printf("Wrong choose\n\n");
    return 0;
}
