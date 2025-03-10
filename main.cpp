#include <iostream>
#include <raylib.h>
#include <cstdlib>

int main(){
        
    // Window win;

    InitWindow(600,600, "Tic-Tac-Toe");
    SetWindowMinSize(600, 600);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);
    
    // ttt game;

    enum display{MainMenu,Singleplayer,Multiplayer,Exit};
    Color bgColor = LIGHTGRAY;

    display menu = MainMenu;
    bgColor = LIGHTGRAY;
    int key;

    while(!WindowShouldClose()){
        

        switch (menu)
        {
            case MainMenu:
            
                BeginDrawing();
                ClearBackground(bgColor);
                
                // GetKeyPressed();
                if(IsKeyPressed(KEY_K))
                {
                    bgColor=LIME;
                    ClearBackground(bgColor);
                }
                if(IsKeyPressed(KEY_L))
                {
                    bgColor=LIGHTGRAY;
                    ClearBackground(bgColor);
                }
                
                // std:system("clear");
                key = GetKeyPressed();
                if(key!=0){
                    std::cout<<TextFormat("%s\n",GetKeyName(key));
                }
                
                // menu=Exit;

                DrawFPS(10,10);

                EndDrawing();            
                break;
            
            default:
                bgColor = BLACK;
            
                BeginDrawing();
                ClearBackground(bgColor);
                char text[]= "Default Case";
                int textlen = MeasureText(text,20);
                DrawText(text, 300-(textlen/2), 300-10, 20, WHITE);
                DrawText(TextFormat("%d",textlen), 300-(MeasureText(TextFormat("%d",textlen),20)/2), 330, 20, WHITE);

                EndDrawing();
            
                break;
        }

    }

    CloseWindow();

    return 0;
}