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

