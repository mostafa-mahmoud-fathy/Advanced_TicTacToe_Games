#ifndef NumericTicTacToe_H
#define NumericTicTacToe_H
#include "BoardGame_Classes.h"
#include <vector>
#include <tuple>
#include <iostream>
#include <set>
#include <cstdlib>
using namespace std;

class NumericBoard : public Board<int> {
public:
    NumericBoard() {
        rows = 3;
        columns = 3;
        board = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new int[columns]{0};
        }
    }

    ~NumericBoard() {
        for (int i = 0; i < rows; ++i) {
            delete[] board[i];
        }
        delete[] board;
    }

    bool update_board(int x, int y, int symbol) override {
        if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] != 0) {
            return false;
        }
        board[x][y] = symbol;
        ++n_moves;
        return true;
    }

    void display_board() override {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (board[i][j] == 0) cout << ". ";
                else cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool is_win() override {
        for (int i = 0; i < rows; ++i) {
            if (board[i][0] + board[i][1] + board[i][2] == 15 && board[i][0] && board[i][1] && board[i][2]) return true;
            if (board[0][i] + board[1][i] + board[2][i] == 15 && board[0][i] && board[1][i] && board[2][i]) return true;
        }
        if (board[0][0] + board[1][1] + board[2][2] == 15 && board[0][0] && board[1][1] && board[2][2]) return true;
        if (board[0][2] + board[1][1] + board[2][0] == 15 && board[0][2] && board[1][1] && board[2][0]) return true;
        return false;
    }

    bool is_draw() override {
        return n_moves == rows * columns && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }

    bool ValidMove(int x, int y, int num, int symbol) {
        return x >= 0 && x < rows && y >= 0 && y < columns && board[x][y] == 0 &&
               ((symbol == 1 && num % 2 != 0) || (symbol == 2 && num % 2 == 0));
    }

    bool checkWin() {
        return is_win();
    }

    int** board;
};

class NumericPlayer : public Player<int> {
private:
    set<int> used_numbers;

public:
    NumericPlayer(string n, int symbol) : Player<int>(n, symbol) {}
    NumericPlayer(int symbol) : Player<int>(symbol) {}

    void getmove(int& x, int& y) override {
        int num;
        getmove(x, y, num); 
    }

    void getmove(int& x, int& y, int& num) {
        cout << getname() << "'s turn (" << getsymbol() << "). Enter row, column, and number: ";
        cin >> x >> y >> num;

        // Ensure valid move logic
        while ((getsymbol() == 1 && num % 2 == 0) || (getsymbol() == 2 && num % 2 != 0) || 
                used_numbers.count(num) || num >= 10) {
            cout << "Invalid number. " 
                 << (getsymbol() == 1 ? "Use an odd number." : "Use an even number.") 
                 << " Ensure the number has not been used before. Try again: ";
            cin >> x >> y >> num;
        }
    }

    void add_used_number(int num) {
        used_numbers.insert(num);
    }
};

class NumericAIPlayer : public Player<int> {
private:
    set<int> used_numbers;
    NumericBoard* board;

public:
    NumericAIPlayer(int symbol, NumericBoard* b) : Player<int>(symbol), board(b) {}

    void getmove(int& x, int& y) override {
        int num;
        getmove(x, y, num); 
    }
    
    void getmove(int& x, int& y, int& num) {
        tie(x, y, num) = getAIMove();
        used_numbers.insert(num);
    }

    tuple<int, int, int> getAIMove() {
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                for (int num = 2; num < 10; num += 2) { 
                    if (board->ValidMove(row, col, num, getsymbol())) {
                        board->board[row][col] = num;
                        if (board->checkWin()) {
                            board->board[row][col] = 0;
                            return {row, col, num};
                        }
                        board->board[row][col] = 0;
                    }
                }
            }
        }

        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                for (int num = 2; num < 10; num += 2) {
                    if (board->ValidMove(row, col, num, getsymbol())) {
                        return {row, col, num};
                    }
                }
            }
        }

        return {0, 0, 2}; // Default move
    }
};



void Numerical_Tic_Tac_Toe() {

    cout << "Welcome to Numerical Tic-Tac-Toe!" << endl;
    cout << "Choose an option:" << endl;
    cout << "1. Play against another human" << endl;
    cout << "2. Play against the AI" << endl;

    int choice;
    cin >> choice;

    while (choice != 1 && choice != 2) {
        cout << "Invalid choice! Please enter 1 or 2: ";
        cin >> choice;
    }

    NumericBoard board;
    NumericPlayer player1("Player 1", 1); // Player 1 uses odd numbers
    NumericPlayer player2("Player 2", 2); // Player 2 uses even numbers
    NumericAIPlayer aiPlayer(2, &board);   // AI uses even numbers

    bool AI = (choice == 2);

    cout << "Player 1 will use odd numbers (1, 3, 5, ...)." << endl;
    if (AI) {
        cout << "You are Player 1. The AI will play as Player 2 with even numbers (2, 4, 6, ...)." << endl;
    } else {
        cout << "Player 2 will use even numbers (2, 4, 6, ...)." << endl;
    }

    int currentPlayer = 1; // 1 for Player 1, 2 for Player 2 or AI

    while (!board.game_is_over()) {
        board.display_board();

        int row, col, num;
        if (currentPlayer == 1 || !AI) {
            if (currentPlayer == 1) {
                player1.getmove(row, col, num);
            } else {
                player2.getmove(row, col, num);
            }
            while (!board.update_board(row, col, num)) {
                cout << "Invalid move. Try again: ";
                if (currentPlayer == 1) {
                    player1.getmove(row, col, num);
                } else {
                    player2.getmove(row, col, num);
                }
            }
            if (currentPlayer == 1) player1.add_used_number(num);
            else player2.add_used_number(num);
        } else {
            cout << "AI is making its move..." << endl;
            aiPlayer.getmove(row, col, num);
            while (!board.update_board(row, col, num));
            cout << "AI placed " << num << " at (" << row << ", " << col << ")." << endl;
        }

        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }

    board.display_board();

    if (board.is_win()) {
        cout << (currentPlayer == 2 ? "Player 1" : (AI ? "AI" : "Player 2")) << " wins!" << endl;
    } else {
        cout << "It's a draw!" << endl;
    }

}
#endif