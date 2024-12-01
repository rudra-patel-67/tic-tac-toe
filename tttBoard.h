#include <iostream>
using namespace std;

enum turn{p1,p2};
enum aiDifficulty{easy, hard};
enum mode{single,two};
enum players{player1,player2,ai};

class tttBoard
{
	private:
		int x, y;
		char input;
		char board[3][3];
		turn currentTurn = p1;
		int move=0;
	public:
	aiDifficulty difficulty=easy;
	bool gameOver=false;

	tttBoard()
	{
		reset();
	}

	void reset()
	{
		char temp='1';
		for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
		{
			board[i][j]=temp;
			temp++;
		}
	}

	void draw()
	{
		x=0;
		y=0;
		for(int i=0;i<5;i++)
		{
			if(i%2!=0)
			{
				cout<<"---------";
			}
			else
			{
				for(int j=0 ; j<3 ; j++)
				{
					cout<<board[x][y]<<" ";
					if(j==0 || j==1)
					{
						cout<<"| ";
					}
					y++;
				}
				y=0;
				x++;
			}
			cout<<endl;    
		}
	}
	
	void update()
	{
		char *saidSpot = NULL;					//temporary variable for updating X or O
		for(int i=0;i<3;i++)
		{
			for(int j=0 ; j<3 ; j++)
			{
				if(board[i][j]==input)
				{
					saidSpot = &board[i][j];	//temporary variable gettin the possition to be updated
				}
			}
		}
		if(saidSpot==NULL)
		cout<<"Invalid position input\n";
		else
		{
			if(currentTurn==p1)					//If it's p1's turn update to O else X
			*saidSpot='O';
			else
			*saidSpot='X';
			switchTurn();
			move++;
		}
	}

	void aiInput()
	{

	}

	void userInput()
	{
		if(move>8)
		{
			gameOver=true;
			cout<<"Game ended to Tie";
			return;
		}
		takeInput:
		cout<<"\nEnter your move position : ";
		cin>>input;
		if(input=='O' || input=='X')
		{
			cout<<"Invalid position input\n";
			goto takeInput;
		}
		update();
	}

	void checkVictory()
	{
		int i=0,ii=0;
		char temp = '-';
		char temp1 = '-';
		char temp2 = '-';
		char temp3 = '-';
		for(i=0;i<3;i++)   					
		{
			temp = board[i][ii];							//Horizontal line check
			if(board[i][ii+1]==temp && board[i][ii+2]==temp)
			{
				winnerStatement(temp);
				break;
			}
			temp1 = board[ii][i];							//Vertical line check
			if(board[ii+1][i]==temp1 && board[ii+2][i]==temp1)
			{
				winnerStatement(temp1);
				break;
			}
			temp2 = board[i][i];							//first diagonal
			if(board[i+1][i+1]==temp2 && board[i+2][i+2]==temp2)
			{
				winnerStatement(temp2);
				break;
			}
		}
		temp3 = board[2][0];							//second diagonal
		if(board[1][1]==temp3 && board[0][2]==temp3)
		{
			winnerStatement(temp3);
			return;
		}
	}

	void winnerStatement(char temp)
	{
		draw();
		if(temp=='O')
		cout<<"\nPlayer 1 won !!!\n";
		else
		cout<<"\nPlayer 2 won !!!\n";
		gameOver=true;
	}
	

	void switchTurn()
	{
		if(currentTurn==p1)
			currentTurn=p2;
		else
			currentTurn=p1;
	}

};
