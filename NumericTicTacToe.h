#ifndef NUMERICTICTACTOE_H
#define NUMERICTICTACTOE_H

#include <vector>
#include <tuple>

class NumericTicTacToe {
private:
    std::vector<std::vector<int>> board; // 3x3 board
    std::vector<bool> usedNumbers;     
    int winner;                         // 0 = No winner, 1 = Player 1, 2 = Player 2

    bool checkWin();                  
    bool Draw();                      
    bool ValidNumber(int num, int player); 

public:
    NumericTicTacToe();
    void initializeBoard();
    void printBoard();
    bool ValidMove(int row, int col, int num, int player);
    void makeMove(int row, int col, int num, int player);
    bool GameOver();
    int getWinner();
    std::tuple<int, int, int> getAIMove(); 
};

#endif

///////////////////////////////////////////////////////////// imple

#include <iostream>
#include <tuple>

using namespace std;

NumericTicTacToe::NumericTicTacToe() : board(3, vector<int>(3, 0)), usedNumbers(11, false), winner(0) {}

void NumericTicTacToe::initializeBoard() {
    board = vector<vector<int>>(3, vector<int>(3, 0));
    usedNumbers = vector<bool>(11, false);
    winner = 0;
}

void NumericTicTacToe::printBoard() {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            if (cell == 0) cout << ". ";
            else cout << cell << " ";
        }
        cout << endl;
    }
}

bool NumericTicTacToe::ValidNumber(int num, int player) {
    return (num >= 1 && num < 10 && !usedNumbers[num] &&
           ((player == 1 && num % 2 == 1) || (player == 2 && num % 2 == 0)));
}

bool NumericTicTacToe::ValidMove(int row, int col, int num, int player) {
    return row >= 0 && row < 3 && col >= 0 && col < 3 &&
           board[row][col] == 0 && ValidNumber(num, player);
}

void NumericTicTacToe::makeMove(int row, int col, int num, int player) {
    board[row][col] = num;
    usedNumbers[num] = true;

    if (checkWin()) winner = player;
}

bool NumericTicTacToe::checkWin() {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] && 1 + board[i][1] + board[i][2] == 15) return true;
        if (board[0][i] + board[1][i] + board[2][i] == 15) return true;
    }
    if (board[0][0] + board[1][1] + board[2][2] == 15) return true;
    if (board[0][2] + board[1][1] + board[2][0] == 15) return true;
    return false;
}

bool NumericTicTacToe::Draw() {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            if (cell == 0) return false;
        }
    }
    return true;
}

bool NumericTicTacToe::GameOver() {
    return winner != 0 || Draw();
}

int NumericTicTacToe::getWinner() {
    return winner;
}

std::tuple<int, int, int> NumericTicTacToe::getAIMove() {
    // Basic AI strategy: 
    // 1. Try to win.
    // 2. Block the opponent.
    // 3. Choose the first available spot.

    // Check for winning or blocking move
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            for (int num = 2; num < 10; num += 2) { // Only even numbers for AI
                if (ValidMove(row, col, num, 2)) {
                    board[row][col] = num;
                    if (checkWin()) {
                        board[row][col] = 0; // Undo simulation
                        return {row, col, num};
                    }
                    board[row][col] = 0; // Undo simulation
                }
            }
        }
    }

    // Choose first available move
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            for (int num = 2; num < 10; num += 2) {
                if (ValidMove(row, col, num, 2)) {
                    return {row, col, num};
                }
            }
        }
    }

    return {0, 0, 2}; // Default move (shouldn't reach here)
}
