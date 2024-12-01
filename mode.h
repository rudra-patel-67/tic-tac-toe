#include "tttBoard.h"

class gameMode
{
    private:
	char choice;

    public:
    void gameBegin(mode mode)
    {
		do
		{
			class tttBoard game;
			while(!game.gameOver)
			{
				game.draw();
				game.userInput();
				if(mode == single)
				cout<<"\n\nGame is in single mode\n\n";
				// game.switchTurn();
				game.checkVictory();
			}
			cout<<"\nAnother round?? (Y/n): ";
			cin>>choice;
			if(choice=='n' || choice=='N')
			{
				return;
			}
			else if(choice!='y'||choice!='Y')
			cout<<"Invalid Input";
		}
		while(choice=='y'||choice=='Y');
    }
};
