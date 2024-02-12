#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char **secBoard,**playBoard;
unsigned length, width, perbomb;

void makeArray(void){
    int i;
    secBoard = calloc(length, sizeof(char *));
    playBoard = calloc(length, sizeof(char *));
    for(i=0;i<length;i++){
        secBoard[i] = calloc(width, sizeof(char) );
        playBoard[i] = calloc(width, sizeof(char) );
    }
}

void deleteArray(void){
    for(int i=0;i<length;i++){
        free(secBoard[i]);
        free(playBoard[i]);
    }
    free(secBoard);
    free(playBoard);
}

void makesecBoard(int l,int w){
    int i,j,bombMax,lbomb,wbomb,num=0,x,y;
    srand((unsigned)time(NULL));
    bombMax=(width*length)*perbomb/100;
    for(i=0; i<length; i++){
        for(j=0; j<width; j++) secBoard[i][j]='-';
    }
    while(bombMax>num){
        lbomb = rand()%length;
        wbomb = rand()%width;
        if(secBoard[lbomb][wbomb]!='*' && lbomb!=l && wbomb!=w){
            secBoard[lbomb][wbomb]='*';
            num++;
        }
    }
    for(i=0; i<length; i++){
        for(j=0; j<width; j++){
            if(secBoard[i][j]=='-'){
                secBoard[i][j]='0';
                if(i-1>=0 && j-1>=0 && secBoard[i-1][j-1]=='*') secBoard[i][j]++;
                if(i-1>=0 && secBoard[i-1][j]=='*') secBoard[i][j]++;
                if(i-1>=0 && j+1<width && secBoard[i-1][j+1]=='*') secBoard[i][j]++;
                if(j-1>=0 && secBoard[i][j-1]=='*') secBoard[i][j]++;
                if(j+1<width && secBoard[i][j+1]=='*') secBoard[i][j]++;
                if(i+1<length && j-1>=0 && secBoard[i+1][j-1]=='*') secBoard[i][j]++;
                if(i+1<length && secBoard[i+1][j]=='*') secBoard[i][j]++;
                if(i+1<length && j+1<width && secBoard[i+1][j+1]=='*') secBoard[i][j]++;
                if(secBoard[i][j]=='0') secBoard[i][j]='-';
            }
        }
    }
}

void Open(int l,int w){
    int i,j;
    if(l<0 || l>length-1 || w<0 || w>width-1) return;
    if(playBoard[l][w]!=' ') return;
    playBoard[l][w]=secBoard[l][w];
    if(playBoard[l][w]=='-'){
        for(i=-1; i<2; i++){
            for(j=-1; j<2; j++){
                Open(l+i,w+j);
            }
        }
    }
    return;
}

void makeplayBoard(int l,int w,char f){
    int i,j;
    static int a=0;
    if(a==0){
        for(i=0; i<length; i++){
            for(j=0; j<width; j++){
                if(playBoard[i][j]!='f') playBoard[i][j]=' ';
            }
        }
        a++;
    }
    if(f=='f'){
        if(playBoard[l][w]!='f') playBoard[l][w]='f';
        else playBoard[l][w]=' ';
    }else if(f=='o' || playBoard[l][w]!='f'){
        Open(l,w);
    }
}

void printsecBoard(void){
    int i,j;
    printf("   ");
    for(i=0;i<width;i++) printf("%1d ",i);
    printf("\n");
    for(i=0;i<length;i++){
        printf("%2d",i);
        for(j=0;j<width;j++) printf("|%c",secBoard[i][j]);
        printf("|\n");
    }
    printf("\n");
}

void printplayBoard(void){
    int i,j;
    printf("   ");
    for(i=0;i<width;i++) printf("%1d ",i);
    printf("\n");
    for(i=0;i<length;i++){
        printf("%2d",i);
        for(j=0;j<width;j++) printf("|%c",playBoard[i][j]);
        printf("|\n");
    }
    printf("\n");
}

int IsClear(void){
    int i,j,a=0,b=0;
    for(i=0; i<length; i++){
        for(j=0; j<width; j++){
            if(playBoard[i][j]==' ') a++;
            if(secBoard[i][j]=='*') b++;
        }
    }
    if(a==b) return 0;
    return 1;
}

int main(void){
    int l,w;
    char f;
    printf("縦 横 割合(%%)--> ");
    scanf("%d %d %d",&length,&width,&perbomb);
    printf("\n");
    makeArray();
    printplayBoard();
    printf("(縦 横) o or f--> ");
    scanf("%d %d %c",&l,&w,&f);
    if(f=='f'){
        do{
            printf("(縦 横) o or f--> ");
            scanf("%d %d %c",&l,&w,&f);
        }while(f=='o');
    }
    printf("\n");
    makesecBoard(l,w);
    makeplayBoard(l,w,f);
    do{
        printplayBoard();
        printf("(縦 横) o or f --> ");
        scanf("%d %d %c",&l,&w,&f);
        printf("\n");
        makeplayBoard(l,w,f);
        if(playBoard[l][w]=='*'){
            printsecBoard();
            printf("--!Game Over!--\n");
            exit(-1);
        }
    }while(IsClear());
    printplayBoard();
    printf("--!Game Clear!--\n");
    deleteArray();
}