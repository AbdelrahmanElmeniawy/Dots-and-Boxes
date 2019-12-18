void undo_function(int mode,int *noundo, int *moves1, int *moves2, int *score1, int *score2, int *row,int *col,int size,char game[size][size],char compgame[size][size],int *player,int totallines, int *moves, int movesplayed[totallines][7])
{
    int noofmoves = *moves;
    if(mode == 2)
    {
        game[movesplayed[noofmoves-1][0]][movesplayed[noofmoves-1][1]] = ' ';
        if(movesplayed[noofmoves-1][2] == 1){
                *moves1 -= 1;
        }else *moves2 -= 1;
        *player = movesplayed[noofmoves-1][2];
        if(movesplayed[noofmoves-1][3] != 0){
            game[movesplayed[noofmoves-1][3]][movesplayed[noofmoves-1][4]] = ' ';
            *player == 1? *score1-- : *score2--;
        }
        if(movesplayed[noofmoves-1][5] != 0){
            game[movesplayed[noofmoves-1][5]][movesplayed[noofmoves-1][6]] = ' ';
            *player == 1? *score1-- : *score2--;
        }
        *noundo += 1;
        noofmoves -= 1;
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
                    *score1 -= 1;
                }
                if(movesplayed[noofmoves-1][5] != 0){
                    game[movesplayed[noofmoves-1][5]][movesplayed[noofmoves-1][6]] = ' ';
                    *score1 -= 1;
                }
                *moves1 -= 1;
                *noundo += 1;
                noofmoves -= 1;
                *player = 1;
                break;
            }
            else
            {
                game[movesplayed[noofmoves-1][0]][movesplayed[noofmoves-1][1]] = ' ';
                if(movesplayed[noofmoves-1][3] != 0){
                    game[movesplayed[noofmoves-1][3]][movesplayed[noofmoves-1][4]] = ' ';
                    *score2 -= 1;
                }
                if(movesplayed[noofmoves-1][5] != 0){
                    game[movesplayed[noofmoves-1][5]][movesplayed[noofmoves-1][6]] = ' ';
                    *score2 -= 1;
                }
                *moves2 -= 1;
                noofmoves -= 1;
            }
        }
    }
    *moves = noofmoves;
}
