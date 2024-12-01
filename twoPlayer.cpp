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
			goto takeInpu;