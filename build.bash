g++ main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o ${PWD##*/}     
x86_64-w64-mingw32-g++ main.cpp -o ${PWD##*/}-win.exe -L./raylib/lib -I./raylib/include -lraylib -lopengl32 -lgdi32 -lwinmm -static-libgcc -static-libstdc++ 
