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
