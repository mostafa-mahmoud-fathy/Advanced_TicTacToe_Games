#ifndef _MISERE_TICTACTOE_H
#define _MISERE_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

template <typename T>
class Misere_Board : public Board<T> {
public:
    static bool flag;
    Misere_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class Misere_Player : public Player<T> {
public:
    Misere_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class Misere_Random_Player : public RandomPlayer<T> {
public:
    Misere_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

//--------------------------------------- IMPLEMENTATION

// Static member definition
template <typename T>
bool Misere_Board<T>::flag = false; // Defining the static member outside the class

// Constructor for Misere_Board
template <typename T>
Misere_Board<T>::Misere_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;  // Initialize to empty (0)
        }
    }
    this->n_moves = 0;
    flag = false;  // Initialize the flag
}

template <typename T>
bool Misere_Board<T>::update_board(int x, int y, T mark) {
    if(Misere_Board<T>::flag){
        return true;
    }
    if (this->game_is_over()) {
        return false;
    }
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
        if (mark == 0) {
            this->n_moves--;
            this->board[x][y] = 0;  // Clear the cell
        } else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);  // Set the mark (X or O)
        }
        return true;
    }
    return false;
}

template <typename T>
void Misere_Board<T>::display_board() {
    if(! Misere_Board<T>::flag){
        for (int i = 0; i < this->rows; i++) {
            cout << "\n| ";
            for (int j = 0; j < this->columns; j++) {
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << (this->board[i][j] ? this->board[i][j] : ' ') << " |";
            }
            cout << "\n" << string(29,'-');
        }
        cout << endl;
    }

}

// Misere: Returns true if the opponent is forced to win
template <typename T>
bool Misere_Board<T>::is_win() {
    if(flag){
        return true;
    }
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
            flag = true; // Losing condition in Misère
        }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        flag = true; // Losing condition in Misère
    }

    return false; // No loss yet
}

template <typename T>
bool Misere_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());  // Draw if board is full and no losing condition
}

template <typename T>
bool Misere_Board<T>::game_is_over() {
    return is_win() || is_draw();  // Game is over if there's a loss or a draw
}

//--------------------------------------

// Constructor for Misere_Player
template <typename T>
Misere_Player<T>::Misere_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Misere_Player<T>::getmove(int& x, int& y) {
    if(! Misere_Board<T>::flag){
        cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
        cin >> x >> y;
    }
}

// Constructor for Misere_Random_Player
template <typename T>
Misere_Random_Player<T>::Misere_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Misere Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Misere_Random_Player<T>::getmove(int& x, int& y) {
    if(! Misere_Board<T>::flag){
        x = rand() % this->dimension;  // Random number between 0 and 2
        y = rand() % this->dimension;
    }
}

#endif //_MISERE_TICTACTOE_H
