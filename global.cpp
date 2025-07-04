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
plays wonBy = NONE;    // Currently not being used

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