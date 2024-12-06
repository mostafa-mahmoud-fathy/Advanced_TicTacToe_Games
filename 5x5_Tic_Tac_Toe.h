#ifndef Tic_Tac_Toe_5x5_H
#define Tic_Tac_Toe_5x5_H
#include "BoardGame_Classes.h"

using namespace std;
template <typename T>
class TicTacToe_5X5 :public Board<T> {
public:
    TicTacToe_5X5();
    bool update_board(int x, int y, T mark) override;
    void display_board()override;
    bool checkThreeInRow(char** board, T player, int startRow, int startCol, int dRow, int dCol);
    bool is_win()override;
    bool is_draw()override;
    bool game_is_over()override;

};

template <typename T>
class Player5x5 : public Player<T> {
public:
    Player5x5(string name, T symbol);
    void getmove(int& x, int& y);

};

template <typename T>
class Random_Player5x5 : public RandomPlayer<T> {
public:
    Random_Player5x5(T symbol);
    void getmove(int& x, int& y);
};


//--------------------------------------- IMPLEMENTATION---------------------------------------
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
TicTacToe_5X5<T>::TicTacToe_5X5() {
    this->rows = this->columns = 5;
    this->board = new char* [this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool TicTacToe_5X5<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) &&(this->board[x][y] == 0 || mark == 0) && !(x == 0 && y == 4) ) { // Only exclude (0,4)
        if (mark == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}


// Display the board and the pieces on it
template <typename T>
void TicTacToe_5X5<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            // Skip cell (0, 4)
            if (i == 0 && j == 4) {
                cout << "      ";
            }
            else {
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << this->board[i][j] << " |";
            }
        }
        cout << "\n" << string(47,'-');
    }
    cout << endl;
}
template <typename T>
bool TicTacToe_5X5<T>::checkThreeInRow(char** board, T player, int startRow, int startCol, int dRow, int dCol) {
    for (int i = 0; i < 3; i++) {
        int newRow = startRow + i * dRow;
        int newCol = startCol + i * dCol;

        if (newRow < 0 || newRow >= this->rows || newCol < 0 || newCol >= this->columns || board[newRow][newCol] != player) {
            return false;
        }
    }
    return true;
}
// Returns true if there is any winner
template <typename T>
bool TicTacToe_5X5<T>::is_win() {
    // Check if all moves have been made (24 moves in total)
    if (this->n_moves < 24) {
        return false; // No need to check for winners yet
    }

    int xCount = 0; // Count of three-in-a-row sequences for player 'X'
    int oCount = 0; // Count of three-in-a-row sequences for player 'O'

    // Iterate through all cells in the grid
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] != 0) { // Skip empty cells
                char player = this->board[i][j]; // Current player ('X' or 'O')

                // Check all four directions starting from (i, j)
                if (checkThreeInRow(this->board, player, i, j, 0, 1)) { // Horizontal
                    if (player == 'X') xCount++;
                    else if (player == 'O') oCount++;
                }

                if (checkThreeInRow(this->board, player, i, j, 1, 0)) { // Vertical
                    if (player == 'X') xCount++;
                    else if (player == 'O') oCount++;
                }

                if (checkThreeInRow(this->board, player, i, j, 1, 1)) { // Diagonal (top-left to bottom-right)
                    if (player == 'X') xCount++;
                    else if (player == 'O') oCount++;
                }

                if (checkThreeInRow(this->board, player, i, j, 1, -1)) { // Diagonal (top-right to bottom-left)
                    if (player == 'X') xCount++;
                    else if (player == 'O') oCount++;
                }
            }
        }
    }


    // Check if either player has more three-in-a-row sequences
    if (this->n_moves == 24)
    {
        if (oCount > xCount) {
            return true;
        }

    }
    this->n_moves++;
    if (this->n_moves == 25)
    {
        if (xCount > oCount) {
            return true;
        }

    }

    // No winner
    return false;
}

// Return true if 24 moves are done and no winner
template <typename T>
bool TicTacToe_5X5<T>::is_draw() {
    return (this->n_moves == 25 && !is_win());
}

template <typename T>
bool TicTacToe_5X5<T>::game_is_over() {
    return is_win() || is_draw();
}
template <typename T>
Player5x5<T>::Player5x5(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Player5x5<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
Random_Player5x5<T>::Random_Player5x5(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Random_Player5x5<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 4
    y = rand() % this->dimension;
}

#endif