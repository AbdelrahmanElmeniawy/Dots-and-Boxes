void AI_function(int *row,int *col,int size,char game[size][size],char compgame[size][size],int player,int totallines, int noofmoves, int movesplayed[totallines][7], int v, int h, int dot)
{
    int s=0, i1,j1,u=0,notuserwin, AI = 1, i, j, check;
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
        if(s) break;
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
            if (bug) break;
        }
    }
    *row = i; *col = j;
}

