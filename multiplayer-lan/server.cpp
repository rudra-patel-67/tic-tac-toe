#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

#define PORT 8080

char board[3][3];
int currentPlayer = 0;

void InitBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

bool IsValidMove(int row, int col) {
    return (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ');
}

bool CheckWin(char symbol) {
    for (int i = 0; i < 3; i++)
        if ((board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) ||
            (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol))
            return true;

    return (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) ||
           (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol);
}

void SendBoard(int client1, int client2) {
    send(client1, board, sizeof(board), 0);
    send(client2, board, sizeof(board), 0);
    send(client1, &currentPlayer, sizeof(currentPlayer), 0);
    send(client2, &currentPlayer, sizeof(currentPlayer), 0);
}

int main() {
    int server_fd, client[2];
    struct sockaddr_in address;
    int opt = 1, addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 2);

    std::cout << "Waiting for players...\n";
    for (int i = 0; i < 2; ++i) {
        client[i] = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        std::cout << "Player " << i + 1 << " connected!\n";
    }

    InitBoard();
    SendBoard(client[0], client[1]);

    while (true) {
        int move[2];
        recv(client[currentPlayer], move, sizeof(move), 0);

        if (IsValidMove(move[0], move[1])) {
            board[move[0]][move[1]] = currentPlayer == 0 ? 'X' : 'O';

            if (CheckWin(currentPlayer == 0 ? 'X' : 'O')) {
                currentPlayer = -1;
            } else {
                currentPlayer = 1 - currentPlayer;
            }
        }

        SendBoard(client[0], client[1]);
    }

    close(server_fd);
    return 0;
}
