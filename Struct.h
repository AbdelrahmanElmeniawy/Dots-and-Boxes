#define MAXSIZE 256

typedef struct{
    char name[MAXSIZE];
    int moves;
    int score;
    int lenname;
}gamer;

typedef struct{
    int namelen;
    char name[MAXSIZE];
    int score;
}users;
