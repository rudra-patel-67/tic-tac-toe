#include "mode.h"

int main()
{
	bool exit = false;	
	cout<<"Tic-Tac-Toe"<<endl<<endl;
	while(!exit)
	{
		char choice=0;
		cout<<"Options :-\n\n";
		cout<<"1. Singleplayer\n";
		cout<<"2. Two player\n";
		cout<<"3. Exit\n";
		cout<<"Your Choice : ";
		cin>>choice;
		switch (choice)
		{
		class gameMode game;
		case '1':
		{
			int possibilityChoice=0;
			do
			{
				cout<<"\nChoose Difficulty : \n";
				cout<<"1. Easy\n";
				cout<<"2. Hard\n";
				cin>>possibilityChoice;
				switch (possibilityChoice)
				{
				case 1:
					cout<<"Easy mode selected\n\n";
					break;
				
				case 2:
					cout<<"Hard mode selected\n\n";
					break;

				default:
					cout<<"Invalid input\n";
					break;
				}
			}
			while(possibilityChoice!=1 && possibilityChoice!=2);
			game.gameBegin(single);

			break;
		}

		case '2':
			game.gameBegin(two);
			break;

		case '3':
			exit=true;
			return 0;
		
		case 'e':
			exit=true;
			return 0;

		default:
			cout<<"Invalid input\n\n";
			break;
		}
	}
    return 0;
}
