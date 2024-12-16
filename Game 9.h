#ifndef _SUS_GAME_H
#define _SUS_GAME_H

#include "boardgame_classes.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// ----------------------------- SUS Board -----------------------------

class SUSBoard : public Board<char> {
public:
    SUSBoard(int rows = 3, int columns = 3);

    virtual bool update_board(int x, int y, char symbol) override;
    virtual void display_board() override;
    virtual bool is_win() override;
    virtual bool is_draw() override;
    virtual bool game_is_over() override;

private:
    bool check_sus(int x, int y, char symbol);
};

// ----------------------------- SUS Player -----------------------------

class SUSPlayer : public Player<char> {
public:
    SUSPlayer(string name, char symbol);
    SUSPlayer(char symbol);

    virtual void getmove(int& x, int& y) override;
};

// ----------------------------- SUS Random Player -----------------------------

class SUSRandomPlayer : public RandomPlayer<char> {
public:
    SUSRandomPlayer(char symbol, int dimension = 3);

    virtual void getmove(int& x, int& y) override;
};

// ----------------------------- SUS Board -----------------------------

SUSBoard::SUSBoard(int rows, int columns) {
    this->rows = rows;
    this->columns = columns;
    board = new char*[rows];
    for (int i = 0; i < rows; i++) {
        board[i] = new char[columns];
        for (int j = 0; j < columns; j++) {
            board[i][j] = '.';
        }
    }
}

bool SUSBoard::update_board(int x, int y, char symbol) {
    if (x >= 0 && x < rows && y >= 0 && y < columns && board[x][y] == '.') {
        board[x][y] = symbol;
        n_moves++;
        return true;
    }
    return false;
}

void SUSBoard::display_board() {
    cout << "Current Board:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

bool SUSBoard::check_sus(int x, int y, char symbol) {
    //  هنا هنتشيك على كل صف وعمود ودياجونال عشان نشوف الكلمة اتكونت او لا
    // ممكن كمان الكاونتر يتحط هنا او نحط الكاونتر في فنكشن لوحدها برا
}

bool SUSBoard::is_win() {
    // هنا لازم يكون معانا مثلا كاونتر لعدد الكلمات اللي كونها كل لاعب واللي كون كلمات اكبر يكون كسب
    // ولكن بشرط ان تكون كل الخانات خلصت
}

bool SUSBoard::is_draw() {
    return n_moves == rows * columns && !is_win();
}

bool SUSBoard::game_is_over() {
    return is_win() || is_draw();
}

// ----------------------------- SUS Player -----------------------------

SUSPlayer::SUSPlayer(string name, char symbol) : Player(name, symbol) {}

SUSPlayer::SUSPlayer(char symbol) : Player(symbol) {}

void SUSPlayer::getmove(int& x, int& y) {
    do{
        cout << this->name << ", enter your row:\n";
        cin >> x;
        cout << this->name << ", enter your column:\n";
        cin >> y;
    } while (!(x >= 0 && x < 3 && y >= 0 && y < 3));

}

// ----------------------------- SUS Random Player -----------------------------

SUSRandomPlayer::SUSRandomPlayer(char symbol, int dimension) : RandomPlayer(symbol) {
    this->dimension = dimension;
    srand(time(0)); // Seed for random number generator
}

void SUSRandomPlayer::getmove(int& x, int& y) {
    x = rand() % dimension;
    y = rand() % dimension;
}

#endif //_SUS_GAME_H
