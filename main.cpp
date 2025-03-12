#include <cstdlib>
#include "element.h"

int main(){
        
    // Window win;

    InitWindow(600,600, "Tic-Tac-Toe");
    SetWindowMinSize(600, 600);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);

    // ttt game;

    enum display{MainMenu,Singleplayer,Multiplayer,Exit};

    display menu = MainMenu;
    // cin>>menu;
    element elm;

    while(!WindowShouldClose()){
        

        switch (menu)
        {
            case MainMenu:
                elm.MainMenu();
                break;

            
                
            default:
                elm.defaultMenu();
                break;
        }

    }

    CloseWindow();

    return 0;
}