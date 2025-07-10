#include "global.cpp"

//---------------------------------------Some Logic Stuff------------------------------------------

void turnSwitch(){                  // For Singleplayer
    if(Turn == O)
        Turn = X;
    else if(Turn == X)
        Turn = O;
}

void playerTurnSwitch(){            // For Multiplayer
    if(playerTurn == O)
        playerTurn = X;
    else if(playerTurn == X)
        playerTurn = O;
}

void setTurns(){
    if((aiTurn==NONE || IsKeyPressed(KEY_Y)) || lastMenu == Singleplayer){
        aiTurn = (plays)GetRandomValue(1,2);
        playerTurn = (aiTurn==X)? O : X;
    }
    else
        playerTurn=X;
}

void boardReset(){
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            board[i][j]=NONE;
}

void boardPrint(){  
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
            std::cout<<board[i][j]<<" ";
        std::cout<<"\n";
    }
}

void turnSwitcher(){
    if(menu==Singleplayer)
        turnSwitch();
    if(menu==Multiplayer)
        playerTurnSwitch();
}

void keyInput(){

    int key = GetKeyPressed();
    // std::cout<<key<<"\n";
    
    if ((key == KEY_KP_1|| key == KEY_Z) && board[2][0]==NONE) {
        board[2][0] = (plays)playerTurn;
        turnSwitcher();
    } else if ((key == KEY_KP_2|| key == KEY_X) && board[2][1]==NONE) {
        board[2][1] = (plays)playerTurn;
        turnSwitcher();
    } else if ((key == KEY_KP_3|| key == KEY_C) && board[2][2]==NONE) {
        board[2][2] = (plays)playerTurn;
        turnSwitcher();
    } else if ((key == KEY_KP_4|| key == KEY_A) && board[1][0]==NONE) {
        board[1][0] = (plays)playerTurn;
        turnSwitcher();
    } else if ((key == KEY_KP_5|| key == KEY_S) && board[1][1]==NONE) {
        board[1][1] = (plays)playerTurn;
        turnSwitcher();
    } else if ((key == KEY_KP_6|| key == KEY_D) && board[1][2]==NONE) {
        board[1][2] = (plays)playerTurn;
        turnSwitcher();
    } else if ((key == KEY_KP_7|| key == KEY_Q) && board[0][0]==NONE) {
        board[0][0] = (plays)playerTurn;
        turnSwitcher();           
    } else if ((key == KEY_KP_8|| key == KEY_W) && board[0][1]==NONE) {
        board[0][1] = (plays)playerTurn; 
        turnSwitcher();
    } else if ((key == KEY_KP_9|| key == KEY_E) && board[0][2]==NONE) {
        board[0][2] = (plays)playerTurn;
        turnSwitcher();
    } 
    
    Rectangle cell;
    Color cellHighlightColor = LIGHTHIGHLIGHT;
    for(int i=1; i<=3; i++){
        for(int j=1; j<=3; j++){
            cell = {(j*widthSection),(i*heightSection),widthSection-10,heightSection-10};
            buttons btn({cell.x+widthSection*0.5f,cell.y+widthSection*.5f},{cell.width,cell.height},.5,5,(Color){0,0,0,0},cellHighlightColor,"");

            if(board[i-1][j-1]==NONE)
                btn.drawHighlightOnlyButton();
            else
                btn.drawTransparentButton();

            if(btn.isPressed() && board[i-1][j-1]==NONE){
                board[i-1][j-1] = (plays)playerTurn;
                turnSwitcher();
            }
        }
    }
}

plays checkWin(){
    // Check rows
    for(int i = 0; i < 3; i++) {
        if(board[i][0] != NONE && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            winLine = {widthSection,heightSection*(i+1)+heightSection/2,widthSection*4,heightSection*(i+1)+heightSection/2};
            return board[i][0];
        }
    }
    
    // Check columns
    for(int i = 0; i < 3; i++) {
        if(board[0][i] != NONE && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            winLine = {widthSection*(i+1)+widthSection/2,heightSection,widthSection*(i+1)+widthSection/2,heightSection*4};     
            return board[0][i];
        }
    }

    // Check diagonals
    if(board[0][0] != NONE && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        winLine = {widthSection,heightSection,widthSection*4,heightSection*4};
        return board[0][0];
    }

    if(board[0][2] != NONE && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        winLine = {widthSection*4,heightSection,widthSection,heightSection*4};
        return board[0][2];
    }

    return NONE;  //Draw
}


bool checkDraw(){
    for(int i=0;i<3;i++)    
        for(int j=0;j<3;j++)    
            if(board[i][j]==NONE)
                return false;
    return true;
}


// --------------------------------DRAWING---------------------------------------------------

void drawX(Vector2 p){
    Vector2 pos = {p.x+20,p.y+20};
    DrawLineEx(pos,{pos.x+widthSection-40,pos.y+heightSection-40},5,BLACK);
    DrawLineEx({pos.x,pos.y+(heightSection-40)},{pos.x+(widthSection-40),pos.y},5,BLACK);
}

void drawO(Vector2 pos){
    DrawRing({pos.x+(widthSection/2),pos.y+(heightSection/2)},40,45,0,360,60,BLACK);
}

void drawHashBoard(){
    for(int i=2; i<4;i++){
        DrawLineEx({widthSection,heightSection*i},{widthSection*(4),heightSection*i},5,BLACK);
        DrawLineEx({widthSection*i,heightSection},{widthSection*i,heightSection*(4)},5,BLACK); 
    }
    if(menu==Help){
        for(int i=1; i<=3;i++){
            for(int j=1;j<=3;j++)
            {
                    DrawText(helpboard[i-1][j-1].c_str(),(widthSection*j)+30,20+(heightSection*i),heightSection*0.80,BLACK);
                }
            }
    }
    else{  
        for(int i=1; i<=3;i++){
            for(int j=1;j<=3;j++)
            {
                if(board[i-1][j-1]==O)
                    drawO({widthSection*j,heightSection*i});
                if(board[i-1][j-1]==X)
                    drawX({widthSection*j,heightSection*i});
            }
        }
    }
}


// **********************************************************************************************************

// #### Menus     

void printTest(){
    std::cout<<"Hello!!";      
}

void printTest(string name,int value){
    std::cout<<name.c_str()<<" "<<value<<"\n";      
}

void mainMenu(){
        
    char title[]= "Tic-Tac-Toe";
    int titleLen = MeasureText(title,30);
    
    static buttons singleplayerBtn({winWidth/2,250},{(winWidth/2),50},.5,3,SKYBLUE,BLUE,"Singleplayer");
    
    static buttons multiplayerBtn({winWidth/2,350},{(winWidth/2),50},.5,3,SKYBLUE,BLUE,"Multiplayer");
    
    // static buttons exitBtn({winWidth/2,400},{(winWidth/2),50},.5,3,SKYBLUE,RED,"Exit");
    
    static buttons helpBtn({widthSection/3,heightSection/3},{50,50},.5,3,{0,0,0,0},BLUE,"?");
    
    bgColor = LIGHTGRAY;
    
    BeginDrawing();
    ClearBackground(bgColor);
    
    DrawText(title,(horizontallyCentered(winWidth,titleLen)),winHeight/4,30,BLACK);

    singleplayerBtn.drawButton();
    multiplayerBtn.drawButton();            
    // exitBtn.drawButton();            
    
    helpBtn.drawButton();

    if(singleplayerBtn.isPressed())
        menu=SinglePlayerModeSelection;
    if(multiplayerBtn.isPressed()){
        playerTurn=X;
        menu=Multiplayer;
    }
    if(helpBtn.isPressed()){
        menu=Help;
        lastMenu=MainMenu;
    }
    // if(exitBtn.isPressed())
    //     exit(0);

    EndDrawing();            
}

void ModeSelectionMenu(){
    
    bgColor = LIGHTGRAY;
    aiTurn = NONE;
    static buttons Easy({winWidth/2,200},{(winWidth/2),50},.5,3,SKYBLUE,GREEN,"Easy");
    static buttons Hard({winWidth/2,300},{(winWidth/2),50},.5,3,SKYBLUE,RED,"Hard");  
    static buttons Back({winWidth/2,400},{(winWidth/2),50},.6,7,SKYBLUE,LIGHTHIGHLIGHT,"Back");  
    lastMenu = menu;
    
    if(Easy.isPressed()) {
        modeOption=false;
        nextMenu=Singleplayer;
        menu=Transition;
    }  
    if(Hard.isPressed()) {
        modeOption=true;
        nextMenu=Singleplayer;
        menu=Transition;
    }  
    if(Back.isPressed()) {
        menu=MainMenu;
    }

    BeginDrawing();
    ClearBackground(bgColor);
    Easy.drawButton();
    Hard.drawButton();
    Back.drawButton();
    EndDrawing();

}

int minimax(plays board[3][3], int depth, bool isMaximizing, plays aiPlayer, plays humanPlayer) {
    // Check for terminal states
    plays winner = checkWin();
    if (winner == aiPlayer) return 10 - depth;  // AI wins (prefer shorter paths)
    if (winner == humanPlayer) return depth - 10;  // Human wins (prefer longer paths)
    if (checkDraw()) return 0;  // Draw
    
    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == NONE) {
                    board[i][j] = aiPlayer;
                    int score = minimax(board, depth + 1, false, aiPlayer, humanPlayer);
                    board[i][j] = NONE;  // Undo move
                    bestScore = max(bestScore, score);
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == NONE) {
                    board[i][j] = humanPlayer;
                    int score = minimax(board, depth + 1, true, aiPlayer, humanPlayer);
                    board[i][j] = NONE;  // Undo move
                    bestScore = min(bestScore, score);
                }
            }
        }
        return bestScore;
    }
}

// Add this function to find the best move
pair<int, int> findBestMove(plays board[3][3], plays aiPlayer, plays humanPlayer) {
    int bestScore = -1000;
    pair<int, int> bestMove = {-1, -1};
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == NONE) {
                board[i][j] = aiPlayer;
                int score = minimax(board, 0, false, aiPlayer, humanPlayer);
                board[i][j] = NONE;  // Undo move
                
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = {i, j};
                }
            }
        }
    }
    
    return bestMove;
}

// Modified aiPlays function
void aiPlays(bool isHard){
    if(Turn == aiTurn){
        if(startThinking == -1){
            startThinking = GetTime();
        }

        string text = "Thinking...";
        Vector2 textpos = renderAt({winWidth/2,heightSection*0.5f},{(float)MeasureText(text.c_str(),40),40});
        
        DrawText(text.c_str(),textpos.x,textpos.y,40,BLACK);
        
        if(!isHard){
            // For easy mode, add a small delay then make random move
            float thinkingTime = 1;
            if(GetTime() - startThinking > thinkingTime){
                while(Turn == aiTurn){
                    int i = GetRandomValue(0, 2);
                    int j = GetRandomValue(0, 2);
                    if(board[i][j] == NONE){
                        board[i][j] = aiTurn;
                        turnSwitch();
                        startThinking = -1;
                        break;
                    }
                }
            }
        }
        
        if(isHard){
            // Add a longer delay for hard mode to show AI is "thinking harder"
            float thinkingTime = GetRandomValue(1,2);
            if(GetTime() - startThinking > thinkingTime){  // 1 second delay
                pair<int, int> bestMove = findBestMove(board, aiTurn, playerTurn);
                
                if(bestMove.first != -1 && bestMove.second != -1){
                    board[bestMove.first][bestMove.second] = aiTurn;
                    turnSwitch();
                    startThinking = -1;
                }
            }
        }
    }
}

void SingleplayerScreen(){
    bgColor = (modeOption) ?  (Color){217, 53, 65,255}:(Color){98, 235, 127,255};
    static buttons Back({winWidth/2,heightSection*4.4f},{(winWidth/2),50},.6,7,TRANSPARENT,LIGHTHIGHLIGHT,"Back");  

    if(aiTurn==NONE || IsKeyPressed(KEY_Y)){
        setTurns();
        if(aiTurn==1){
            playerTurn=O;
        }
        else
            playerTurn=X;
    }
    
    BeginDrawing();
    ClearBackground(bgColor);
    
    aiPlays(modeOption);  // <-- This is the correct call

    if(Turn==playerTurn){
        string text = "Your Turn";
        Vector2 textpos = renderAt({winWidth/2,heightSection*0.5f},{(float)MeasureText(text.c_str(),40),40});
        DrawText(text.c_str(),textpos.x,textpos.y,40,BLACK);
        keyInput();
    }
    
    drawHashBoard();

    
    win = checkWin();
    if(win!=NONE){
        lastMenu = Singleplayer;
        menu = WinScreen;    
    }
    
    const bool isDraw = checkDraw();
    if(win==NONE && isDraw){
        lastMenu = Singleplayer;
        menu = TieScreen;
    }
    
    if(!gameStarted()){
        Back.drawHighlightOnlyButton();
    }
    
    if(Back.isPressed()){
        menu=SinglePlayerModeSelection;
    }  
    EndDrawing();
}

void MultiplayerScreen(){
    
    bgColor = (playerTurn==X)? BLUE:RED;

    BeginDrawing();
    ClearBackground(bgColor);

    const char* turnText = (playerTurn==X)? "Player 1 plays" : "Player 2 plays";
    int turnTextlen = MeasureText(turnText,30);
    static buttons helpBtn({widthSection/3,heightSection/3},{50,50},.5,3,{0,0,0,0},BLUE,"?");
    static buttons Back({winWidth/2,heightSection*4.4f},{(winWidth/2),50},.6,7,SKYBLUE,LIGHTHIGHLIGHT,"Back");  
    DrawText(turnText,(winWidth/2)-(turnTextlen/2),(heightSection/2)-15,30,BLACK);

    // NOTE : # for ttt
    keyInput();
    drawHashBoard();

    helpBtn.drawButton();
    
    if(helpBtn.isPressed()){
        lastMenu=Multiplayer;
        menu=Help;
        printTest("Help button pressed",0);
    }

    if(!gameStarted())
    Back.drawButton();
    
    if(Back.isPressed()){
        printTest("Back button pressed",0);
        menu=MainMenu;
    }
    win = checkWin();
    if(win!=NONE){
        lastMenu = menu;
        menu = WinScreen;    
    }
    
    const bool isDraw = checkDraw();
    if(win==NONE && isDraw)
        menu = TieScreen;
    EndDrawing();
}

void TransitionScreen(display next){
    bgColor = BLACK;
    
    BeginDrawing();
    ClearBackground(bgColor);
    menu = next;
    EndDrawing();
}

void defaultMenu(){
    bgColor = BLACK;
    
    BeginDrawing();
    ClearBackground(bgColor);
    EndDrawing();
}


void TieDisplay(){
    bgColor = LIGHTGRAY;
    
    char text[]= "It's a Tie";
    int textlen = MeasureText(text,heightSection/2);
    static buttons Reset({winWidth*0.35f,(winHeight*0.9f)},{widthSection,50},.5,3,SKYBLUE,BLUE,"Reset");  
    static buttons Back({winWidth*0.65f,(winHeight*0.9f)},{widthSection,50},.5,3,SKYBLUE,BLUE,"Back");  
    static buttons ChangeMode({winWidth*0.50f,(winHeight*0.9f)},{widthSection*1.25f,50},.5,3,SKYBLUE,BLUE,"Change Mode");  

    if(lastMenu==Singleplayer){
        Reset.changeDimensions({winWidth*0.25f,(winHeight*0.9f)},{widthSection,50});  
        Back.changeDimensions({winWidth*0.75f,(winHeight*0.9f)},{widthSection,50});  
    }
    
    BeginDrawing();
    ClearBackground(bgColor);

    DrawText(text, winWidth/2-(textlen/2), heightSection*0.3, heightSection/2, BLACK);
    drawHashBoard();    
    Back.drawButton();
    Reset.drawButton();

    if(lastMenu==Singleplayer){
        ChangeMode.drawButton();
        if(ChangeMode.isPressed()){
            setTurns();
            boardReset();
            menu=SinglePlayerModeSelection;
        }  
    }
    
    if(Reset.isPressed()){
        setTurns();
        boardReset();
        menu=lastMenu;
    }  
    if(Back.isPressed()){
        setTurns();
        boardReset();
        menu=MainMenu;
    }  
    EndDrawing();
}


void howToPlayScreen(){
    
    bgColor = LIGHTGRAY;
    // char text[]= "A few keybinds to remember :";
    // int textlen = MeasureText(text,20);
    static buttons backBtn({widthSection/3,heightSection/3},{60,60},.5,3,{0,0,0,0},BLUE,"Back");

    BeginDrawing();
    ClearBackground(bgColor);
    
    // DrawText(text, widthSection*2, heightSection*4+20, 20, BLACK);
    drawHashBoard();
    // DrawTexture(layoutTexture,widthSection+10,heightSection+10,WHITE);

    backBtn.drawButton();

    if(backBtn.isPressed() || IsKeyReleased(KEY_F1))
        goBack();
    EndDrawing();
}

void winnerDisplay(plays win){
    // bgColor = LIGHTGRAY;
    BeginDrawing();
    string str;     
    if(lastMenu==Singleplayer)
        str=(win==aiTurn)?"AI Won":"Player Won";
    else
        str=(win==X)?"Player One Won":"Player Two Won";
    const char* text = str.c_str();
    int textlen = MeasureText(text,50);
    static buttons Reset({winWidth*0.35f,(winHeight*0.9f)},{widthSection,50},.5,3,SKYBLUE,BLUE,"Reset");  
    static buttons Back({winWidth*0.65f,(winHeight*0.9f)},{widthSection,50},.5,3,SKYBLUE,BLUE,"Back");  
    static buttons ChangeMode({winWidth*0.50f,(winHeight*0.9f)},{widthSection*1.25f,50},.5,3,SKYBLUE,BLUE,"Change Mode");  

    if(lastMenu==Singleplayer){
        Reset.changeDimensions({winWidth*0.25f,(winHeight*0.9f)},{widthSection,50});  
        Back.changeDimensions({winWidth*0.75f,(winHeight*0.9f)},{widthSection,50});  
    }

    ClearBackground(bgColor);
    DrawText(text, winWidth/2-(textlen/2), heightSection*.3, 50, BLACK);

    drawHashBoard();    
    DrawLineEx({winLine.startX,winLine.startY},{winLine.endX,winLine.endY},5,BLACK);

    Back.drawButton();
    Reset.drawButton();

    if(lastMenu==Singleplayer){
        ChangeMode.drawButton();
        if(ChangeMode.isPressed()){
            setTurns();
            boardReset();
            menu=SinglePlayerModeSelection;
        }  
    }
    if(Reset.isPressed()){
        setTurns();
        boardReset();
        menu=lastMenu;
    }  
    if(Back.isPressed()){
        setTurns();
        boardReset();
        menu=MainMenu;
    }  
    EndDrawing();
}



// **********************************************************************************************************

void GameLoop();


int main(){
        
    InitWindow(winWidth, winHeight, "Tic-Tac-Toe");
    SetWindowMinSize(winWidth, winHeight);
    // SetWindowState(FLAG_WINDOW_RESIZABLE);
    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(GameLoop, 0, 1);
    #else
        SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
        //--------------------------------------------------------------------------------------


    deltatime=GetFrameTime();
    elapsedtime=GetTime();
    menu = MainMenu;  // Just to make Multiplayer menu easier to make 

    
    while(!WindowShouldClose())
        GameLoop();
    CloseWindow();

    #endif

    return 0;
}


void GameLoop(){
    
    deltatime++;

    // Pressing M returns to Main Menu
    if(IsKeyPressed(KEY_M) && menu !=Multiplayer){
        menu=MainMenu;
        setTurns();
        boardReset();
    }

    if(IsKeyPressed(KEY_ENTER) && menu == Help)
        menu=Multiplayer;

    if(IsKeyDown(KEY_F1))
        menu=Help;

    if(IsKeyPressed(KEY_R) && (menu != Multiplayer && menu != Singleplayer) && gameEnded()){
        setTurns();
        boardReset();
        menu=lastMenu;
    }


    switch (menu)
    {
        case MainMenu:
            mainMenu();
            break;

        case SinglePlayerModeSelection:
            ModeSelectionMenu();
            break;

        case Singleplayer:
            SingleplayerScreen();
            break;

        case Multiplayer:
            MultiplayerScreen();
            break;

        case WinScreen:
            winnerDisplay(win);
            break;
            
        case TieScreen:
            TieDisplay();
            break;

        case Help:
            howToPlayScreen();
            break;
        
        case Transition:
            TransitionScreen(nextMenu);
            break;
            
        default:
            defaultMenu();
            break;
    }
}
