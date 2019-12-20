
int scanint(){//function to read int to avoid error when entering char it accepts the hexadecimal numbers
    char readstr[MAXSIZE];
    int  i, len;
    int readint=0, w;
    gets(readstr);
    len = strlen(readstr);
    for(i=0; i < len; i++){
        if(readstr[i] > 47 && readstr[i] < 58){ // 0 - 9
            w = readstr[i]- 48;
        }
        else if (readstr[i] > 96 && readstr[i] < 103){ //a - f         a = 10
            w = readstr[i]- 87;
        }
        else{
            return -1;
        }
        readint = readint*16+ w; //hexadecimal
    }
    return readint;
}
