#ifndef _SUS_GAME_H
#define _SUS_GAME_H

#include "boardgame_classes.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>

using namespace std;

// ----------------------------- SUS Board -----------------------------
template <typename T>
class SUSBoard : public Board<T> {
private:
    map<pair<int, int>, int> usedCell;
    int scores[2] = {0, 0}; // Track scores for Player 1 and Player 2

public:
    SUSBoard(int rows = 3, int columns = 3) {
        this->rows = rows;
        this->columns = columns;
        this->board = new T*[rows];
        for (int i = 0; i < rows; i++) {
            this->board[i] = new T[columns];
            for (int j = 0; j < columns; j++) {
                this->board[i][j] = '.';  // Initialize with empty spots (.)
            }
        }
    }

    ~SUSBoard() {
        for (int i = 0; i < this->rows; i++) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }

    T **get_board() {
        return this->board;
    }

    bool update_board(int x, int y, T symbol) override {
        if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == '.') {
            this->board[x][y] = symbol;
            this->n_moves++;
            return true;
        }
        return false;
    }

    void display_board() override {
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                cout << this->board[i][j] << " ";
            }
            cout << endl;
        }
    }

    int check_sus(int x, int y, T symbol, int playerIndex) {
        if (symbol != 'S' && symbol != 'U') return 0; // Valid "S" or "U"

        int susCount = 0;
        T opposite = (symbol == 'S') ? 'U' : 'S';

        // Directions: Horizontal, Vertical, Diagonal
        int dx[] = {1, 0, 1, -1}; // x-direction
        int dy[] = {0, 1, 1, 1};  // y-direction

        for (int d = 0; d < 4; ++d) {
            int count = 1; // Include the current symbol

            // Check forward direction
            for (int step = 1; step <= 2; ++step) {
                int nx = x + dx[d] * step;
                int ny = y + dy[d] * step;
                if (nx >= 0 && nx < this->rows && ny >= 0 && ny < this->columns) {
                    if (step == 1 && this->board[nx][ny] == opposite) {
                        count++;
                    } else if (step == 2 && this->board[nx][ny] == symbol) {
                        count++;
                    }
                }
            }

            // Check backward direction
            for (int step = 1; step <= 2; ++step) {
                int nx = x - dx[d] * step;
                int ny = y - dy[d] * step;
                if (nx >= 0 && nx < this->rows && ny >= 0 && ny < this->columns) {
                    if (step == 1 && this->board[nx][ny] == opposite) {
                        count++;
                    } else if (step == 2 && this->board[nx][ny] == symbol) {
                        count++;
                    }
                }
            }

            // If exactly "S-U-S" sequence is found
            if (count == 3) {
                susCount++;
                // Increment the score for the player who made the move
                this->scores[playerIndex]++;
            }
        }

        return susCount;
    }

    bool is_win() override {
        if (this->scores[0] > this->scores[1]) {
            cout << "Player 1 wins with " << this->scores[0] << " SUS words!\n";
            return true;
        } else if (this->scores[1] > this->scores[0]) {
            cout << "Player 2 wins with " << this->scores[1] << " SUS words!\n";
            return true;
        }
        return false;
    }

    bool is_draw() override {
        return this->n_moves == this->rows * this->columns && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

// ----------------------------- SUS Player -----------------------------
template <typename T>
class SUSPlayer : public Player<T> {
public:
    SUSPlayer(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int &x, int &y) override {
        do {
            cout << this->name << ", enter your row:\n";
            cin >> x;
            cout << this->name << ", enter your column:\n";
            cin >> y;
        } while (!(x >= 0 && x < 3 && y >= 0 && y < 3));
    }
};

// ----------------------------- SUS Random Player -----------------------------
template <typename T>
class SUSRandomPlayer : public RandomPlayer<T> {
public:
    SUSRandomPlayer(T symbol, int dimension = 3) : RandomPlayer<T>(symbol) {
        this->dimension = dimension;
        srand(time(0)); // Seed for random number generator
    }

    void getmove(int &x, int &y) override {
        x = rand() % this->dimension;
        y = rand() % this->dimension;
    }
};

#endif //_SUS_GAME_H
