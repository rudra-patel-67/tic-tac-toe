#include <cstdlib>
#include <raylib.h>
#include <iostream>
#include <string>
using namespace std;

// ------------------------------Initailization----------------------------------------

enum display{MainMenu,Singleplayer,Multiplayer,WinScreen,TieScreen,Exit};
enum plays{null,O,X};

plays turn = O;
plays wonBy = null;

int winWidth=600;
int winHeight=600;

Color bgColor;

int heightSection = winHeight/5;
int widthSection = winWidth/5;


plays board[3][3]={
                    {null,null,null},
                    {null,null,null},
                    {null,null,null}
                };

    

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
            board[i][j]=null;
}

void boardPrint(){  
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
            std::cout<<board[i][j]<<" ";
        std::cout<<"\n";
    }
}


void gameOver(){
    if(wonBy==O){}
        //p1 won
    if(wonBy==X){}
        //p2 won
    
    //Tie
}

display menu = MainMenu;

void menuSwitch(){             // NOTE : ONLY FOR TESTING
    if(menu==MainMenu)
        menu=Exit;
    else if(menu==Exit)
        menu=MainMenu;
}

void keyInput(){
    
    
    int key = GetKeyPressed();
    // std::cout<<key<<"\n";
    
    if (key == KEY_KP_1 && board[2][0]==null) {
        board[2][0] = (plays)turn;
        turnSwitch();
    } else if (key == KEY_KP_2 && board[2][1]==null) {
        board[2][1] = (plays)turn;
        turnSwitch();
    } else if (key == KEY_KP_3 && board[2][2]==null) {
        board[2][2] = (plays)turn;
        turnSwitch();
    } else if (key == KEY_KP_4 && board[1][0]==null) {
        board[1][0] = (plays)turn;
        turnSwitch();
    } else if (key == KEY_KP_5 && board[1][1]==null) {
        board[1][1] = (plays)turn;
        turnSwitch();
    } else if (key == KEY_KP_6 && board[1][2]==null) {
        board[1][2] = (plays)turn;
        turnSwitch();
    } else if (key == KEY_KP_7 && board[0][0]==null) {
        board[0][0] = (plays)turn;
        turnSwitch();
    } else if (key == KEY_KP_8 && board[0][1]==null) {
        board[0][1] = (plays)turn; 
        turnSwitch();
    } else if (key == KEY_KP_9 && board[0][2]==null) {
        board[0][2] = (plays)turn;
        turnSwitch();
    } 
}

plays checkWin(){
    int i,ii;
    i=ii=0;
    plays temp,temp1,temp2,temp3;
    for(i=0;i<3;i++)
    {
        temp = board[i][ii];							//Horizontal line check
        if(board[i][ii+1]==temp && board[i][ii+2]==temp)
        {
            return temp;
            break;
        }
        temp1 = board[ii][i];							//Vertical line check
        if(board[ii+1][i]==temp1 && board[ii+2][i]==temp1)
        {
            return temp1;
            break;
        }
    }
    temp2 = board[0][0];							//first diagonal
    if(board[1][1]==temp2 && board[2][2]==temp2)
    {
        return temp2;
    }
    temp3 = board[2][0];
    if(board[1][1]==temp3 && board[0][2]==temp3)
    {
        return temp3;
    }

    return null;
}

plays win=null;

bool checkDraw(){
    for(int i=0;i<3;i++)    
        for(int j=0;j<3;j++)    
            if(board[i][j]==null)
                return false;
    return true;
}


// --------------------------------DRAWING---------------------------------------------------

void drawX(Vector2 p)
{
    Vector2 pos = {p.x+20,p.y+20};
    DrawLineEx(pos,{pos.x+widthSection-40,pos.y+heightSection-40},5,BLACK);
    DrawLineEx({pos.x,pos.y+(heightSection-40)},{pos.x+(widthSection-40),pos.y},5,BLACK);
}

void drawO(Vector2 pos)
{
    DrawCircle(pos.x+(widthSection/2),pos.y+(heightSection/2),heightSection/2.65,BLACK);
    DrawCircle(pos.x+(widthSection/2),pos.y+(heightSection/2),heightSection/3,bgColor);
}

void drawHashBoard(){
    for(int i=2; i<4;i++)
    {
        DrawLineEx({widthSection,heightSection*i},{widthSection*(4),heightSection*i},5,BLACK);
        DrawLineEx({widthSection*i,heightSection},{widthSection*i,heightSection*(4)},5,BLACK); 
    }
}

//-------------------------------------------------------------------------------------

class buttons{
    
    private:
        Vector2 pos;
        Vector2 size;
        float roundness;
        int segments;
        Color btnBgColor;
        Color defaultBgColor;
        Vector4 button;
        string id;

    public:
    
    buttons(Vector2 p, Vector2 s,float r, int seg, Color bgC, string i){
        pos=p;
        size=s;
        roundness=r;
        segments=seg;
        btnBgColor=defaultBgColor=bgC;
        id = i;
    }
    
    void drawButtons()
    {
        Vector2 mousePos = GetMousePosition();
        if((mousePos.x>button.x && mousePos.x<button.z  && mousePos.y>button.y && mousePos.y<button.w) && id == "exit")
            btnBgColor=RED;
        else if((mousePos.x>button.x && mousePos.x<button.z  && mousePos.y>button.y && mousePos.y<button.w))
            btnBgColor=YELLOW;
        else
            btnBgColor=defaultBgColor;
        DrawRectangleRounded({pos.x-(size.x/2),pos.y-(size.y/2),size.x,size.y},roundness,segments,btnBgColor);

        button = {pos.x-(size.x/2),pos.y-(size.y/2),pos.x+(size.x/2),pos.y+(size.y/2)};
        // func();
    }
    
    bool isPressed(){
        Vector2 mousePos = GetMousePosition();
        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && (mousePos.x>button.x && mousePos.x<button.z  && mousePos.y>button.y && mousePos.y<button.w)){
            cout<<endl<<id<<endl;
            return true;   
        }
        return false;
    }
};


// **********************************************************************************************************

// #### Menus 

void winnerDisplay(plays win);
    

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
    int titleLen = MeasureText(title,20);
    // printTest(titleLen);
    DrawText(title,((winWidth/2)-(titleLen/2)),winHeight/8,20,BLACK);

    buttons btn1({(float)winWidth/2,200},{((float)winWidth/2),50},.5,3,GREEN,"Singleplayer");
    
    buttons btn2({(float)winWidth/2,300},{((float)winWidth/2),50},.5,3,GREEN,"Multliplayer");

    buttons btn3({(float)winWidth/2,400},{((float)winWidth/2),50},.5,3,GREEN,"exit");
    
    bgColor = LIGHTGRAY;

    const char singTitle[] = "Singleplayer (Coming Soon)";
    const char multTitle[] = "Multiplayer (Pass & Play)";
    int textlen = MeasureText(singTitle,20);    
    btn1.drawButtons();
    DrawText(singTitle,(winWidth/2)-(textlen/2),190,20,BLACK);
    textlen = MeasureText(multTitle,20);    
    btn2.drawButtons();            
    DrawText(multTitle,(winWidth/2)-(textlen/2),290,20,BLACK);
    btn3.drawButtons();            
    DrawText("Exit",(winWidth/2)-(MeasureText("Exit",20)/2),390,20,BLACK);
    

    // std::cout << (int)btn1.isPressed() << " " << (int)btn2.isPressed() << "\n";
    
    if(btn1.isPressed())
        menu=Exit;
    if(btn2.isPressed())
        menu=Multiplayer;
    if(btn3.isPressed())
        _Exit(0);

    EndDrawing();            
}

void drawDrawScreen();

void MultiplayerMenu(){
    
    bgColor = (turn==O)? BLUE:RED;

    BeginDrawing();
    ClearBackground(bgColor);

    const char* turnText = (turn==O)? "Player 1 plays" : "Player 2 plays";
    int turnTextlen = MeasureText(turnText,30);
    DrawText(turnText,(winWidth/2)-(turnTextlen/2),(heightSection/2)-15,30,BLACK);

    // NOTE : # for ttt
    drawHashBoard();

    keyInput();

    for(int i=1; i<=3;i++){
        for(int j=1;j<=3;j++)
        {
            if(board[i-1][j-1]==1)
                drawO({widthSection*j,heightSection*i});
            if(board[i-1][j-1]==2)
                drawX({widthSection*j,heightSection*i});
        }
    }

    EndDrawing();

    win = checkWin();
    if(win!=null)
        menu = WinScreen;

    cout<<checkDraw()<<endl;
    

    const bool isDraw = checkDraw();
    if(isDraw)
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


void drawDrawScreen(){
    bgColor = LIGHTGRAY;
    
    BeginDrawing();
    ClearBackground(bgColor);
    char text[]= "It's a Tie";
    char text1[]= "Press R to reset the board";
    char text2[]= "Press M to go to Main Menu";
    int textlen = MeasureText(text,heightSection/2);
    int textlen1 = MeasureText(text1,20);
    int textlen2 = MeasureText(text2,20);
    DrawText(text, winWidth/2-(textlen/2), heightSection*1.85, heightSection/2, BLACK);
    DrawText(text1, winWidth/2-(textlen1/2), winHeight/2+20, 20, BLACK);
    DrawText(text2, winWidth/2-(textlen2/2), winHeight/2+45, 20, BLACK);
    EndDrawing();
}


void howToPlayScreen(){
    bgColor = LIGHTGRAY;
    
    BeginDrawing();
    ClearBackground(bgColor);
    char text[]= "Comingr Soon...";
    char text1[]= "Press M to return to Main Menu";
    int textlen = MeasureText(text,40);
    int textlen1 = MeasureText(text1,20);
    DrawText(text, winWidth/2-(textlen/2), winHeight/2-30, 40, WHITE);
    DrawText(text1, winWidth/2-(textlen1/2), winHeight/2+30, 20, WHITE);
    EndDrawing();
}

void winnerDisplay(plays win){
    // bgColor = LIGHTGRAY;
    BeginDrawing();
    ClearBackground(bgColor);
    const char* text=(win==O)?"Player One Won":"Player Two Won";
    // cout<<text;
    int textlen = MeasureText(text,50);
    DrawText(text, winWidth/2-(textlen/2), winHeight/2-10, 50, BLACK);
    EndDrawing();
}



// **********************************************************************************************************



int main(){
        
    // Window win;

    InitWindow(winWidth, winHeight, "Tic-Tac-Toe");
    SetWindowMinSize(winWidth, winHeight);
    // SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);

    menu = MainMenu;  // Just to make Multiplayer menu easier to make 

    // ttt game;
    
    while(!WindowShouldClose()){
        
        if(IsKeyPressed(KEY_SPACE) && menu==MainMenu)
            menu=Exit;
        else if(IsKeyPressed(KEY_SPACE) && menu==Exit)
            menu=MainMenu;

        if(IsKeyPressed(KEY_M))
            menu=MainMenu;
        if(IsKeyPressed(KEY_R) && menu != Multiplayer){
            menu = Multiplayer;
            turn = O;
            boardReset();
        }

        // menu = TieScreen;

        switch (menu)
        {
            case MainMenu:
                mainMenu();
                break;

            case Multiplayer:
                // howToPlayScreen();
                MultiplayerMenu();
                break;

            case WinScreen:
                winnerDisplay(win);
                break;
             
            case TieScreen:
                drawDrawScreen();
                break;
             
            default:
                defaultMenu();
                break;
        }

    }

    CloseWindow();

    return 0;
}