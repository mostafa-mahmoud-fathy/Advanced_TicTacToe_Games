#ifndef FOURINAROWGAME_H
#define FOURINAROWGAME_H

#include <vector>

class FourInARowGame {
private:
    std::vector<std::vector<char>> board; 
    int winner; // 0 = No winner, 1 = Player 1, 2 = Player 2

    bool checkWin(int row, int col, char marker); 
    bool isDraw(); 

public:
    FourInARowGame();
    void startBoard();
    void printBoard();
    int AIMove(char aiMarker, char opponentMarker); 
    bool isValidMove(int col); 
    void makeMove(int col, char marker);
    bool GameOver();
    int getWinner();
};
#endif

/////////////////////////// implementaion
#include <iostream>
#include <cstdlib> // For rand and srand
#include <ctime>   // For seeding rand
using namespace std;

int FourInARowGame::AIMove(char aiMarker, char opponentMarker) {
    // 1. Check for winning move
    for (int col = 0; col < 7; ++col) {
        if (isValidMove(col)) {
            for (int row = 5; row >= 0; --row) {
                if (board[row][col] == '.') {
                    board[row][col] = aiMarker;
                    if (checkWin(row, col, aiMarker)) {
                        board[row][col] = '.'; // Undo move
                        return col;
                    }
                    board[row][col] = '.'; // Undo move
                    break;
                }
            }
        }
    }

    // 2. Check to block opponent's winning move
    for (int col = 0; col < 7; ++col) {
        if (isValidMove(col)) {
            for (int row = 5; row >= 0; --row) {
                if (board[row][col] == '.') {
                    board[row][col] = opponentMarker;
                    if (checkWin(row, col, opponentMarker)) {
                        board[row][col] = '.'; 
                        return col;
                    }
                    board[row][col] = '.'; 
                    break;
                }
            }
        }
    }

    // 3. Random valid move
    srand(time(nullptr)); // Seed random generator
    std::vector<int> validMoves;
    for (int col = 0; col < 7; ++col) {
        if (isValidMove(col)) {
            validMoves.push_back(col);
        }
    }
    if (!validMoves.empty()) {
        int randomIndex = rand() % validMoves.size();
        return validMoves[randomIndex];
    }

    return -1; // No valid move
}


FourInARowGame::FourInARowGame() : board(6, vector<char>(7, '.')), winner(0) {}

void FourInARowGame::startBoard() {
    board = vector<vector<char>>(6, vector<char>(7, '.'));
    winner = 0;
}

void FourInARowGame::printBoard() {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
    cout << "1 2 3 4 5 6 7" << endl; 
}

bool FourInARowGame::isValidMove(int col) {
    return col >= 0 && col < 7 && board[0][col] == '.';
}

void FourInARowGame::makeMove(int col, char marker) {
    for (int row = 5; row >= 0; --row) {
        if (board[row][col] == '.') {
            board[row][col] = marker;
            if (checkWin(row, col, marker)) {
                winner = (marker == 'X') ? 1 : 2;
            }
            return;
        }
    }
}

bool FourInARowGame::checkWin(int row, int col, char marker) {
    // Directions: {row offset, col offset}
    const int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
    for (auto [dr, dc] : directions) {
        int count = 1; // Count the current marker
        for (int d = 1; d <= 3; ++d) { // Check forward direction
            int nr = row + d * dr, nc = col + d * dc;
            if (nr >= 0 && nr < 6 && nc >= 0 && nc < 7 && board[nr][nc] == marker) {
                ++count;
            } else break;
        }
        for (int d = 1; d <= 3; ++d) { // Check backward direction
            int nr = row - d * dr, nc = col - d * dc;
            if (nr >= 0 && nr < 6 && nc >= 0 && nc < 7 && board[nr][nc] == marker) {
                ++count;
            } else break;
        }
        if (count >= 4) return true;
    }
    return false;
}

bool FourInARowGame::isDraw() {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            if (cell == '.') return false;
        }
    }
    return true;
}

bool FourInARowGame::GameOver() {
    return winner != 0 || isDraw();
}

int FourInARowGame::getWinner() {
    return winner;
}

