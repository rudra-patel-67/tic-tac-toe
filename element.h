#define ELEMENT_H  
#ifdef ELEMENT_H   

#include <raylib.h>
#include <iostream>

class element{
    
    private:
        int key;
        Color bgColor;
    
    public:

        void printTest(){
            std::cout<<"Hello!!";      
        }

        element(){
            bgColor = LIGHTGRAY;
        }

        void MainMenu(){

            BeginDrawing();
            ClearBackground(bgColor);
            
            addButton({300,100},{(300),50},.5,3,RED);
            addButton({300,200},{(300),50},.5,3,RED);
            
            // menu=Exit;

            // DrawFPS(10,10);

            EndDrawing();            
        }

        void defaultMenu(){
            bgColor = BLACK;
            
            BeginDrawing();
            ClearBackground(bgColor);
            char text[]= "Default Case";
            int textlen = MeasureText(text,20);
            DrawText(text, 300-(textlen/2), 300-10, 20, WHITE);
            DrawText(TextFormat("%d",textlen), 300-(MeasureText(TextFormat("%d",textlen),20)/2), 330, 20, WHITE);
            EndDrawing();
        }

        void addButton(Vector2 pos, Vector2 size,float roundness, int segments, Color bgColor){
            DrawRectangleRounded({pos.x-(size.x/2),pos.y-(size.y/2),size.x,size.y},roundness,segments,bgColor);
            
            // func();
        }

       
};

#endif