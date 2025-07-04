#include "global.cpp"

//---------------------------------------Some Logic Stuff------------------------------------------

void turnSwitch(){
    if(turn == O)
        turn = X;
    else if(turn == X)
        turn = O;
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

void keyInput(){

    int key = GetKeyPressed();
    // std::cout<<key<<"\n";
    
    if ((key == KEY_KP_1|| key == KEY_Z) && board[2][0]==NONE) {
        board[2][0] = (plays)turn;
        turnSwitch();
    } else if ((key == KEY_KP_2|| key == KEY_X) && board[2][1]==NONE) {
        board[2][1] = (plays)turn;
        turnSwitch();
    } else if ((key == KEY_KP_3|| key == KEY_C) && board[2][2]==NONE) {
        board[2][2] = (plays)turn;
        turnSwitch();
    } else if ((key == KEY_KP_4|| key == KEY_A) && board[1][0]==NONE) {
        board[1][0] = (plays)turn;
        turnSwitch();
    } else if ((key == KEY_KP_5|| key == KEY_S) && board[1][1]==NONE) {
        board[1][1] = (plays)turn;
        turnSwitch();
    } else if ((key == KEY_KP_6|| key == KEY_D) && board[1][2]==NONE) {
        board[1][2] = (plays)turn;
        turnSwitch();
    } else if ((key == KEY_KP_7|| key == KEY_Q) && board[0][0]==NONE) {
        board[0][0] = (plays)turn;
        turnSwitch();
    } else if ((key == KEY_KP_8|| key == KEY_W) && board[0][1]==NONE) {
        board[0][1] = (plays)turn; 
        turnSwitch();
    } else if ((key == KEY_KP_9|| key == KEY_E) && board[0][2]==NONE) {
        board[0][2] = (plays)turn;
        turnSwitch();
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
                if(board[i-1][j-1]==1)
                    drawO({widthSection*j,heightSection*i});
                if(board[i-1][j-1]==2)
                    drawX({widthSection*j,heightSection*i});
            }
        }
    }
}

//-------------------------------------------------------------------------------------

class buttons{
    
    private:
        Vector2 pos;
        Vector2 size;
        Vector2 renderPos;
        float roundness;
        int segments;
        Color btnBgColor;
        Color defaultBgColor;
        Color btnHoverBgColor;
        Color btnBorderColor;
        Vector4 button;
        string id;

    public:
    
    buttons(Vector2 p, Vector2 s,float r, int seg, Color bgC, Color hvrC, string i){
        pos=p;
        size=s;
        roundness=r;
        segments=seg;
        btnBgColor=defaultBgColor=bgC;
        btnHoverBgColor=hvrC;
        btnBorderColor=BLACK;
        id = i;
        renderPos = renderAt(p,s);
    }
    
    void drawButtons()
    {
        Vector2 mousePos = GetMousePosition();
        if((mousePos.x>button.x && mousePos.x<button.z  && mousePos.y>button.y && mousePos.y<button.w))
            btnBgColor=btnHoverBgColor;
        else
            btnBgColor=defaultBgColor;
            DrawRectangleRounded({renderPos.x,renderPos.y,size.x,size.y},roundness,segments,btnBgColor);
            DrawRectangleRoundedLinesEx({renderPos.x,renderPos.y,size.x,size.y},roundness,segments,2,btnBorderColor);
        Vector2 textPos = renderAt(pos,{(float)MeasureText(id.c_str(),20.0f)});
        DrawText(id.c_str(),textPos.x,textPos.y-10,20,BLACK);
        button = {pos.x-(size.x/2),pos.y-(size.y/2),pos.x+(size.x/2),pos.y+(size.y/2)};
    }
    
    bool isPressed(){
        Vector2 mousePos = GetMousePosition();
        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && (mousePos.x>button.x && mousePos.x<button.z  && mousePos.y>button.y && mousePos.y<button.w)){
            return true;   
        }
        return false;
    }
};


// **********************************************************************************************************

// #### Menus     

void printTest(){
    std::cout<<"Hello!!";      
}

void printTest(int value){
    std::cout<<"Value = "<<value<<"\n";      
}

void mainMenu(){
    
    BeginDrawing();
    ClearBackground(bgColor);
    
    char title[]= "Tic-Tac-Toe";
    int titleLen = MeasureText(title,30);
    DrawText(title,(horizontallyCentered(winWidth,titleLen)),winHeight/8,30,BLACK);

    buttons singleplayerBtn({winWidth/2,200},{(winWidth/2),50},.5,3,SKYBLUE,BLUE,"Singleplayer");
    
    buttons multiplayerBtn({winWidth/2,300},{(winWidth/2),50},.5,3,SKYBLUE,BLUE,"Multiplayer");

    buttons exitBtn({winWidth/2,400},{(winWidth/2),50},.5,3,SKYBLUE,RED,"Exit");
    
    buttons helpBtn({widthSection/3,heightSection/3},{50,50},.5,3,{0,0,0,0},BLUE,"?");
    

    bgColor = LIGHTGRAY;

    const char singTitle[] = "Singleplayer (Coming Soon)";
    const char multTitle[] = "Multiplayer (Pass & Play)";
    int textlen = MeasureText(singTitle,20);    
    singleplayerBtn.drawButtons();
    textlen = MeasureText(multTitle,20);    
    multiplayerBtn.drawButtons();            
    exitBtn.drawButtons();            
    
    helpBtn.drawButtons();

    if(singleplayerBtn.isPressed())
        menu=SinglePlayerModeSelection;
    if(multiplayerBtn.isPressed())
        menu=Multiplayer;
    if(helpBtn.isPressed()){
        menu=Help;
        lastMenu=MainMenu;
    }
    if(exitBtn.isPressed())
        _Exit(0);

    EndDrawing();            
}

void TieDisplay();
void defaultMenu();

void ModeSelectionMenu(){
    BeginDrawing();
    ClearBackground(bgColor);
    buttons Easy({winWidth/2,200},{(winWidth/2),50},.5,3,SKYBLUE,GREEN,"Easy");
    buttons Hard({winWidth/2,300},{(winWidth/2),50},.5,3,SKYBLUE,RED,"Hard");  
    buttons Back({winWidth/2,400},{(winWidth/2),50},.5,3,SKYBLUE,BLUE,"Back");  
    Easy.drawButtons();
    Hard.drawButtons();  
    Back.drawButtons();
    if(Back.isPressed()){
        menu=MainMenu;
    }  
    EndDrawing();            
}

void SingleplayerScreen(){

}

void MultiplayerScreen(){
    
    bgColor = (turn==O)? BLUE:RED;

    BeginDrawing();
    ClearBackground(bgColor);

    const char* turnText = (turn==O)? "Player 1 plays" : "Player 2 plays";
    int turnTextlen = MeasureText(turnText,30);
    buttons helpBtn({widthSection/3,heightSection/3},{50,50},.5,3,{0,0,0,0},BLUE,"?");

    DrawText(turnText,(winWidth/2)-(turnTextlen/2),(heightSection/2)-15,30,BLACK);

    // NOTE : # for ttt
    drawHashBoard();

    keyInput();

    helpBtn.drawButtons();

    if(helpBtn.isPressed()){
        menu=Help;
        lastMenu=Multiplayer;
    }

    EndDrawing();

    win = checkWin();
    if(win!=NONE)
        menu = WinScreen;    
    
    const bool isDraw = checkDraw();
    if(win==NONE && isDraw)
        menu = TieScreen;

}

void defaultMenu(){
    bgColor = BLACK;
    
    BeginDrawing();
    ClearBackground(bgColor);
    char text[]= "Coming Soon...";
    char text1[]= "Press M to return to Main Menu";
    int textlen = MeasureText(text,40);
    int textlen1 = MeasureText(text1,20);
    DrawText(text, winWidth/2-(textlen/2), winHeight/2-30, 40, WHITE);
    DrawText(text1, winWidth/2-(textlen1/2), winHeight/2+30, 20, WHITE);
    EndDrawing();
}


void TieDisplay(){
    bgColor = LIGHTGRAY;
    
    BeginDrawing();
    ClearBackground(bgColor);
    char text[]= "It's a Tie";
    int textlen = MeasureText(text,heightSection/2);
    buttons Reset({winWidth*0.35,(winHeight*0.9)},{widthSection,50},.5,3,SKYBLUE,BLUE,"Reset");  
    buttons Back({winWidth*0.65,(winHeight*0.9)},{widthSection,50},.5,3,SKYBLUE,BLUE,"Back");  

    DrawText(text, winWidth/2-(textlen/2), heightSection*0.3, heightSection/2, BLACK);
    drawHashBoard();    
    Back.drawButtons();
    Reset.drawButtons();
    
    if(Reset.isPressed()){
        turn = O;
        boardReset();
        menu=Multiplayer;
    }  
    if(Back.isPressed()){
        turn = O;
        boardReset();
        menu=MainMenu;
    }  
    EndDrawing();
}


void howToPlayScreen(){
    
    bgColor = LIGHTGRAY;
    char text[]= "A few keybinds to remember :";
    int textlen = MeasureText(text,20);
    buttons backBtn({widthSection/3,heightSection/3},{60,60},.5,3,{0,0,0,0},BLUE,"Back");

    BeginDrawing();
    ClearBackground(bgColor);
    
    DrawText(text, widthSection*2, heightSection*4+20, 20, BLACK);
    drawHashBoard();
    DrawTexture(layoutTexture,widthSection+10,heightSection+10,WHITE);

    backBtn.drawButtons();

    if(backBtn.isPressed() || IsKeyReleased(KEY_F1))
        menu=lastMenu;

    EndDrawing();
}

void winnerDisplay(plays win){
    // bgColor = LIGHTGRAY;
    BeginDrawing();
    const char* text=(win==O)?"Player One Won":"Player Two Won";
    int textlen = MeasureText(text,50);
    buttons Reset({winWidth*0.35,(winHeight*0.9)},{widthSection,50},.5,3,SKYBLUE,BLUE,"Reset");  
    buttons Back({winWidth*0.65,(winHeight*0.9)},{widthSection,50},.5,3,SKYBLUE,BLUE,"Back");  
    
    ClearBackground(bgColor);
    DrawText(text, winWidth/2-(textlen/2), heightSection*.3, 50, BLACK);
    drawHashBoard();    
    DrawLineEx({winLine.startX,winLine.startY},{winLine.endX,winLine.endY},5,BLACK);
    Back.drawButtons();
    Reset.drawButtons();
    if(Reset.isPressed()){
        turn = O;
        boardReset();
        menu=Multiplayer;
    }  
    if(Back.isPressed()){
        turn = O;
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



    menu = Help;  // Just to make Multiplayer menu easier to make 

    
    while(!WindowShouldClose())
        GameLoop();
    CloseWindow();

    #endif

    return 0;
}


void GameLoop(){
    // Pressing M returns to Main Menu
    if(IsKeyPressed(KEY_M) && menu !=Multiplayer){
        menu=MainMenu;
        turn = O;
        boardReset();
    }

    if(IsKeyPressed(KEY_ENTER) && menu == Help)
        menu=Multiplayer;

    if(IsKeyDown(KEY_F1))
        menu=Help;

    if(IsKeyPressed(KEY_R) && menu != Multiplayer){
        menu = Multiplayer;
        turn = O;
        boardReset();
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
            
        default:
            defaultMenu();
            break;
    }
}
