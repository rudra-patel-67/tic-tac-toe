#include "raylib.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <string>
#include <thread> // For multithreading

using namespace std;

#define PORT 8080

enum display { MainMenu, Multiplayer, WinScreen, Temp };
enum plays { NONE, O, X };

// Function to run the game logic and Raylib calls in a separate thread
void RunGame(int client_fd_param) {
    int client_fd = client_fd_param; // Copy the file descriptor for this thread
    plays board[3][3];
    int currentPlayer;
    int myPlayer;
    plays win = NONE;
    display menu = Multiplayer;

    int winWidth = 800;
    int winHeight = 600;
    int boardSize = 600;
    int cellSize = boardSize / 3;

    // Initialize Raylib window for this thread
    InitWindow(winWidth, winHeight, "Tic Tac Toe - Client");
    SetTargetFPS(60);

    // Connect to the server and get player assignment
    struct sockaddr_in serv_addr;
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    if (connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        exit(EXIT_FAILURE);
    }
    cout << "Connected to server" << endl;

    recv(client_fd, &myPlayer, sizeof(myPlayer), 0);
    cout << "Received player assignment: " << myPlayer << endl;

    // Initialize the board
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = NONE;
        }
    }

    // Game loop for this thread
    while (!WindowShouldClose() && menu != Temp) {
        if (client_fd == -1) {
            menu = Temp;
            break;
        }

        if (menu == Multiplayer) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && currentPlayer == myPlayer && win == NONE) {
                Vector2 mouse = GetMousePosition();
                int col = mouse.x / cellSize;
                int row = mouse.y / cellSize;

                if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == NONE) {
                    int move[2] = { row, col };
                    send(client_fd, move, sizeof(move), 0);
                }
            }

            // Receive game state
            int bytesReceived = recv(client_fd, board, sizeof(board), 0);
            if (bytesReceived <= 0) {
                cout << "Server Disconnected" << endl;
                close(client_fd);
                client_fd = -1;
                menu = Temp;
                break;
            }
            recv(client_fd, &currentPlayer, sizeof(currentPlayer), 0);
            recv(client_fd, &win, sizeof(win), 0);
            int gameStatus;
            recv(client_fd, &gameStatus, sizeof(gameStatus), 0);
            if (gameStatus != 0 && menu != WinScreen) {
                menu = WinScreen;
            }

            BeginDrawing();
            ClearBackground(RAYWHITE);
            for (int i = 1; i < 3; i++) {
                DrawLine(i * cellSize, 0, i * cellSize, boardSize, BLACK);
                DrawLine(0, i * cellSize, boardSize, i * cellSize, BLACK);
            }

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    Vector2 center = { (float)j * cellSize + cellSize / 2, (float)i * cellSize + cellSize / 2 };
                    if (board[i][j] == O) {
                        DrawCircle(center.x, center.y, cellSize / 3, BLUE);
                        DrawCircle(center.x, center.y, cellSize / 3 - 10, RAYWHITE);
                    } else if (board[i][j] == X) {
                        DrawLineEx({ center.x - cellSize / 3, center.y - cellSize / 3 }, { center.x + cellSize / 3, center.y + cellSize / 3 }, 5, RED);
                        DrawLineEx({ center.x + cellSize / 3, center.y - cellSize / 3 }, { center.x - cellSize / 3, center.y + cellSize / 3 }, 5, RED);
                    }
                }
            }

            if (menu == Multiplayer) {
                if (currentPlayer == myPlayer) {
                    DrawText("Your Turn", boardSize + 10, 50, 30, DARKGREEN);
                } else {
                    DrawText("Opponent's Turn", boardSize + 10, 50, 30, DARKGRAY);
                }
            } else if (menu == WinScreen) {
                string winner = (win == O) ? "Player One (O)" : "Player Two (X)";
                const char* text = TextFormat("%s wins!", winner.c_str());
                int textlen = MeasureText(text, 40);
                DrawText(text, boardSize + 10, 50, 40, (win == O) ? BLUE : RED);
                DrawText("Press 'R' to Restart", boardSize + 10, 100, 20, GRAY);
            }
            EndDrawing();
        }
        else if (menu == WinScreen) {
             BeginDrawing();
            ClearBackground(RAYWHITE);
            for (int i = 1; i < 3; i++) {
                DrawLine(i * cellSize, 0, i * cellSize, boardSize, BLACK);
                DrawLine(0, i * cellSize, boardSize, i * cellSize, BLACK);
            }

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    Vector2 center = { (float)j * cellSize + cellSize / 2, (float)i * cellSize + cellSize / 2 };
                    if (board[i][j] == O) {
                        DrawCircle(center.x, center.y, cellSize / 3, BLUE);
                        DrawCircle(center.x, center.y, cellSize / 3 - 10, RAYWHITE);
                    } else if (board[i][j] == X) {
                        DrawLineEx({ center.x - cellSize / 3, center.y - cellSize / 3 }, { center.x + cellSize / 3, center.y + cellSize / 3 }, 5, RED);
                        DrawLineEx({ center.x + cellSize / 3, center.y - cellSize / 3 }, { center.x - cellSize / 3, center.y + cellSize / 3 }, 5, RED);
                    }
                }
            }
            string winner = (win == O) ? "Player One (O)" : "Player Two (X)";
            const char* text = TextFormat("%s wins!", winner.c_str());
            int textlen = MeasureText(text, 40);
            DrawText(text, boardSize + 10, 50, 40, (win == O) ? BLUE : RED);
            DrawText("Press 'R' to Restart", boardSize + 10, 100, 20, GRAY);
            EndDrawing();
            if (IsKeyPressed(KEY_R)) {
                win = NONE;
                menu = Multiplayer;
                 for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        board[i][j] = NONE;
                    }
                }
            }
        }
    }

    CloseWindow();
    close(client_fd);
}

int main() {
    // Create two threads for the game instances
    std::thread gameThread1(RunGame, 0); // Pass 0 as a dummy client_fd for the first connection
    std::thread gameThread2(RunGame, 0); // Pass 0 again for the second connection

    // Wait for the threads to finish (which should be when the windows are closed)
    gameThread1.join();
    gameThread2.join();

    return 0;
}
