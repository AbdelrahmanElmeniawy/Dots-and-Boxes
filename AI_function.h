void AI_function(int *row,int *col,int size,char game[size][size],char compgame[size][size],int player,int totallines, int noofmoves, int movesplayed[totallines][7], int v, int h, int dot)
{
    int foundgoodmove=0, i1,j1, AI = 1, i, j, check;
    for(i=1; i<size; i++)
    {
        for(j=1; j<size; j++)
        {
            if(game[i][j]==' '&&(compgame[i][j]== v ||compgame[i][j]==h))
            {
                game[i][j]=compgame[i][j];
                check=checkbox(i,j,size,game,compgame,player,totallines, noofmoves, movesplayed, AI);
                if(check==1||check==2) //found a move that close a box
                {
                    foundgoodmove=1;
                    break;
                }
                else
                {
                    game[i][j]=' ';
                }
            }
        }
        if(foundgoodmove)
            break;
    }
    if(foundgoodmove==0) //couldn't found a move that close a box but try not to help the user with a bad move
    {
        for(i=1; i<size; i++)
        {
            for(j=1; j<size ; j++)
            {
                if(game[i][j]==' '&&(compgame[i][j]== v ||compgame[i][j]==h)) //trying a move
                {
                    game[i][j]=compgame[i][j];
                    int notuserhelper=1, willhelpuser=0;
                    for(i1=1; i1<size; i1++)
                    {
                        for(j1=1; j1<size; j1++)
                        {
                            if(game[i1][j1]==' '&&(compgame[i1][j1]== v ||compgame[i1][j1]==h)) //see if this move help a user close a box
                            {
                                game[i1][j1]=compgame[i1][j1];
                                check=checkbox(i1,j1,size,game,compgame,player,totallines, noofmoves, movesplayed, AI);
                                if(check==1||check==2)
                                {
                                    game[i][j]=' ';
                                    game[i1][j1]=' ';
                                    willhelpuser=1;
                                    notuserhelper=0;
                                    break;
                                }
                                else
                                    game[i1][j1]=' ';
                            }
                        }
                        if(willhelpuser)
                            break;
                    }
                    if(notuserhelper)
                    {
                        foundgoodmove=1;
                        break;
                    }
                }
            }
            if(foundgoodmove)
                break;
        }
    }
    if(foundgoodmove == 0) //all moves will help the user close a box so choose any move
    {
        for(i = 1; i < size; i++)
        {
            int anymove = 0;
            for(j = 1; j < size; j++)
            {
                if(game[i][j] == ' ' && (compgame[i][j] == v || compgame[i][j]== h))
                {
                    anymove = 1;
                    break;
                }
            }
            if (anymove)
                break;
        }
    }
    *row = i;
    *col = j;
}

