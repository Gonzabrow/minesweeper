#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char field[4][13];/*field ni card deteru(1) ka detenai(0) ka*/

typedef struct{
	char suit;
	int num;
}Card;

typedef struct{
	int pass;
	int handMax;
	char name[2];
	Card hand[52];
	int isAlive;
}Player;

void shuffleCards(Card deck[52]){
	int i,j=0;
	Card tmp;
	srand((unsigned)time(NULL));
	
	for(i=0; i<52; i++){
		j=rand()%52;
		tmp=deck[i];
		deck[i]=deck[j];
		deck[j]=tmp;
	}
}

void sortCards(Card hand[],int pnum){
	int i,j=0;
	Card tmp;
	int c=0;
	char suit[]={'S','H','D','C'};
	for(i=0; i<4; i++){
		while(j<52/pnum){
			if(hand[j].suit==suit[i]){
				tmp=hand[c];
				hand[c]=hand[j];
				hand[j]=tmp;
				c++;
			}
			j++;
		}
		j=0;
	}
	//num no sort wakarisoude wakarimasenn!! nemui node nemasu!!
	//i->suit j->suit no kazu ruikei desu! mirai no zibunn atoha makaseta! ganbare---
	int a,b;
	c=0;
	for(i=0; i<4; i++){
		c=j;
		while(hand[j].suit==suit[i]){
			j++;
		}
		for(a=c; a<j-1; a++){
			for(b=a+1; b<j; b++){
				if(hand[a].num>hand[b].num){
					tmp=hand[a];
					hand[a]=hand[b];
					hand[b]=tmp;
				}
			}
		}
	}
}

void printField(Card deck[]){
	char suit[]={'S','H','D','C'};
	int i,j,c=0;
	printf(" ");
	for(i=1; i<14; i++) printf(" %3d",i);
	printf("\n");
	for(i=0; i<4; i++){
		printf("%c",suit[i]);
		for(j=0; j<13; j++){
			if(field[i][j]==1) printf(" %c%2d",suit[i],j+1);
			else printf("    ");
			c++;
		}
		printf("\n");
	}
}

void putCard(Player* p,int num){
	if(p->hand[num].suit=='S' ) field[0][p->hand[num].num-1]=1;
	if(p->hand[num].suit=='H') field[1][p->hand[num].num-1]=1;
	if(p->hand[num].suit=='D') field[2][p->hand[num].num-1]=1;
	if(p->hand[num].suit=='C') field[3][p->hand[num].num-1]=1;
	//hand kara dasita card kesitai yo------
	for(int i=num; i+1 < p->handMax; i++){
		p->hand[i]=p->hand[i+1];
	}
	p->handMax--;
}

/*int IsGameFinish(){
	
}*/

int main(void){
	Card deck[52];
	Player player[8];
	int i,j;
	int playerNum;
	int p;
	int passMax;
	
	char yn;
	
	/*field data set*/
	for(i=0; i<4; i++){
		for(j=0; j<13; j++){
			field[i][j]=0;
		}
	}
		
	/*trump tukuru--*/
	for(i=0; i<13; i++){
		deck[i].suit='S';
		deck[i+13].suit='H';
		deck[i+26].suit='D';
		deck[i+39].suit='C';
		
		deck[i].num=i+1;
		deck[i+13].num=i+1;
		deck[i+26].num=i+1;
		deck[i+39].num=i+1;
	}
	
	/*player num scanf*/
	printf("num of player -> ");
	scanf("%d",&playerNum);

	/*passMax scanf*/
	printf("pass max num -> ");
	scanf("%d",&passMax);

	
	/*player name scanf*/
	for(i=0; i<playerNum; i++){
		printf("player%d name -> ",i+1);
		scanf("%s",&player[i].name);
	}
	
	/*player alive set*/
	for(i=0; i<playerNum; i++){
		player[i].isAlive=0; // 1 gameover
	}
	
	/*trump kubaru*/
	shuffleCards(deck);
	int k=0;
	for(i=0; i<52/playerNum; i++){
		for(j=0; j<playerNum; j++){
			player[j].hand[i].suit=deck[k].suit;
			player[j].hand[i].num=deck[k].num;
			k++;
		}
	}
	
	/*hand sort suru SHDC 1234*/
	for(i=0; i<playerNum; i++){
		sortCards(player[i].hand,playerNum);
	}
	
	//7 card dasu
		for(i=0; i<playerNum; i++){
			player[i].handMax=52/playerNum;
			for(j=0; j<52/playerNum; j++){
				if(player[i].hand[j].num==7){
					putCard(&player[i],j);
					if(player[i].hand[j].suit=='D') p=i;
				}
			}
		}
	
	printf("--Game Start--\n");
		
	do{
		//field hyouzi
		printField(deck);

		//player kakuninn
		printf("%s's turn\nAre You %s? ", player[p].name, player[p].name);
		do{
			scanf("%c",&yn);
		}while(yn!='Y' && yn!='y');

		//player hand hyouzi
		for(i=0; i<player[p].handMax; i++){
			printf("%c%d ",player[p].hand[i].suit,player[p].hand[i].num);
		}
		printf("\n");
		for(i=0; i<player[p].handMax; i++){
			if(player[p].hand[i].num > 10) printf("%3d ",i);
			else printf("%2d ",i);
		}
		printf("\n");

		//dasu card erabu
		printf("put card (pass -1) -> ");
		scanf("%d",&i);
		if(i>=0 && i<player[p].handMax){
			putCard(&player[p],i);
		}
		else if(i==-1) {
			player[p].pass++;
		}
		else printf("gomi");
		
		printf("\n");

		if (player[p].pass > passMax || player[p].handMax == 0)
		{
			player[p].isAlive = 1;
		}
		
		
		p++;
		if(p == playerNum) p=0;
		if(player[p].isAlive == 1) p++;
		
	}while(i!=100);
	
}