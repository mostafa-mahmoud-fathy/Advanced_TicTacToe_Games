#ifndef _4X4_TIC_TAC_TOE_H
#define _4X4_TIC_TAC_TOE_H
#include "BoardGame_Classes.h"

using namespace std;
template <typename T>
class TicTacToe_4X4 :public Board<T> {
protected:
    bool checkThreeInRow(char** board, T player, int startRow, int startCol, int dRow, int dCol);
public:
    static int dist_x ;
    static int dist_y ;
    TicTacToe_4X4();
    bool update_board(int x , int y , T mark)override;
    void display_board()override;
    bool is_win()override;
    bool is_draw()override;
    bool game_is_over()override;

};

template <typename T>
class Player4X4 : public Player<T> {
public:
    Player4X4(string name, T symbol);
    void getmove(int& x, int& y );

};

template <typename T>
class Random_Player4X4 : public RandomPlayer<T> {
public:
    Random_Player4X4(T symbol);
    void getmove(int& x, int& y );
};


//--------------------------------------- IMPLEMENTATION---------------------------------------
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

template <typename T>
int TicTacToe_4X4<T> :: dist_x =- 1;

template <typename T>
int TicTacToe_4X4<T> :: dist_y =- 1;
// Constructor for X_O_Board
template <typename T>
TicTacToe_4X4<T>::TicTacToe_4X4() {
    this->rows = this->columns = 4;
    this->board = new char* [this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            if(i == 0 && j%2 == 0){
                this->board[i][j] = 'O';
            }
            else if(i == 0 && j%2 != 0){
                this->board[i][j] = 'X';
            }
            else if(i == 3 && j%2 == 0){
                this->board[i][j] = 'X';
            }
            else if(i == 3 && j%2 != 0){
                this->board[i][j] = 'O';
            }
            else{
                this->board[i][j] = 0;
            }
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool TicTacToe_4X4<T>::update_board( int x , int y , T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns)
         &&(this->board[x][y] == mark ) && (this->board[dist_x][dist_y] == 0)
         &&(abs(x - dist_x) + abs(y - dist_y)) == 1){

        if (mark == 0) {
            this->board[x][y] = 0;
        }
        else {
            this->board[dist_x][dist_y] = toupper(mark);
            this->board[x][y] = 0 ;
        }

        return true;
    }
    return false;
}


// Display the board and the pieces on it
template <typename T>
void TicTacToe_4X4<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n" << string(38,'-');
    }
    cout << endl;
}
template <typename T>
bool TicTacToe_4X4<T>::checkThreeInRow(char** board, T player, int startRow, int startCol, int dRow, int dCol) {
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
bool TicTacToe_4X4<T>::is_win() {
    // Iterate through all cells in the grid
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] != 0) { // Skip empty cells
                char player = this->board[i][j];

                if (checkThreeInRow(this->board, player, i, j, 0, 1) ||  // Horizontal
                    checkThreeInRow(this->board, player, i, j, 1, 0) ||  // Vertical
                    checkThreeInRow(this->board, player, i, j, 1, 1) ||  // Diagonal (top-left to bottom-right)
                    checkThreeInRow(this->board, player, i, j, 1, -1)) { // Diagonal (top-right to bottom-left)
                    return true;
                }
            }
        }
    }
    return false;
}

template <typename T>
bool TicTacToe_4X4<T>::is_draw() {
    return false;
}

template <typename T>
bool TicTacToe_4X4<T>::game_is_over() {
    return is_win() || is_draw();
}
template <typename T>
Player4X4<T>::Player4X4(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Player4X4<T>::getmove(int& x, int& y ) {
        cout << "\nPlease enter your move:\n"
             << "- Source position (x y): ";
        cin >> x >> y;
        cout << "- Destination position (x_dist y_dist): ";
        cin >> TicTacToe_4X4<T>::dist_x  >> TicTacToe_4X4<T>::dist_y ;
}

// Constructor for X_O_Random_Player
template <typename T>
Random_Player4X4<T>::Random_Player4X4(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 4;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Random_Player4X4<T>::getmove(int& x, int& y ) {
    x = rand() % this->dimension;  // Random source x
    y = rand() % this->dimension;  // Random source y
    TicTacToe_4X4<T> ::dist_x = rand() % this->dimension;  // Random destination x
    TicTacToe_4X4<T> :: dist_y = rand() % this->dimension;
}
#endif