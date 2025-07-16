@echo off
for %%F in ("%cd%") do set current_folder=%%~nxF
g++ main.cpp -o %current_folder%-win.exe -L./raylib/lib -I./raylib/include -lraylib -lopengl32 -lgdi32 -lwinmm -static-libgcc -static-libstdc++ 
pause