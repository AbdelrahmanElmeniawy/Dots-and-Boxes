
int scanint(){
    char readstr[MAXSIZE];
    int  i, len;
    int readint=0, w;
    gets(readstr);
    len = strlen(readstr);
    for(i=0; i < len; i++){
        if(readstr[i] > 47 && readstr[i] < 58){
            w = readstr[i]- 48;
        }
        else if (readstr[i] > 96 && readstr[i] < 103){
            w = readstr[i]- 87;
        }
        else{
            return -1;
        }
        readint = readint*16+ w;
    }
    return readint;
}
