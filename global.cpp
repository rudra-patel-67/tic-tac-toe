#if defined(PLATFORM_WEB)           // "For Web"
#include <emscripten/emscripten.h>
#endif
#include <cstdlib>
#include "./raylib/include/raylib.h"
#include <iostream>
#include <string>

using namespace std;


// ------------------------------Initailization----------------------------------------

enum display{MainMenu,Singleplayer,Multiplayer,SinglePlayerModeSelection,WinScreen,TieScreen,Help,Temp};
enum plays{NONE,O,X};

plays turn = O;

float winWidth=600;
float winHeight=600;

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
display lastMenu = MainMenu;
plays win=NONE;


void winnerDisplay(plays win);

inline Vector2 renderAt(Vector2 position, Vector2 dimensions){
    return {(position.x-(dimensions.x/2)),(position.y-(dimensions.y/2))};
}

inline int verticallyCentered(float parentHeight, float childHeight){
    return {(int)(parentHeight/2)-(int)(childHeight/2)};
}

inline int horizontallyCentered(float parentWidth, float childWidth){
    return {(int)(parentWidth/2)-(int)(childWidth/2)};
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

    void drawTransparentButton()
    {
        Vector2 mousePos = GetMousePosition();
        if((mousePos.x>button.x && mousePos.x<button.z  && mousePos.y>button.y && mousePos.y<button.w))
            btnBgColor=btnHoverBgColor;
        else
            btnBgColor=defaultBgColor;
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
