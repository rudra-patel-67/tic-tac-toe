#if defined(PLATFORM_WEB)           // "For Web"
#include <emscripten/emscripten.h>
#endif
#include <cstdlib>
#include "./raylib/include/raylib.h"
#include <iostream>
#include <string>
#include <utility>

#define LIGHTHIGHLIGHT CLITERAL(Color){255, 255, 255, 40}
#define TRANSPARENT CLITERAL(Color){0,0,0,0}

using namespace std;


// ------------------------------Initailization----------------------------------------

enum display{MainMenu,Singleplayer,Multiplayer,SinglePlayerModeSelection,WinScreen,TieScreen,Help,Transition};
enum plays{NONE,X,O};
bool modeOption=false;

plays Turn = X;
plays playerTurn = NONE;
plays aiTurn = NONE;

float winWidth=600;
float winHeight=600;

int deltatime;
int elapsedtime;
double aiThinkStart = -1;  // global
bool aiHasPlayed = false;
int startThinking = -1;


Color bgColor;

struct Line {
    float startX, startY;
    float endX, endY;
};
Line winLine;

float heightSection = winHeight/5;
float widthSection = winWidth/5;


plays board[3][3]={
                    {NONE,NONE,NONE},
                    {NONE,NONE,NONE},
                    {NONE,NONE,NONE}
                };

string helpboard[3][3]={
                    {"Q","W","E"},
                    {"A","S","D"},
                    {"Z","X","C"}
                };
                
display menu = MainMenu;
display nextMenu = MainMenu;
display lastMenu = MainMenu;
plays win=NONE;

bool gameStarted(){
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if (board[i][j] != NONE) {
                return true;
            }
        }
    }
    return false;
}

bool gameEnded(){
    if(win!=NONE)
    return true;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if (board[i][j] == NONE) {
                return false;
            }
        }
    }
    return true;
}



void goBack(){
    menu=lastMenu;
}

void winnerDisplay(plays win);

inline Vector2 renderAt(Vector2 position, Vector2 dimensions){
    return {(position.x-(dimensions.x/2)),(position.y-(dimensions.y/2))};
}

inline int verticallyCentered(float parentHeight, float childHeight){
    return (int)(parentHeight/2)-(int)(childHeight/2);
}

inline int horizontallyCentered(float parentWidth, float childWidth){
    return (int)(parentWidth/2)-(int)(childWidth/2);
}

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
    
    void drawButton()
    {
        Vector2 mousePos = GetMousePosition();
        button = {pos.x-(size.x/2),pos.y-(size.y/2),pos.x+(size.x/2),pos.y+(size.y/2)};
        if((mousePos.x>button.x && mousePos.x<button.z  && mousePos.y>button.y && mousePos.y<button.w))
            btnBgColor=btnHoverBgColor;
        else
            btnBgColor=defaultBgColor;
        DrawRectangleRounded({renderPos.x,renderPos.y,size.x,size.y},roundness,segments,btnBgColor);
        DrawRectangleRoundedLinesEx({renderPos.x,renderPos.y,size.x,size.y},roundness,segments,2,btnBorderColor);
        Vector2 textPos = renderAt(pos,{(float)MeasureText(id.c_str(),20.0f)});
        DrawText(id.c_str(),textPos.x,textPos.y-10,20,BLACK);
    }

    void drawTransparentButton()
    {
        button = {pos.x-(size.x/2),pos.y-(size.y/2),pos.x+(size.x/2),pos.y+(size.y/2)};
        Vector2 textPos = renderAt(pos,{(float)MeasureText(id.c_str(),20.0f)});
        DrawText(id.c_str(),textPos.x,textPos.y-10,20,BLACK);
    }
    
    void drawHighlightOnlyButton()
    {
        Vector2 mousePos = GetMousePosition();
        button = {pos.x-(size.x/2),pos.y-(size.y/2),pos.x+(size.x/2),pos.y+(size.y/2)};
        if((mousePos.x>button.x && mousePos.x<button.z  && mousePos.y>button.y && mousePos.y<button.w))
            btnBgColor=btnHoverBgColor;
        else
            btnBgColor=defaultBgColor;
        Vector2 textPos = renderAt(pos,{(float)MeasureText(id.c_str(),20.0f)});
        DrawRectangleRounded({renderPos.x,renderPos.y,size.x,size.y},roundness,segments,btnBgColor);
        DrawText(id.c_str(),textPos.x,textPos.y-10,20,BLACK);
    }

    bool isHovering(){
        Vector2 mousePos = GetMousePosition();
        return ((mousePos.x>button.x && mousePos.x<button.z  && mousePos.y>button.y && mousePos.y<button.w)) ? true : false;  
    }
    
    bool isPressed(){
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isHovering()){
            return true;   
        }
        return false;
    }

    void changeDimensions(Vector2 p, Vector2 s){
        pos=p;
        size=s;
        renderPos = renderAt(p,s);
    }
};
