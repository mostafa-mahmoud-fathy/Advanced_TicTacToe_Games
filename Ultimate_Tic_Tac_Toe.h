#ifndef ULTIMATE_BOARD_H
#define ULTIMATE_BOARD_H

#include "BoardGame_Classes.h"
#include <vector>
#include <iostream>
using namespace std;

// Small Tic Tac Toe Board Class
template <typename T>
class SmallBoard : public Board<T> {
private:
    T grid[3][3]; // 3x3 grid for a small Tic Tac Toe board
    T winner;     // To track the winner of the small board

public:
    SmallBoard();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    T check_winner();
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    T get_winner();
    T get_grid(int row, int col) const {
        return grid[row][col];
    }
};

// Ultimate Tic Tac Toe Board Class
template <typename T>
class UltimateBoard : public Board<T> {
private:
    vector<SmallBoard<T>*> smallBoards; 
    T mainBoard[3][3];                  // Main board to track winners

public:
    UltimateBoard();
    ~UltimateBoard();

    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};
template <typename T>
class Ultimate_Player : public Player<T> {
public:
    Ultimate_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class Ultimate_Random_Player : public RandomPlayer<T> {
public:
    Ultimate_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
SmallBoard<T>::SmallBoard() : winner(' ') {
    this->rows = 3;
    this->columns = 3;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            grid[i][j] = ' ';
}

template <typename T>
bool SmallBoard<T>::update_board(int x, int y, T symbol) {
    if (x >= 0 && x < 3 && y >= 0 && y < 3 && grid[x][y] == ' ') {
        grid[x][y] = symbol;
        return true;
    }
    return false;
}

// Displays a SmallBoard
template <typename T>
void SmallBoard<T>::display_board() {}


// Checks for a winner in the SmallBoard
template <typename T>
T SmallBoard<T>::check_winner() {
    for (int i = 0; i < 3; ++i) {
        if (grid[i][0] != ' ' && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]) return grid[i][0];
        if (grid[0][i] != ' ' && grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i]) return grid[0][i];
    }
    if (grid[0][0] != ' ' && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) return grid[0][0];
    if (grid[0][2] != ' ' && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]) return grid[0][2];
    return ' ';
}

template <typename T>
bool SmallBoard<T>::is_win() {
    winner = check_winner();
    return winner != ' ';
}

template <typename T>
bool SmallBoard<T>::is_draw() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (grid[i][j] == ' ') return false;
    return winner == ' ';
}

template <typename T>
bool SmallBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
T SmallBoard<T>::get_winner() {
    return winner;
}

// UltimateBoard Constructor
template <typename T>
UltimateBoard<T>::UltimateBoard() {
    this->rows = 3;
    this->columns = 3;

    // Initialize 9 smaller boards
    for (int i = 0; i < 9; ++i) {
        smallBoards.push_back(new SmallBoard<T>());
    }

    // Initialize main board
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            mainBoard[i][j] = ' ';
}

// UltimateBoard Destructor
template <typename T>
UltimateBoard<T>::~UltimateBoard() {
    for (auto board : smallBoards) {
        delete board;
    }
}

// Updates the UltimateBoard
template <typename T>
bool UltimateBoard<T>::update_board(int x, int y, T symbol) {
    int smallBoardIndex = (x / 3) * 3 + (y / 3);
    int localX = x % 3, localY = y % 3;

    if (mainBoard[x / 3][y / 3] != ' ') {
        return false;
    }

    if (smallBoards[smallBoardIndex]->update_board(localX, localY, symbol)) {
        if (smallBoards[smallBoardIndex]->is_win()) {
            mainBoard[x / 3][y / 3] = smallBoards[smallBoardIndex]->get_winner();
        }
        return true;
    }
    return false;
}

// Displays the UltimateBoard
template <typename T>
void UltimateBoard<T>::display_board() {
    cout << "\nUltimate Tic Tac Toe Board:\n";

    // Iterate through the 3 rows of the main board
    for (int mainRow = 0; mainRow < 3; ++mainRow) {
        // Iterate through the 3 sub-rows inside each main row (which is the rows of small boards)
        for (int subRow = 0; subRow < 3; ++subRow) {
            cout << "| ";

            // Iterate through the 3 columns of the main board (representing small boards)
            for (int mainCol = 0; mainCol < 3; ++mainCol) {
                int smallBoardIndex = mainRow * 3 + mainCol; // Calculate the index of the small board

                // Display the state of each cell in the current sub-row of the small board
                for (int subCol = 0; subCol < 3; ++subCol) {
                    char cellValue = smallBoards[smallBoardIndex]->get_grid(subRow, subCol);

                    // Display the cell's row, column, and the current symbol (move)
                    cout << "(" << mainRow * 3 + subRow << "," << mainCol * 3 + subCol << ") ";
                    cout << cellValue; // Show the symbol if present

                    if (subCol < 2) {
                        cout << " | "; // Add separator between columns of the small board
                    }
                }
                cout << " || "; // Add separator between small boards
            }
            cout << "\n";
        }
        cout << string(95, '-') << "\n"; // Separator between rows of small boards
    }
    cout << endl;
}

// Checks if there's a winner on the UltimateBoard
template <typename T>
bool UltimateBoard<T>::is_win() {
    for (int i = 0; i < 3; ++i) {
        if (mainBoard[i][0] != ' ' && mainBoard[i][0] == mainBoard[i][1] && mainBoard[i][1] == mainBoard[i][2])
            return true;
        if (mainBoard[0][i] != ' ' && mainBoard[0][i] == mainBoard[1][i] && mainBoard[1][i] == mainBoard[2][i])
            return true;
    }
    if (mainBoard[0][0] != ' ' && mainBoard[0][0] == mainBoard[1][1] && mainBoard[1][1] == mainBoard[2][2])
        return true;
    if (mainBoard[0][2] != ' ' && mainBoard[0][2] == mainBoard[1][1] && mainBoard[1][1] == mainBoard[2][0])
        return true;
    return false;
}

// Checks if the UltimateBoard is a draw
template <typename T>
bool UltimateBoard<T>::is_draw() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (mainBoard[i][j] == ' ') return false;
    return true;
}

// Checks if the game is over
template <typename T>
bool UltimateBoard<T>::game_is_over() {
    return is_win() || is_draw();
}
template <typename T>
Ultimate_Player<T>::Ultimate_Player(string name, T symbol) : Player<T>(name, symbol) {}

// Generate a move for the human player (in this case, the player provides input)
template <typename T>
void Ultimate_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 8) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for Ultimate_Random_Player, passing the symbol to the parent RandomPlayer class
template <typename T>
Ultimate_Random_Player<T>::Ultimate_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 8;
    this->name = "Ultimate Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator

}

// Generate a random move for the computer player
template <typename T>
void Ultimate_Random_Player<T>::getmove(int& x, int& y) {
    srand(time(0));  // Seed random number generator
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

#endif
