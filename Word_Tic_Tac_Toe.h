#ifndef WORDTICTACTOE_H
#define WORDTICTACTOE_H

#include <cstdlib>
#include <ctime>
#include <cctype>
#include <unordered_set>
#include <fstream>
#include "MINMAXPLAYER.h"
#include "BoardGame_Classes.h"

using namespace std;

class WordBoard : public Board<char> {
private:
    unordered_set<string> dictionary; // Set to store valid words
    vector<string> load_dictionary(const string& filename);

public:
    WordBoard(int rows = 3, int columns = 3);

    bool update_board(int x, int y, char symbol) override;

    void display_board() override;

    bool is_win() override;

    bool is_draw() override;

    bool game_is_over() override;

    bool is_valid_word(const string& word); // Check if a word is valid
};

class WordPlayer : public Player<char> {
public:
    WordPlayer(string name, char symbol);
    WordPlayer(char symbol);

    void getmove(int& x, int& y) override; // Prompt the player for a move
};

class WordRandomPlayer : public RandomPlayer<char> {
public:
    WordRandomPlayer(char symbol);

    void getmove(int& x, int& y) override; // Generate a random move
};

//class WordAIPlayer : public X_O_MinMax_Player<char> {
//public:
//    WordAIPlayer(char symbol);
//
//    void getmove(int& x, int& y, char opponentLetter); // Accept opponent's letter
//
//private:
//    vector<char> availableLetters; // Store available letters
//    void initializeAvailableLetters();
//    pair<int, int> getBestMove(char letter, char opponentLetter); // Adjusted to consider opponent's letter
//    int calculateMinMax(char symbol, char opponentSymbol, bool isMaximizing);
//};

WordBoard::WordBoard(int rows, int columns) : Board() {
    this->rows = rows;
    this->columns = columns;
    board = new char*[rows];
    for (int i = 0; i < rows; ++i) {
        board[i] = new char[columns]();
    }
    vector<string> words = load_dictionary("dic.txt");
    dictionary = unordered_set<string>(words.begin(), words.end()); // Convert vector to unordered_set
}

vector<string> WordBoard::load_dictionary(const string& filename) {
    vector<string> words;
    ifstream file(filename);
    string word;
    while (file >> word) {
        words.push_back(word);
    }
    return words;
}

bool WordBoard::update_board(int x, int y, char symbol) {
    if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] != '\0') {
        return false;
    }
    board[x][y] = symbol;
    n_moves++;
    return true;
}

void WordBoard::display_board() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            cout << (board[i][j] == '\0' ? '.' : board[i][j]) << " ";
        }
        cout << endl;
    }
}

bool WordBoard::is_win() {
    vector<string> words_to_check;

    for (int i = 0; i < rows; ++i) {
        string row, col;
        for (int j = 0; j < columns; ++j) {
            row += board[i][j];
            col += board[j][i];
        }
        words_to_check.push_back(row);
        words_to_check.push_back(col);
    }

    string diag1, diag2, diag3, diag4;
    for (int i = 0; i < rows; ++i) {
        diag1 += board[i][i];
        diag2 += board[i][rows - i - 1];
        diag3 += board[rows - i - 1][i];
    }
    for(int i = rows - 1; i <= 0; --i){
        diag4 += board[i][i];
    }
    words_to_check.push_back(diag1);
    words_to_check.push_back(diag2);
    words_to_check.push_back(diag3);
    words_to_check.push_back(diag4);

    for (const string& word : words_to_check) {
        if (is_valid_word(word)) {
            return true;
        }
    }
    return false;
}

bool WordBoard::is_draw() {
    return n_moves == rows * columns && !is_win();
}

bool WordBoard::game_is_over() {
    return is_win() || is_draw();
}

bool WordBoard::is_valid_word(const string& word) {
    return dictionary.find(word) != dictionary.end();
}

WordPlayer::WordPlayer(string name, char symbol) : Player(name, symbol) {}

WordPlayer::WordPlayer(char symbol) : Player(symbol) {}

void WordPlayer::getmove(int& x, int& y) {
    do {
    cout << "Enter row :\n";
    cin >> x;
    cout << "Enter column :\n";
    cin >> y;
    } while (!(x >= 0 && x < 3 && y >= 0 && y < 3));
}

WordRandomPlayer::WordRandomPlayer(char symbol) : RandomPlayer(symbol) {}

void WordRandomPlayer::getmove(int& x, int& y) {
    x = rand() % 3;
    y = rand() % 3;
    cout << "computer player chooses: " << x << ", " << y << endl;
}

//WordAIPlayer::WordAIPlayer(char symbol) : X_O_MinMax_Player(symbol){}

//void WordAIPlayer::initializeAvailableLetters() {
//    for (char c = 'A'; c <= 'Z'; ++c) {
//        availableLetters.push_back(c);
//    }
//}

//void WordAIPlayer::getmove(int& x, int& y) {
//    char chosenLetter = availableLetters[rand() % availableLetters.size()];
//
//    // Find the best move based on the chosen letter and the opponent's letter
//    pair<int, int> bestMove = getBestMove(chosenLetter, opponentLetter);
//    x = bestMove.first;
//    y = bestMove.second;
//}

//int WordAIPlayer::calculateMinMax(char symbol, char opponentSymbol, bool isMaximizing) {
//    if (this->boardPtr->is_win()) {
//        return isMaximizing ? -1 : 1;
//    } else if (this->boardPtr->is_draw()) {
//        return 0;
//    }
//
//    int bestValue = isMaximizing ? numeric_limits<int>::min() : numeric_limits<int>::max();
//
//    for (int i = 0; i < 3; ++i) {
//        for (int j = 0; j < 3; ++j) {
//            if (this->boardPtr->update_board(i, j, isMaximizing ? symbol : opponentSymbol)) {
//                int value = calculateMinMax(opponentSymbol, symbol, !isMaximizing);
//                this->boardPtr->update_board(i, j, '\0'); // Undo move
//
//                if (isMaximizing) {
//                    bestValue = max(bestValue, value);
//                } else {
//                    bestValue = min(bestValue, value);
//                }
//            }
//        }
//    }
//
//    return bestValue;
//}

//pair<int, int> WordAIPlayer::getBestMove() {
//    int bestValue = numeric_limits<int>::min();
//    pair<int, int> bestMove = {-1, -1};
//
//    for (int i = 0; i < 3; ++i) {
//        for (int j = 0; j < 3; ++j) {
//            if (this->boardPtr->update_board(i, j, letter)) {
//                int moveValue = calculateMinMax(letter, opponentLetter, false);
//                this->boardPtr->update_board(i, j, '\0'); // Undo move
//
//                if (moveValue > bestValue) {
//                    bestMove = {i, j};
//                    bestValue = moveValue;
//                }
//            }
//        }
//    }
//
//    return bestMove;
//}


#endif // WORDTICTACTOE_H