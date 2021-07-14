#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

// 0 = blank
// 1 = knot/zero
// 2 = cross/x
const int esc=27;

int b[3][3] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
int turns=0;
int token=0, comp=0;
int hm=0;

void displayboard();
void play();
void reset();

void intro()
{
	int err=1;
	printf("WELCOME TO SMARTBOT PROJECT by KESHAV NATH and VATSAL MITTAL\n\n");
	printf("I have created a BOT for Tic Tac Toe / Knots and Crosses / XO\n");
	printf("It is nearly impossible to defeat!\n\n");
	char ch;
	while(err)
	{
		printf("Press 'X' key to be X or 'O' key to be O\n");
		printf("Remember, X always starts first.\n\n");
		ch=getch();
		printf("%c\n",ch);
		if (ch=='0' || ch=='o')
		{
			token=1;
			comp=2;
			err=0;
		}
		else if (ch=='x')
		{
			token = 2;
			comp = 1;
			err = 0;
		}
		else printf("INVALID SELECTION\n");
	}	
	printf("Press D to play against a dumb bot, or anything else to play against the SmartBot!\n");
	ch = getch();
	printf("%c\n",ch);
	if (ch!='d')
		{
			hm=1;
			printf("Good Luck.\n");
		}
	else
		printf("Coward.\n");
}

void turn()
{
	int i=0, j=0;
	char ch;
	int err=1;
	printf("\nYOUR TURN\n");
	while (err)
	{
		printf("ENTER ROW :-");
		ch = getch();
		i = ch - '0';
		printf("%d", i);
	
		printf("\nENTER COLLUMN :-");
		ch = getch();
		j = ch - '0';
		printf("%d \n", i);
		
		if (i>2 || i<0 || j>2 || j<0)
			printf("INVALID\n\n");
		else if (b[i][j]!=0)
			printf("THAT SPACE IS OCCUPIED\n\n");
		else
		{
			b[i][j] = token;
			err=0;
			turns++;
			printf("YOU PLAYED AT %d,%d \n", i,j);
			displayboard();
		}
	}	
}

void dumbturn()
{
	int err=1, i=0,j=0;
	while(err)
	{
		i=rand() % 3;
		j=rand() % 3;
		//printf("%d,%d", i,j";
		
		if (b[i][j]==0)
		{
			err=0;
			b[i][j]=comp;
			printf("\n\nCOMPUTER PLAYED AT %d,%d \n", i,j);
			turns++;
			displayboard();
		}
	}
}

//AI

void ai();

void displayboard()
{
	printf("\n");
	printf("        0  1  2 \n\n");
	int i=0;
	for (i=0; i<3; i++)
	{
		printf("     %d ",i);
		int j=0;
		for (j=0; j<3; j++)
		{
			if (b[i][j] == 1)
				printf(" 0 ");
			else if (b[i][j]==2)
				printf(" X ");
			else 
				printf(" - ");
		}
		printf("\n\n");
	}	
}

void windisplay()
{
	printf("\n\n\n");
	int i=0;
	for (i=0; i<3; i++)
	{
		printf(" || ");
		int j=0;
		for (j=0; j<3; j++)
		{
			if (b[i][j] == 1)
				printf(" 0 ");
			else if (b[i][j]==2)
				printf(" X ");
			else 
				printf(" - ");
		}
		printf(" || \n\n");
	}
}

int diagonals()
{
	if (b[0][0] == b[1][1] && b[1][1] == b[2][2] && b[0][0] > 0)
		return b[0][0];
	else if (b[0][2] == b[1][1] && b[1][1] == b[2][0] && b[2][0] > 0)
		return b[0][2];
	else return 0;
}

int verticals()
{
	int i=0;
	for (i=0; i<3; i++)
	{
		if (b[i][0] == b[i][1] && b[i][1] == b[i][2] && b[i][0] > 0)
			{
				return	b[i][0];
			}
	}
	return 0;
}

int horizontals()
{
	int i=0;
	for (i=0; i<3; i++)
	{
		if (b[0][i] == b[1][i] && b[1][i] == b[2][i] && b[2][i] > 0)
		{
			return	b[0][i];
		}
		
	}
	return 0;
}

int wincheck()
{	int w;
	w=diagonals();
	if (w>0)
		return w;
	else
		w=verticals();
	if (w>0)
		return w;
	else
		w=horizontals();
	if (w>0)
		return w;
	return  0;	
}

void checker()
{
	char tch, cch, ch;
	if (token==1)
	{
		tch='O';
		cch='X';
	}
	else
	{
		tch='X';
		cch='O';
	}
	int win=0;
	if (turns>=5)
		{
			win=wincheck();
			if(win!=0)
			{
				windisplay();
				turns=10;
				if (win==token)
					printf("\nYOU WIN AS %c \n\n",tch);
				else printf("\nCOMPUTER WINS AS %c \n\n", cch);
			}
			
			else if (turns==9)
			{
				windisplay();
				printf("DRAW\n\n");
			}
			
			if(turns>=9)
			{
				printf("\nGOOD GAME\nPress ESC to EXIT or ANY OTHER KEY to PLAY AGAIN.\n");
				ch=getch();
				if(ch!=esc)
					play();
			}	
		}	
}

void play()
{
	reset();
	
	displayboard();
	intro();
	
	if (token==1)
	{
		printf("\n COMPUTER STARTS\n\n");
		if (hm==0)
			dumbturn();
		else
		{
			displayboard();
			ai();
		}
	}
	
	while(turns<9)
	{	
		turn();
		
		checker();
		
		if(turns>9)
			break;
			
		if(hm==0)
			dumbturn();
		else
			ai();
		
		checker();
		if(turns>9)
		
			break;
			
	}
}

void reset()
{
	int i=0;
	for(i=0; i<3; i++)
	{
		int j=0;
		for(j=0; j<3; j++)
		{
			b[i][j]=0;
		}
	}
	turns=0;
	token=0;
	comp=0;
	hm=0;
	
	//random seed
	srand(time(NULL));
}

int main()
{
	play();
	return 0;
}

// BOT STARTS HERE - BOT STARTS HERE - BOT STARTS HERE - BOT STARTS HERE

void ai()
{
	int x,y, win=0, err=1, randerr=1;
	
	while(err)
	{

	//check for wins and losses
	if(turns>=3)
	{
	//check horizontals
	int i=0;
	for (i=0; i<3; i++)
	{
		int j=0;
		for (j=0; j<2; j++)
		{
			if (b[i][j]==b[i][j+1] && b[i][j]>0)
			{
				if (j==0 && b[i][2]==0)
				{
					x=i;
					y=2;
					win=1;
					err=0;
					if (b[i][j]==comp)
						break;
				}
				else if (j==1 && b[i][0]==0)
				{
					x=i;
					y=0;
					win=1;
					err=0;
					if (b[i][j]==comp)
						break;
				}
			}
		}
		if (b[i][0]==b[i][2] && b[i][0] > 0)
		{
			if (b[i][1]==0)
			{
				x=i;
				y=1;
				win=1;
				err=0;
				if (b[i][0]==comp)
					break;
			}
		}
	}
	
	//checkverticals
	if(!win)
	{
		int j=0;
		for (j=0; j<3; j++)
		{
			int i=0;
			for (i=0; i<2; i++)
			{
				if (b[i][j]==b[i+1][j] && b[i][j]>0)
				{
					if (i==0 && b[2][j]==0)
					{
						x=2;
						y=j;
						win=1;
						err=0;
						if (b[i][j]==comp)
							break;
					}
					else if (i==1 && b[0][j]==0)
					{
						x=0;
						y=j;
						win=1;
						err=0;
						if (b[i][j]==comp)
							break;
					}
				}
			}
			if (b[0][j]==b[2][j] && b[0][j]>0)
			{
				if(b[1][j]==0)
				{
					x=1;
					y=j;
					win=1;
					err=0;
					if(b[0][j]==comp)
						break;
				}
			}
		}
	}
	
	//checkdiagonals
	if(!win)
	{
		int i=0;
		for (i=0; i<2; i++)
		{
			if (b[i][i] == b[i+1][i+1] && b[i][i] > 0)
			{
				if (i==0 && b[2][2]==0)
				{
					x=2;
					y=2;
					win=1;
					err=0;
					if (b[i][i]==comp)
						break;
				}
				else if(i==1 && b[0][0]==0)
				{
					x=0;
					y=0;
					win=1;
					err=0;
					if (b[i][i]==comp)
						break;
				}
			}
			if (b[i][2-i]==b[i+1][1-i] && b[i][2-i] > 0)
			{
				if (i==0 && b[2][0]==0)
				{
					x=2;
					y=0;
					win=1;
					err=0;
					if(b[0][2]==comp)
						break;
				}
				else if (i==1 && b[0][2] == 0)
				{
					x=0;
					y=2;
					win=1;
					err=0;
					if(b[2][0]==comp)
						break;
				}
			}
		}
		if(b[0][0]==b[2][2] && b[0][0]>0)
		{
			if (b[1][1]==0)
			{
				x=1;
				y=1;
				win=1;
				err=0;
				if(b[0][0]==comp)
					break;
			}
		}
		if(b[0][2]==b[2][0] && b[0][2]>0)
		{
			if (b[1][1]==0)
			{
				x=1;
				y=1;
				win=1;
				err=0;
				if(b[0][2]==comp)
					break;
			}
		}
	}
	}
	
	//dirtytactics as 0
	if(!win && turns==1)
	{
		if(comp==1)
		{
			if(b[1][1]==token)
			{
				x=0;
				y=0;
				win=1;
				err=0;
			}
		}
	}
	
	if(!win && turns==3)
	{
		if(comp==1)
		{
			if(b[1][1]==comp)
			{
				if((b[0][0]==token && b[2][2]==token) || (b[0][2]==token && b[2][0]==token))
				{
					x=0;
					y=1;
					err=0;
					win=1;
				}
			}
			else if(b[1][1]==token && b[2][2]==token)
			{
				x=2;
				y=0;
				win=1;
				err=0;
			}
		}
	}
	
	//dirtytactics as X
	if(!win && comp==2)
	{
		if(turns==2 && b[0][0]==comp) //corner
		{
			if(b[0][1]!=token && b[0][2]!=token)
			{
				x=0;
				y=2;
				win=1;
				err=0;
			}
			
			else
			{
				x=2;
				y=0;
				win=1;
				err=0;
			}
			
		}
		
		if(turns==4 && b[0][0]==comp)
		{
			if (b[0][2]==comp)
			{
				if(b[1][0]==token || b[2][0]==token || b[2][1]==token)
				{
					x=2;
					y=2;
					win=1;
					err=0;
				}
				else
				{
					x=0;
					y=0;
					win=1;
					err=0;
				}
			}
			
			if (b[2][0]==comp)
			{
				x=2;
				y=2;
				win=1;
				err=0;
			}
		}
		
		if(turns==2 && b[1][1]==comp) //center
		{
			//winner1 - hopeful
			if(b[0][0]==token)
			{
				x=2;
				y=2;
				win=1;
				err=0;
			}
			else if(b[0][2]==token)
			{
				x=2;
				y=0;
				win=1;
				err=0;
			}
			else if(b[2][0]==token)
			{
				x=0;
				y=2;
				win=1;
				err=0;
			}
			else if(b[2][2]==token)
			{
				x=0;
				y=0;
				win=1;
				err=0;
			}
			
			//winner2 - direct
			if(b[0][1]==token || b[1][0]==token)
			{
				x=2;
				y=2;
				win=1;
				err=0;
			}
			else if(b[1][2]==token || b[2][1]==token)
			{
				x=0;
				y=0;
				win=1;
				err=0;
			}
		}
	}
	
	//strategy randomizer for X
	if(!win && turns==0)
	{
		int strat=rand();
		strat=strat%2;
		//printf("%d",strat);
		if (strat==0) //Take center strategy
		{
			x=1;
			y=1;
			err=0;
			win=1;
		}
		else //Take corner strategy
		{
			x=0;
			y=0;
			err=0;
			win=1;
		}
	}
	
	//no stratergy - randomizer
	if(!win)
	{
		if(b[1][1]==0)
		{
			x=1;
			y=1;
			err=0;
		}
		else
		
			while(randerr)
			{
				x=rand() % 3;
				y= rand() % 3;
				
				if (b[x][y]==0)
				{
					randerr=0;
					err=0;
				}	
			}	
	}
	
	b[x][y]=comp;
	turns++;
	printf("THE COMPUTER PLAYED AT %d,%d \n", x,y);
	displayboard();
	
	}
	
}

//Thank you
